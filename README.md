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

This is a short example of the new verbose macro usage:

```c
#include "minunit.h"

/* Verbose test */
MU_TEST_VERBOSE(test_example_verbose) {
    mu_assert_verbose(1 == 1, "1 should equal 1");
    mu_assert_verbose(2 == 2, "2 should equal 2");
    return NULL;  // Indicate success
}

MU_TEST_SUITE(test_suite) {
    MU_RUN_TEST_VERBOSE(test_example_verbose);  // Verbose test
}

int main(void) {
    MU_RUN_SUITE(test_suite);
    MU_REPORT_VERBOSE();
    return MU_EXIT_CODE;
}
```

Which will produce color (cannot be displayed on github) output similar to:

```
[TEST] Running test_example_verbose...
[ASSERTION PASSED] 1 should equal 1
[ASSERTION PASSED] 2 should equal 2
[PASS] test_example_verbose

=== Test Summary ===
Tests run: 1
Assertions: 2
Failures: 0

Finished in 223199.39773168 seconds (real) 0.00055337 seconds (proc)
```

## How to use non-verbose tests

This is a minimal test suite written with minunit:

```c
#include "minunit.h"

MU_TEST(test_check) _check(5 == 7);
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

`mu_assert_string_eq(expected, resurt):` it will pass if the two strings are equal.

## Authors

David Siñuela Pastor <siu.4coders@gmail.com>
