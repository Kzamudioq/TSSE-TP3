/**************************************************************************************************
 * @file gps.c
 * @brief Capa de abstracción para el manejo de GPS (implementación)
 *************************************************************************************************/

/* === Inclusiones de archivos de cabecera ===================================================== */

#include <stdio.h>
#include <string.h>
#include <usart.h>
#include "gps.h"

#if (GPS_DEBUG == 1)
#include <usbd_cdc_if.h>
#endif

/* === Variables globales ======================================================================= */

uint8_t rx_data = 0;              // Datos recibidos por el UART
uint8_t rx_buffer[GPSBUFSIZE];    // Buffer de recepción
uint8_t rx_index = 0;              // Índice de posición en el buffer de recepción
GPS_t GPS;                         // Estructura para almacenar los datos del GPS

/* === Funciones privadas ======================================================================= */

/**
 * @brief Imprime un mensaje de depuración a través de USB CDC.
 *
 * @param data Puntero al mensaje a imprimir.
 */
#if (GPS_DEBUG == 1)
void GPS_print(char *data){
    char buf[GPSBUFSIZE] = {0,};
    sprintf(buf, "%s\n", data);
    CDC_Transmit_FS((unsigned char *) buf, (uint16_t) strlen(buf));
}
#endif

/* === Funciones públicas ======================================================================= */

/**
 * @brief Inicializa el módulo GPS.
 */
void GPS_Init() {
    HAL_UART_Receive_IT(GPS_USART, &rx_data, 1);
}

/**
 * @brief Función de callback del UART para manejar los datos recibidos.
 */
void GPS_UART_CallBack() {
    // Si el dato recibido no es un salto de línea y el índice del buffer está dentro de los límites
    if (rx_data != '\n' && rx_index < sizeof(rx_buffer)) {
        rx_buffer[rx_index++] = rx_data;  // Almacena el dato en el buffer
    } else {
        #if (GPS_DEBUG == 1)
        GPS_print((char*)rx_buffer);  // Imprime el mensaje recibido (para depuración)
        #endif

        // Si el mensaje NMEA es válido, lo analiza y actualiza la estructura GPS
        if (GPS_validate((char*) rx_buffer)) {
            GPS_parse((char*) rx_buffer);
        }

        rx_index = 0;                    // Reinicia el índice del buffer
        memset(rx_buffer, 0, sizeof(rx_buffer));  // Limpia el buffer
    }

    // Espera recibir el siguiente dato por el UART
    HAL_UART_Receive_IT(GPS_USART, &rx_data, 1);
}

/**
 * @brief Valida un mensaje NMEA.
 *
 * @param nmeastr Puntero al mensaje NMEA a validar.
 * @return 1 si el mensaje es válido, 0 si es inválido.
 */
int GPS_validate(char *nmeastr) {
    char check[3];              // Almacena el checksum del mensaje
    char checkcalcstr[3];       // Almacena el checksum calculado del mensaje
    int i;
    int calculated_check;

    i = 0;
    calculated_check = 0;

    // Verifica que el mensaje comience con '$'
    if (nmeastr[i] == '$') {
        i++;
    } else {
        return 0;
    }

    // Calcula el checksum del mensaje hasta encontrar '*' o finalizar el mensaje
    while ((nmeastr[i] != 0) && (nmeastr[i] != '*') && (i < 75)) {
        calculated_check ^= nmeastr[i];
        i++;
    }

    // Verifica si el mensaje es demasiado largo
    if (i >= 75) {
        return 0;
    }

    // Si hay un carácter '*' después del checksum, lo almacena
    if (nmeastr[i] == '*') {
        check[0] = nmeastr[i + 1];
        check[1] = nmeastr[i + 2];
        check[2] = 0;
    } else {
        return 0;  // No se encontró un separador de checksum, mensaje inválido
    }

    // Calcula el checksum en formato hexadecimal
    sprintf(checkcalcstr, "%02X", calculated_check);

    // Compara los checksums calculado y del mensaje para determinar si el mensaje es válido
    return ((checkcalcstr[0] == check[0]) && (checkcalcstr[1] == check[1])) ? 1 : 0;
}

/**
 * @brief Analiza y procesa un mensaje NMEA.
 *
 * @param GPSstrParse Puntero al mensaje NMEA a analizar.
 */
void GPS_parse(char *GPSstrParse) {
    // Analiza el mensaje según el tipo de sentencia NMEA
    if (!strncmp(GPSstrParse, "$GPGGA", 6)) {
        if (sscanf(GPSstrParse, "$GPGGA,%f,%f,%c,%f,%c,%d,%d,%f,%f,%c", &GPS.utc_time, &GPS.nmea_latitude, &GPS.ns,
                   &GPS.nmea_longitude, &GPS.ew, &GPS.lock, &GPS.satelites, &GPS.hdop, &GPS.msl_altitude,
                   &GPS.msl_units) >= 1) {
            // Convierte las coordenadas NMEA a decimales y las almacena en la estructura GPS
            GPS.dec_latitude = GPS_nmea_to_dec(GPS.nmea_latitude, GPS.ns);
            GPS.dec_longitude = GPS_nmea_to_dec(GPS.nmea_longitude, GPS.ew);
            return;
        }
    } else if (!strncmp(GPSstrParse, "$GPRMC", 6)) {
        if (sscanf(GPSstrParse, "$GPRMC,%f,%f,%c,%f,%c,%f,%f,%d", &GPS.utc_time, &GPS.nmea_latitude, &GPS.ns,
                   &GPS.nmea_longitude, &GPS.ew, &GPS.speed_k, &GPS.course_d, &GPS.date) >= 1)
            return;

    } else if (!strncmp(GPSstrParse, "$GPGLL", 6)) {
        if (sscanf(GPSstrParse, "$GPGLL,%f,%c,%f,%c,%f,%c", &GPS.nmea_latitude, &GPS.ns, &GPS.nmea_longitude,
                   &GPS.ew, &GPS.utc_time, &GPS.gll_status) >= 1)
            return;
    } else if (!strncmp(GPSstrParse, "$GPVTG", 6)) {
        if (sscanf(GPSstrParse, "$GPVTG,%f,%c,%f,%c,%f,%c,%f,%c", &GPS.course_t, &GPS.course_t_unit, &GPS.course_m,
                   &GPS.course_m_unit, &GPS.speed_k, &GPS.speed_k_unit, &GPS.speed_km, &GPS.speed_km_unit) >= 1)
            return;
    }
}

/**
 * @brief Convierte las coordenadas NMEA a decimales.
 *
 * @param deg_coord Coordenadas en formato NMEA (grados decimales).
 * @param nsew Indica si la coordenada es norte/sur o este/oeste.
 * @return Coordenadas en formato decimal.
 */
float GPS_nmea_to_dec(float deg_coord, char nsew) {
    int degree = (int) (deg_coord / 100);
    float minutes = deg_coord - degree * 100;
    float dec_deg = minutes / 60;
    float decimal = degree + dec_deg;
    if (nsew == 'S' || nsew == 'W') {  // Devuelve negativo si es sur u oeste
        decimal *= -1;
    }
    return decimal;
}

/* === Fin del archivo ========================================================================== */