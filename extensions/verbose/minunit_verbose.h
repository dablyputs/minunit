#ifndef MINUNIT_VERBOSE_H
#define MINUNIT_VERBOSE_H

#include "minunit.h"
#include <string.h>

/**
 * ANSI color codes for enhanced test output readability.
 * These codes are used to color-code different types of test output:
 * - RESET: Returns text to default color
 * - BOLD: Makes text bold
 * - RED: Used for failures and errors
 * - GREEN: Used for successful assertions
 * - YELLOW: Used for suite headers
 * - BLUE: Used for test counts
 * - MAGENTA: Used for assertion counts
 * - CYAN: Used for failure counts
 */
#define ANSI_COLOR_RESET   "\x1b[0m"
#define ANSI_BOLD          "\x1b[1m"
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"

/**
 * Defines a verbose test function.
 * Unlike regular tests, verbose tests return a char* to provide detailed error messages.
 * Usage: MU_TEST_VERBOSE(my_test) { ... }
 */
#define MU_TEST_VERBOSE(method_name) static char* method_name(void)

/**
 * Runs a verbose test and handles setup/teardown.
 * Features:
 * - Tracks test timing
 * - Handles test setup and teardown
 * - Prints colored output for failures
 * - Flushes output for immediate feedback
 * Usage: MU_RUN_TEST_VERBOSE(my_test)
 */
#define MU_RUN_TEST_VERBOSE(test) MU__SAFE_BLOCK(\
    if (minunit_real_timer==0 && minunit_proc_timer==0) {\
        minunit_real_timer = mu_timer_real();\
        minunit_proc_timer = mu_timer_cpu();\
    }\
    if (minunit_setup) (*minunit_setup)();\
    minunit_status = 0;\
    char* result = test();\
    minunit_run++;\
    if (result != 0) {\
        minunit_fail++;\
        printf(ANSI_COLOR_RED "[FAIL] %s\n" ANSI_COLOR_RESET, result);\
    }\
    (void)fflush(stdout);\
    if (minunit_teardown) (*minunit_teardown)();\
)

/**
 * Runs a suite of verbose tests.
 * Features:
 * - Prints suite name in yellow
 * - Handles suite-level setup/teardown
 * - Resets setup/teardown after suite completion
 * Usage: MU_RUN_SUITE_VERBOSE(my_suite)
 */
#define MU_RUN_SUITE_VERBOSE(suite_name) do { \
    printf(ANSI_COLOR_YELLOW "[SUITE] Running %s\n" ANSI_COLOR_RESET, #suite_name); \
    suite_name(); \
    minunit_setup = NULL; \
    minunit_teardown = NULL; \
} while (0)

/**
 * Generates a detailed test summary report.
 * Features:
 * - Color-coded statistics
 * - Real and CPU time measurements
 * - Formatted output with bold headers
 * Usage: MU_REPORT_VERBOSE()
 */
#define MU_REPORT_VERBOSE() MU__SAFE_BLOCK(\
    double minunit_end_real_timer;\
    double minunit_end_proc_timer;\
    printf(ANSI_BOLD "\n\n=== Test Summary ===\n" ANSI_COLOR_RESET); \
    printf(ANSI_COLOR_BLUE "Tests run: %d\n" ANSI_COLOR_RESET, minunit_run); \
    printf(ANSI_COLOR_MAGENTA "Assertions: %d\n" ANSI_COLOR_RESET, minunit_assert); \
    printf(ANSI_COLOR_CYAN "Failures: %d\n" ANSI_COLOR_RESET, minunit_fail); \
    minunit_end_real_timer = mu_timer_real();\
    minunit_end_proc_timer = mu_timer_cpu();\
    printf(ANSI_BOLD "\nFinished in %.8f seconds (real) %.8f seconds (proc)\n\n" ANSI_COLOR_RESET, \
        minunit_end_real_timer - minunit_real_timer,\
        minunit_end_proc_timer - minunit_proc_timer);\
)

/**
 * Basic assertions for verbose tests.
 * These macros provide the core assertion functionality with enhanced output.
 */

/**
 * Checks a condition and returns an error message if it fails.
 * Features:
 * - Increments assertion counter
 * - Prints colored success/failure messages
 * - Returns detailed error message on failure
 * Usage: mu_check_verbose(condition)
 */
#define mu_check_verbose(test) MU__SAFE_BLOCK(\
    minunit_assert++;\
    if (!(test)) {\
        (void)snprintf(minunit_last_message, MINUNIT_MESSAGE_LEN, "%s failed:\n\t%s:%d: %s", __func__, __FILE__, __LINE__, #test);\
        minunit_status = 1;\
        printf(ANSI_COLOR_RED "[CHECK FAILED] %s\n" ANSI_COLOR_RESET, minunit_last_message);\
        return minunit_last_message;\
    } else {\
        printf(ANSI_COLOR_GREEN "[CHECK PASSED] %s\n" ANSI_COLOR_RESET, #test);\
    }\
)

/**
 * Forces a test failure with a custom message.
 * Features:
 * - Increments assertion counter
 * - Prints colored failure message
 * - Returns detailed error message
 * Usage: mu_fail_verbose("custom error message")
 */
#define mu_fail_verbose(message) MU__SAFE_BLOCK(\
    minunit_assert++;\
    (void)snprintf(minunit_last_message, MINUNIT_MESSAGE_LEN, "%s failed:\n\t%s:%d: %s", __func__, __FILE__, __LINE__, message);\
    minunit_status = 1;\
    printf(ANSI_COLOR_RED "[FAIL] %s\n" ANSI_COLOR_RESET, minunit_last_message);\
    return minunit_last_message;\
)

