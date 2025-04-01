#include "minunit.h"

/* Example of a verbose test function */
MU_TEST_VERBOSE(test_basic_verbose) {
    mu_assert_verbose(1 == 1, "Basic assertion should pass");
    return NULL;  // Indicate success
}

/* Example of verbose integer comparison */
MU_TEST_VERBOSE(test_int_comparison_verbose) {
    int expected = 42;
    int actual = 42;
    mu_assert_int_eq_verbose(expected, actual);
    return NULL;
}

/* Example of verbose double comparison */
MU_TEST_VERBOSE(test_double_comparison_verbose) {
    double expected = 3.14159;
    double actual = 3.14159;
    mu_assert_double_eq_verbose(expected, actual);
    return NULL;
}

/* Example of verbose string comparison */
MU_TEST_VERBOSE(test_string_comparison_verbose) {
    const char* expected = "Hello, World!";
    const char* actual = "Hello, World!";
    mu_assert_string_eq_verbose(expected, actual);
    return NULL;
}

/* Example of verbose check */
MU_TEST_VERBOSE(test_check_verbose) {
    mu_check_verbose(1 == 1);
    return NULL;
}

/* Example of verbose failure */
MU_TEST_VERBOSE(test_failure_verbose) {
    mu_fail_verbose("This test is designed to fail");
    return NULL;
}

/* Example of a test that will fail with verbose output */
MU_TEST_VERBOSE(test_failing_assertions_verbose) {
    mu_assert_int_eq_verbose(42, 43);  // Will fail
    mu_assert_double_eq_verbose(3.14, 3.15);  // Will fail
    mu_assert_string_eq_verbose("Hello", "World");  // Will fail
    return NULL;
}

/* Test suite with setup and teardown */
static void setup(void) {
    printf(ANSI_COLOR_CYAN "[SETUP] Running test setup\n" ANSI_COLOR_RESET);
}

static void teardown(void) {
    printf(ANSI_COLOR_CYAN "[TEARDOWN] Running test teardown\n" ANSI_COLOR_RESET);
}

/* Test suite that runs all verbose tests */
MU_TEST_SUITE(test_suite_verbose) {
    /* Configure setup and teardown for the suite */
    MU_SUITE_CONFIGURE(setup, teardown);
    
    /* Run all verbose tests */
    MU_RUN_TEST_VERBOSE(test_basic_verbose);
    MU_RUN_TEST_VERBOSE(test_int_comparison_verbose);
    MU_RUN_TEST_VERBOSE(test_double_comparison_verbose);
    MU_RUN_TEST_VERBOSE(test_string_comparison_verbose);
    MU_RUN_TEST_VERBOSE(test_check_verbose);
    MU_RUN_TEST_VERBOSE(test_failure_verbose);
    MU_RUN_TEST_VERBOSE(test_failing_assertions_verbose);
}

int main(void) {
    /* Run the verbose test suite */
    MU_RUN_SUITE_VERBOSE(test_suite_verbose);
    
    /* Generate verbose report */
    MU_REPORT_VERBOSE();
    
    return MU_EXIT_CODE;
}
