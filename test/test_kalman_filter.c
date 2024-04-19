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

/** @file test_kalman_filter.c
 ** @brief Unit Tests for the Kalman Filter API (Ceedling)
 **/

/* === Headers files inclusions ================================================================ */

#include <unity.h>
#include "kalman_filter.h"

/* === Macros definitions ====================================================================== */

/* === Private function declarations =========================================================== */

void setUp(void);
void tearDown(void);

void test_kalman_filter_init(void);
void test_kalman_filter_predict(void);
void test_kalman_filter_update(void);
void test_kalman_filter_reset(void);
void test_kalman_filter_get_estimate(void);
void test_kalman_filter_get_covariance(void);

/* === Public variable definitions ============================================================= */

/* === Private variable definitions ============================================================ */

/* === Private function implementations ======================================================== */

void setUp(void) {
    // Set up tasks before each test case is executed
}

void tearDown(void) {
    // Clean up tasks after each test case is executed
}

/* === Public function implementations ========================================================= */

/**
 * @brief Test case: Kalman filter initialization
 */
void test_kalman_filter_init(void) {
    kalman_filter_init();
    TEST_ASSERT_FLOAT_WITHIN(0.001, 0.0, kalman_filter_get_estimate());
    TEST_ASSERT_FLOAT_WITHIN(0.001, 1.0, kalman_filter_get_covariance());
}

/**
 * @brief Test case: Kalman filter prediction
 */
void test_kalman_filter_predict(void) {
    kalman_filter_init();
    kalman_filter_predict(1.0);
    TEST_ASSERT_FLOAT_WITHIN(0.001, 1.0, kalman_filter_get_estimate());
}

/**
 * @brief Test case: Kalman filter update
 */
void test_kalman_filter_update(void) {
    kalman_filter_init();
    kalman_filter_predict(1.0);
    kalman_filter_update(2.0);
    TEST_ASSERT_FLOAT_WITHIN(0.001, 1.5, kalman_filter_get_estimate());
}

/**
 * @brief Test case: Kalman filter reset
 */
void test_kalman_filter_reset(void) {
    kalman_filter_init();
    kalman_filter_predict(1.0);
    kalman_filter_reset();
    TEST_ASSERT_FLOAT_WITHIN(0.001, 0.0, kalman_filter_get_estimate());
    TEST_ASSERT_FLOAT_WITHIN(0.001, 1.0, kalman_filter_get_covariance());
}

/**
 * @brief Test case: Kalman filter get estimate
 */
void test_kalman_filter_get_estimate(void) {
    kalman_filter_init();
    TEST_ASSERT_FLOAT_WITHIN(0.001, 0.0, kalman_filter_get_estimate());
}

/**
 * @brief Test case: Kalman filter get covariance
 */
void test_kalman_filter_get_covariance(void) {
    kalman_filter_init();
    TEST_ASSERT_FLOAT_WITHIN(0.001, 1.0, kalman_filter_get_covariance());
}

/* === End of documentation ==================================================================== */
