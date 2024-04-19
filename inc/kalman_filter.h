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

/** @file kalman_filter.h
 ** @brief Kalman Filter Library - Header File
 **/

#ifndef KALMAN_FILTER_H_
#define KALMAN_FILTER_H_

/* === Macros definitions ====================================================================== */

/* === Data type declarations ================================================================== */

/* === API function prototypes ================================================================= */

/**
 * @brief Initializes the Kalman filter.
 */
void kalman_filter_init(void);

/**
 * @brief Performs the prediction step of the Kalman filter.
 *
 * @param control_input Control input for the prediction step.
 */
void kalman_filter_predict(float control_input);

/**
 * @brief Performs the update step of the Kalman filter.
 *
 * @param measurement Measurement input for the update step.
 */
void kalman_filter_update(float measurement);

/**
 * @brief Resets the Kalman filter, setting the estimate and covariance to their initial values.
 */
void kalman_filter_reset(void);

/**
 * @brief Gets the current estimate from the Kalman filter.
 *
 * @return The current estimate.
 */
float kalman_filter_get_estimate(void);

/**
 * @brief Gets the current covariance matrix from the Kalman filter.
 *
 * @return The current covariance matrix.
 */
float kalman_filter_get_covariance(void);

#endif /* KALMAN_FILTER_H_ */
