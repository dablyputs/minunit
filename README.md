## MinUnit

Minunit is a minimal unit testing framework for C/C++ self-contained in a
single header file.

It provides a way to define and configure test suites and a few handy assertion
types.  It reports the summary of the number of tests run, number of assertions
and time elapsed.

Note that this project is based on:
http://www.jera.com/techinfo/jtns/jtn002.html

## Verbose Mode

This fork simply adds a verbose set of test macros with colored output similar to that of the check50 program from the Harvard CS50 intro to computer science class available on edx and at Harvard the college. My ADHD brain needs a little reward when I get something right.

## How to use Verbose Mode

The verbose mode provides detailed, color-coded output for each test and assertion. Here's a comprehensive example showing all verbose features:

```c
#include "minunit.h"

/* Basic verbose test */
MU_TEST_VERBOSE(test_basic_verbose) {
    mu_assert_verbose(1 == 1, "Basic assertion should pass");
    return NULL;  // Indicate success
}

/* Integer comparison test */
MU_TEST_VERBOSE(test_int_comparison_verbose) {
    int expected = 42;
    int actual = 42;
    mu_assert_int_eq_verbose(expected, actual);
    return NULL;
}

/* Double comparison test */
MU_TEST_VERBOSE(test_double_comparison_verbose) {
    double expected = 3.14159;
    double actual = 3.14159;
    mu_assert_double_eq_verbose(expected, actual);
    return NULL;
}

/* String comparison test */
MU_TEST_VERBOSE(test_string_comparison_verbose) {
    const char* expected = "Hello, World!";
    const char* actual = "Hello, World!";
    mu_assert_string_eq_verbose(expected, actual);
    return NULL;
}

/* Basic check test */
MU_TEST_VERBOSE(test_check_verbose) {
    mu_check_verbose(1 == 1);
    return NULL;
}

/* Explicit failure test */
MU_TEST_VERBOSE(test_failure_verbose) {
    mu_fail_verbose("This test is designed to fail");
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
}

int main(void) {
    /* Run the verbose test suite */
    MU_RUN_SUITE_VERBOSE(test_suite_verbose);
    
    /* Generate verbose report */
    MU_REPORT_VERBOSE();
    
    return MU_EXIT_CODE;
}
```

## Verbose Assertion Types

The verbose mode provides the following assertion types with detailed output:

- `mu_assert_verbose(condition, message)`: Basic assertion with pass/fail message
- `mu_check_verbose(condition)`: Simple condition check with pass/fail output
- `mu_assert_int_eq_verbose(expected, result)`: Integer comparison with value details
- `mu_assert_double_eq_verbose(expected, result)`: Double comparison with value details
- `mu_assert_string_eq_verbose(expected, result)`: String comparison with value details
- `mu_fail_verbose(message)`: Explicit failure with custom message

## Verbose Test Suite Features

- `MU_TEST_VERBOSE(test_name)`: Define a verbose test function
- `MU_RUN_TEST_VERBOSE(test)`: Run a verbose test
- `MU_RUN_SUITE_VERBOSE(suite_name)`: Run a verbose test suite
- `MU_REPORT_VERBOSE()`: Generate a verbose test report
- `MU_SUITE_CONFIGURE(setup, teardown)`: Configure setup/teardown for verbose tests

## Output Format

The verbose mode produces color-coded output (not shown in GitHub):

```
[SUITE] Running test_suite_verbose
[SETUP] Running test setup
[TEST] Running test_basic_verbose
[ASSERTION PASSED] Basic assertion should pass
[PASS] test_basic_verbose
[TEARDOWN] Running test teardown
[SETUP] Running test setup
[TEST] Running test_int_comparison_verbose
[INTEGER COMPARISON PASSED] expected 42, got 42
[PASS] test_int_comparison_verbose
[TEARDOWN] Running test teardown
[SETUP] Running test setup
[TEST] Running test_double_comparison_verbose
[DOUBLE COMPARISON PASSED] expected 3.14159, got 3.14159
[PASS] test_double_comparison_verbose
[TEARDOWN] Running test teardown
[SETUP] Running test setup
[TEST] Running test_string_comparison_verbose
[STRING COMPARISON PASSED] expected 'Hello, World!', got 'Hello, World!'
[PASS] test_string_comparison_verbose
[TEARDOWN] Running test teardown
[SETUP] Running test setup
[TEST] Running test_check_verbose
[CHECK PASSED] 1 == 1
[PASS] test_check_verbose
[TEARDOWN] Running test teardown
[SETUP] Running test setup
[TEST] Running test_failure_verbose
[FAIL] test_failure_verbose failed:
	verbose_minunit_example.c:41: This test is designed to fail
[FAIL] test_failure_verbose: test_failure_verbose failed:
	verbose_minunit_example.c:41: This test is designed to fail
[TEARDOWN] Running test teardown
[SETUP] Running test setup
[TEST] Running test_failing_assertions_verbose
[INTEGER COMPARISON FAILED] test_failing_assertions_verbose failed:
	verbose_minunit_example.c:47: expected 42 but got 43
[FAIL] test_failing_assertions_verbose: test_failing_assertions_verbose failed:
	verbose_minunit_example.c:47: expected 42 but got 43
[TEARDOWN] Running test teardown


=== Test Summary ===
Tests run: 7
Assertions: 7
Failures: 2

Finished in 0.00009029 seconds (real) 0.00008979 seconds (proc)
```

## How to use non-verbose tests

This is a minimal test suite written with minunit:

```c
#include "minunit.h"

MU_TEST(test_check) {
    mu_check(5 == 7);
}
MU_TEST_SUITE(test_suite) {
    MU_RUN_TEST(test_check);
}

int main(int argc, char *argv[]) {
    MU_RUN_SUITE(test_suite);
    MU_REPORT();
    return MU_EXIT_CODE;
}
```

Which will produce the following output:

```
F
test_check failed:
    readme_sample.c:4: 5 == 7

1 tests, 1 assertions, 1 failures

Finished in 0.00032524 seconds (real) 0.00017998 seconds (proc)
```

Check out `minunit_example.c` to see a complete example. Compile with something
like:

```
gcc minunit_example.c -lrt -lm -o minunit_example
```

Don't forget to add `-lrt` for the timer and `-lm` for linking the function `fabs`
used in `mu_assert_double_eq`.

## Setup and teardown functions

One can define setup and teardown functions and configure the test suite to run
them by using the macro `MU_SUITE_CONFIGURE` with within a `MU_TEST_SUITE`
declaration.

## Assertion types

`mu_check(condition)`: will pass if the condition is evaluated to `true`, otherwise
it will show the condition as the error message

`mu_fail(message)`: will fail and show the message

`mu_assert(condition, message)`: will pass if the condition is `true`, otherwise it
will show the failed condition and the message

`mu_assert_int_eq(expected, result)`: it will pass if the two numbers are
equal or show their values as the error message

`mu_assert_double_eq(expected, result)`: it will pass if the two values
are almost equal or show their values as the error message. The value of
`MINUNIT_EPSILON` sets the threshold to determine if the values are close enough.

`mu_assert_string_eq(expected, result)`: it will pass if the two strings are equal.

## Authors

David Siñuela Pastor <siu.4coders@gmail.com>
David Sewell <david.sewell+minunit@gmail.com>