/**
 * Asserts a condition with a custom message.
 * Features:
 * - Increments assertion counter
 * - Prints colored success/failure messages
 * - Returns detailed error message on failure
 * Usage: mu_assert_verbose(condition, "custom message")
 */
#define mu_assert_verbose(test, message) MU__SAFE_BLOCK(\
    minunit_assert++;\
    if (!(test)) {\
        (void)snprintf(minunit_last_message, MINUNIT_MESSAGE_LEN, "%s failed:\n\t%s:%d: %s", __func__, __FILE__, __LINE__, message);\
        minunit_status = 1;\
        printf(ANSI_COLOR_RED "[ASSERTION FAILED] %s\n" ANSI_COLOR_RESET, minunit_last_message);\
        return minunit_last_message;\
    } else {\
        printf(ANSI_COLOR_GREEN "[ASSERTION PASSED] %s\n" ANSI_COLOR_RESET, message);\
    }\
)

/**
 * Extended assertions for verbose tests.
 * These macros provide specialized comparison functionality with enhanced output.
 */

/**
 * Asserts that two integers are equal.
 * Features:
 * - Handles integer comparison
 * - Prints actual vs expected values
 * - Returns detailed error message on failure
 * Usage: mu_assert_int_eq_verbose(expected, actual)
 */
#define mu_assert_int_eq_verbose(expected, result) MU__SAFE_BLOCK(\
    int minunit_tmp_e;\
    int minunit_tmp_r;\
    minunit_assert++;\
    minunit_tmp_e = (expected);\
    minunit_tmp_r = (result);\
    if (minunit_tmp_e != minunit_tmp_r) {\
        (void)snprintf(minunit_last_message, MINUNIT_MESSAGE_LEN, "%s failed:\n\t%s:%d: expected %d but got %d", __func__, __FILE__, __LINE__, minunit_tmp_e, minunit_tmp_r);\
        minunit_status = 1;\
        printf(ANSI_COLOR_RED "[INTEGER COMPARISON FAILED] %s\n" ANSI_COLOR_RESET, minunit_last_message);\
        return minunit_last_message;\
    } else {\
        printf(ANSI_COLOR_GREEN "[INTEGER COMPARISON PASSED] expected %d, got %d\n" ANSI_COLOR_RESET, minunit_tmp_e, minunit_tmp_r);\
    }\
)

/**
 * Asserts that two floating-point numbers are equal within epsilon.
 * Features:
 * - Handles floating-point comparison with epsilon
 * - Prints actual vs expected values with appropriate precision
 * - Returns detailed error message on failure
 * Usage: mu_assert_double_eq_verbose(expected, actual)
 */
#define mu_assert_double_eq_verbose(expected, result) MU__SAFE_BLOCK(\
    double minunit_tmp_e;\
    double minunit_tmp_r;\
    minunit_assert++;\
    minunit_tmp_e = (expected);\
    minunit_tmp_r = (result);\
    if (fabs(minunit_tmp_e-minunit_tmp_r) > MINUNIT_EPSILON) {\
        int minunit_significant_figures = 1 - log10(MINUNIT_EPSILON);\
        (void)snprintf(minunit_last_message, MINUNIT_MESSAGE_LEN, "%s failed:\n\t%s:%d: %.*g expected but was %.*g", __func__, __FILE__, __LINE__, minunit_significant_figures, minunit_tmp_e, minunit_significant_figures, minunit_tmp_r);\
        minunit_status = 1;\
        printf(ANSI_COLOR_RED "[DOUBLE COMPARISON FAILED] %s\n" ANSI_COLOR_RESET, minunit_last_message);\
        return minunit_last_message;\
    } else {\
        printf(ANSI_COLOR_GREEN "[DOUBLE COMPARISON PASSED] expected %g, got %g\n" ANSI_COLOR_RESET, minunit_tmp_e, minunit_tmp_r);\
    }\
)

/**
 * Asserts that two strings are equal.
 * Features:
 * - Handles NULL pointer cases
 * - Prints actual vs expected strings
 * - Returns detailed error message on failure
 * Usage: mu_assert_string_eq_verbose(expected, actual)
 */
#define mu_assert_string_eq_verbose(expected, result) MU__SAFE_BLOCK(\
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
        printf(ANSI_COLOR_RED "[STRING COMPARISON FAILED] %s\n" ANSI_COLOR_RESET, minunit_last_message);\
        return minunit_last_message;\
    } else {\
        printf(ANSI_COLOR_GREEN "[STRING COMPARISON PASSED] expected '%s', got '%s'\n" ANSI_COLOR_RESET, minunit_tmp_e, minunit_tmp_r);\
    }\
)

#endif /* MINUNIT_VERBOSE_H */
