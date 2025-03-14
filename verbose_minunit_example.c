#include "minunit.h"

/* Non-verbose test
MU_TEST(test_example) {
    mu_assert(1 == 1, "1 should equal 1");
    mu_assert(2 == 2, "2 should equal 2");
}
*/

/* Verbose test */
MU_TEST_VERBOSE(test_example_verbose) {
    mu_assert_verbose(1 == 1, "1 should equal 1");
    mu_assert_verbose(2 == 2, "2 should equal 2");
    return NULL;  // Indicate success
}

MU_TEST_SUITE(test_suite) {
    //   MU_RUN_TEST(test_example);                  // Non-verbose test
    MU_RUN_TEST_VERBOSE(test_example_verbose);  // Verbose test
}

int main(void) {
    MU_RUN_SUITE(test_suite);
    MU_REPORT_VERBOSE();
    return MU_EXIT_CODE;
}
