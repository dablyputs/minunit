#include <stdio.h>
#include "../minunit.h"
#include "../extensions/verbose/minunit_verbose.h"
#include "../extensions/assertions/minunit_assert.h"
#include "../extensions/timing/minunit_timer.h"

/* Test setup and teardown functions */
static void setup(void) {
    printf("Setting up test environment...\n");
}

static void teardown(void) {
    printf("Cleaning up test environment...\n");
}

/* Basic verbose test examples */
MU_TEST_VERBOSE(test_check_verbose) {
    int x = 5;
    int y = 5;
    mu_check_verbose(x == y);
    return NULL;  /* Success */
}

MU_TEST_VERBOSE(test_fail_verbose) {
    mu_fail_verbose("This test is designed to fail");
    /* No need for return NULL here as mu_fail_verbose always returns */
}

MU_TEST_VERBOSE(test_assert_verbose) {
    int value = 42;
    mu_assert_verbose(value == 42, "Value should be 42");
    return NULL;  /* Success */
}

/* Extended assertion examples */
MU_TEST_VERBOSE(test_int_eq_verbose) {
    int expected = 42;
    int actual = 42;
    mu_assert_int_eq_verbose(expected, actual);
    return NULL;  /* Success */
}

MU_TEST_VERBOSE(test_double_eq_verbose) {
    double expected = 3.14159265359;
    double actual = 3.14159265359;
    mu_assert_double_eq_verbose(expected, actual);
    return NULL;  /* Success */
}

MU_TEST_VERBOSE(test_string_eq_verbose) {
    const char* expected = "Hello, World!";
    const char* actual = "Hello, World!";
    mu_assert_string_eq_verbose(expected, actual);
    return NULL;  /* Success */
}

/* Test suite */
MU_TEST_SUITE(test_suite) {
    /* Configure setup and teardown for all tests */
    MU_SUITE_CONFIGURE(setup, teardown);

    /* Run tests with verbose output */
    MU_RUN_TEST_VERBOSE(test_check_verbose);
    MU_RUN_TEST_VERBOSE(test_fail_verbose);
    MU_RUN_TEST_VERBOSE(test_assert_verbose);
    MU_RUN_TEST_VERBOSE(test_int_eq_verbose);
    MU_RUN_TEST_VERBOSE(test_double_eq_verbose);
    MU_RUN_TEST_VERBOSE(test_string_eq_verbose);
}

int main(int argc, char *argv[]) {
    /* Mark command line arguments as intentionally unused */
    UNUSED(argc);
    UNUSED(argv);

    /* Run the test suite with verbose output */
    MU_RUN_SUITE_VERBOSE(test_suite);

    /* Print verbose test results */
    MU_REPORT_VERBOSE();

    /* Return number of failures */
    return MU_EXIT_CODE;
}
