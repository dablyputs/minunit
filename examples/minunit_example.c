#include <stdio.h>
#include "minunit.h"

/* Test setup and teardown functions */
static void setup(void) {
    printf("Setting up test environment...\n");
}

static void teardown(void) {
    printf("Cleaning up test environment...\n");
}

/* Basic test examples */
MU_TEST(test_check) {
    int x = 5;
    int y = 5;
    mu_check(x == y);
}

MU_TEST(test_fail) {
    mu_fail("This test is designed to fail");
}

MU_TEST(test_assert) {
    int value = 42;
    mu_assert(value == 42, "Value should be 42");
}

/* Test suite */
MU_TEST_SUITE(test_suite) {
    /* Configure setup and teardown for all tests */
    MU_SUITE_CONFIGURE(setup, teardown);

    /* Run tests */
    MU_RUN_TEST(test_check);
    MU_RUN_TEST(test_fail);
    MU_RUN_TEST(test_assert);
}

int main(int argc, char *argv[]) {
    /* Mark command line arguments as intentionally unused */
    UNUSED(argc);
    UNUSED(argv);

    /* Run the test suite */
    MU_RUN_SUITE(test_suite);

    /* Print test results */
    MU_REPORT();

    /* Return number of failures */
    return MU_EXIT_CODE;
}
