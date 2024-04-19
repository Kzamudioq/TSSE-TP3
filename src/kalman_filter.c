/************************************************************************************************
Copyright (c) 2024, Karen Zamudio <kzamudioquintero@gmail.com>

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
associated documentation files (the "Software"), to deal in the Software without restriction,
including without limitation the rights to use, copy, modify, merge, publish, distribute,
sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial
portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT
NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES
OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

SPDX-License-Identifier: MIT
*************************************************************************************************/

/** @file kalman_filter.c
 ** @brief Kalman Filter Library - Source File
 **/

/* === Header files inclusions ================================================================ */

#include "kalman_filter.h"

/* === Macros definitions ====================================================================== */

/* === Private data type definitions =========================================================== */

/* === Private function prototypes ============================================================= */

/* === Private constant definitions ============================================================ */

/* === Global variable definitions ============================================================= */

static float estimate = 0.0;   /**< Current estimate */
static float covariance = 1.0; /**< Current covariance matrix */

/* === Private function implementations ======================================================== */

/* === Public function implementations ========================================================= */

void kalman_filter_init(void) {
    // Initializes the estimate and covariance
    estimate = 0.0;
    covariance = 1.0;
}

void kalman_filter_predict(float control_input) {
    // Performs the prediction step of the Kalman filter
    // This is an example implementation, replace with your prediction logic
    estimate += control_input;
}

void kalman_filter_update(float measurement) {
    // Performs the update step of the Kalman filter
    // This is an example implementation, replace with your update logic
    float kalman_gain = covariance / (covariance + 1.0); // Kalman gain factor
    estimate += kalman_gain * (measurement - estimate);
    covariance *= (1.0 - kalman_gain);
}

void kalman_filter_reset(void) {
    // Resets the Kalman filter, setting the estimate and covariance to their initial values
    kalman_filter_init();
}

float kalman_filter_get_estimate(void) {
    // Gets the current estimate from the Kalman filter
    return estimate;
}

float kalman_filter_get_covariance(void) {
    // Gets the current covariance matrix from the Kalman filter
    return covariance;
}
