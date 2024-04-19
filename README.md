@Kzamudio ¿Qué te parece el repositorio? ¡Está chido! :+1:

<h1 align="center">
  <p align="center">:star: Filtro de Kalman - Implementación y Pruebas Unitarias :star:</p>
</h1>


Este repositorio contiene una implementación en C de un Filtro de Kalman, una técnica de estimación y predicción utilizada en sistemas de control y procesamiento de señales. El Filtro de Kalman es útil para estimar el estado de un sistema en tiempo real, dado un conjunto de mediciones sujetas a ruido.

<p align="center" width="100%">
    <img width="60%" src="https://github.com/Kzamudioq/AdM_workspace/assets/138271936/67ba9f76-0e78-4c72-b221-bfcbd64c9453"> 
</p>


## 🧠 ¿Qué es un Filtro de Kalman? 🧠

Es un algoritmo que utiliza mediciones sensoriales a lo largo del tiempo para estimar el estado de un sistema, incluso cuando las mediciones están sujetas a ruido y error.

## 💡 Filtro de Kalman en Realità  💡

El filtro de Kalman juega un papel fundamental en Realità, el sistema autónomo diseñado para la captura de información topográfica. En el subsistema de fusión de datos, 🧠`el filtro de Kalman se despliega como una herramienta esencial para combinar y refinar las mediciones provenientes de diversos sensores, como GPS, encoder, sensor LiDAR e IMU` 💡 . Su función principal radica en mejorar la precisión y coherencia de la representación tridimensional del entorno capturado. Al integrar estas múltiples fuentes de datos, el filtro de Kalman permite compensar las limitaciones individuales de cada sensor y proporciona una estimación más robusta y confiable del estado del sistema. 

Esta integración inteligente de datos permite a Realità generar mapas detallados y precisos del entorno, lo que resulta crucial para una amplia gama de aplicaciones, desde la planificación urbana hasta la gestión de recursos naturales. En resumen, el filtro de Kalman desempeña un papel crucial en la transformación de datos crudos en una representación digital precisa y completa del mundo real.

<p align="center" width="100%">
    <img width="30%" src="https://github.com/Kzamudioq/TSSE-TP3/assets/138271936/7abada0b-9ffd-4dd6-bc57-3e19421aa88d"> 
</p>



## implementación

El código fuente proporcionado implementa un Filtro de Kalman en C. El archivo kalman_filter.c contiene las funciones para inicializar el filtro, realizar predicciones, actualizaciones y obtener estimaciones del estado del sistema.

<p align="center" width="100%">
    <img width="30%" src="https://github.com/Kzamudioq/AdM_workspace/assets/138271936/0f2c5716-6713-4066-b01a-244e71a82916"> 
</p>

## Pruebas Unitarias
Se han desarrollado pruebas unitarias utilizando Ceedling para garantizar la correcta funcionalidad de la implementación del Filtro de Kalman que se muestra a continuación: 

1. ``Test_kalman_filter_init:`` Verifica la inicialización del filtro.
2. ``Test_kalman_filter_predict:`` Prueba la función de predicción.
3. ``Test_kalman_filter_update:`` Evalúa la función de actualización.
4. ``Test_kalman_filter_reset:`` Confirma el reinicio del filtro.
5. ``Test_kalman_filter_get_estimate:`` Verifica la función para obtener la estimación del filtro.
6. ``Test_kalman_filter_get_covariance:`` Prueba la función para obtener la covarianza del filtro.

<p align="center" width="100%">
    <img width="70%" src="https://github.com/Kzamudioq/TSSE-TP3/assets/138271936/c0b997b5-bfdd-44b8-a66f-7f297356f5ae"> 
</p>


### Ejecución de las Pruebas

Después de clonar el repositorio usted debería ejecutar el siguiente comando:

```
pre-commit install
```

Para ejecutar las pruebas unitarias se utiliza el siguiente comando:

```
ceedling test:all
```

<p align="center" width="100%">
    <img width="40%" src="https://github.com/Kzamudioq/TSSE-TP3/assets/138271936/dc53bc81-d2ed-4b99-9804-ee193a1c81b9"> 
</p>


Para generar el informe de cobertura de las pruebas se utiliza el siguiente comando:

```
ceedling clobber gcov:all utils:gcov
```

Para generar la documentación del proyecto se utiliza el siguiente comando:

```
make doc

```

Para compilar el proyecto se utiliza el siguiente comando:

```
make all

```


