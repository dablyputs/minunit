#ifndef MINUNIT_ASSERT_H
#define MINUNIT_ASSERT_H

#include "minunit.h"
#include <math.h>
#include <string.h>

/**
 * Epsilon value for floating-point comparisons.
 * 
 * This value (1E-12) represents the maximum allowed difference between
 * two floating-point numbers to consider them equal. It is used to handle
 * the inherent imprecision in floating-point arithmetic.
 * 
 * The value 1E-12 is chosen because:
 * - It's small enough to catch meaningful differences
 * - It's large enough to handle normal floating-point rounding errors
 * - It provides approximately 12 decimal places of precision
 * 
 * When comparing floating-point numbers:
 * - If |a - b| <= MINUNIT_EPSILON, the numbers are considered equal
 * - If |a - b| > MINUNIT_EPSILON, the numbers are considered different
 * 
 * Note: This value may need adjustment based on your specific needs:
 * - For more precise comparisons, use a smaller value (e.g., 1E-15)
 * - For less precise comparisons, use a larger value (e.g., 1E-6)
 */
#define MINUNIT_EPSILON 1E-12

/**
 * Assert that two integers are equal.
 * 
 * Provides detailed error message including expected and actual values.
 * Uses standard integer comparison.
 */
#define mu_assert_int_eq(expected, result) MU__SAFE_BLOCK(\
    int minunit_tmp_e;\
    int minunit_tmp_r;\
    minunit_assert++;\
    minunit_tmp_e = (expected);\
    minunit_tmp_r = (result);\
    if (minunit_tmp_e != minunit_tmp_r) {\
        (void)snprintf(minunit_last_message, MINUNIT_MESSAGE_LEN, "%s failed:\n\t%s:%d: expected %d but got %d", __func__, __FILE__, __LINE__, minunit_tmp_e, minunit_tmp_r);\
        minunit_status = 1;\
        return;\
    } else {\
        printf(".");\
    }\
)

/**
 * Assert that two floating-point numbers are equal within epsilon.
 * 
 * Uses MINUNIT_EPSILON (1E-12) for comparison to handle floating-point
 * imprecision. Provides detailed error message with significant figures
 * based on epsilon.
 */
#define mu_assert_double_eq(expected, result) MU__SAFE_BLOCK(\
    double minunit_tmp_e;\
    double minunit_tmp_r;\
    minunit_assert++;\
    minunit_tmp_e = (expected);\
    minunit_tmp_r = (result);\
    if (fabs(minunit_tmp_e-minunit_tmp_r) > MINUNIT_EPSILON) {\
        int minunit_significant_figures = 1 - log10(MINUNIT_EPSILON);\
        (void)snprintf(minunit_last_message, MINUNIT_MESSAGE_LEN, "%s failed:\n\t%s:%d: %.*g expected but was %.*g", __func__, __FILE__, __LINE__, minunit_significant_figures, minunit_tmp_e, minunit_significant_figures, minunit_tmp_r);\
        minunit_status = 1;\
        return;\
    } else {\
        printf(".");\
    }\
)

/**
 * Assert that two strings are equal.
 * 
 * Handles NULL pointers gracefully by converting them to "<null pointer>".
 * Uses strcmp for comparison. Provides detailed error message showing
 * expected and actual strings.
 */
#define mu_assert_string_eq(expected, result) MU__SAFE_BLOCK(\
    const char* minunit_tmp_e = expected;\
    const char* minunit_tmp_r = result;\
    minunit_assert++;\
    if (!minunit_tmp_e) {\
        minunit_tmp_e = "<null pointer>";\
    }\
    if (!minunit_tmp_r) {\
        minunit_tmp_r = "<null pointer>";\
    }\
    if(strcmp(minunit_tmp_e, minunit_tmp_r) != 0) {\
        (void)snprintf(minunit_last_message, MINUNIT_MESSAGE_LEN, "%s failed:\n\t%s:%d: '%s' expected but was '%s'", __func__, __FILE__, __LINE__, minunit_tmp_e, minunit_tmp_r);\
        minunit_status = 1;\
        return;\
    } else {\
        printf(".");\
    }\
)

#endif /* MINUNIT_ASSERT_H */
