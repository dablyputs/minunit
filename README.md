# MinUnit

Minunit is a minimal unit testing framework for C/C++ with a modular design and colored output support.

## Features

- Single header core (`minunit.h`)
- Modular extensions system
- Colored verbose output mode
- JTN002 compatibility mode
- Built-in timing utilities
- Cross-platform support
- No external dependencies

## Project Structure

```
minunit/
├── examples/                 # Example test files
│   ├── minunit_example.c    # Basic usage example
│   ├── verbose_example.c    # Verbose output example
│   └── jtn002_example.c     # JTN002 compatibility example
├── extensions/              # Modular extensions
│   ├── assertions/         # Enhanced assertion macros
│   ├── os/                # OS-specific functionality
│   ├── timing/            # Timer utilities
│   └── verbose/           # Verbose test output
├── minunit.h              # Core header file
└── Makefile              # Build system
```

## Quick Start

1. Copy `minunit.h` to your project
2. Include any desired extensions
3. Write your tests
4. Compile and run

```bash
# Build all examples
make all

# Run all examples
make run

# Clean build artifacts
make clean
```

## Basic Usage

```c
#include "minunit.h"

/* Define a test */
MU_TEST(test_check) {
    mu_check(5 == 5);
}

/* Define a test suite */
MU_TEST_SUITE(test_suite) {
    MU_RUN_TEST(test_check);
}

int main(int argc, char *argv[]) {
    UNUSED(argc);  /* Silence unused parameter warning */
    UNUSED(argv);  /* Silence unused parameter warning */

    MU_RUN_SUITE(test_suite);
    MU_REPORT();
    return MU_EXIT_CODE;
}
```

## Verbose Mode

For more detailed, colored output:

```c
#include "minunit.h"
#include "extensions/verbose/minunit_verbose.h"

/* Define a verbose test */
MU_TEST_VERBOSE(test_check_verbose) {
    mu_check_verbose(5 == 5);
    return NULL;  /* Success */
}

/* Define a test suite */
MU_TEST_SUITE(test_suite) {
    MU_RUN_TEST_VERBOSE(test_check_verbose);
}

int main(int argc, char *argv[]) {
    UNUSED(argc);
    UNUSED(argv);

    MU_RUN_SUITE_VERBOSE(test_suite);
    MU_REPORT_VERBOSE();
    return MU_EXIT_CODE;
}
```

## JTN002 Compatibility

For compatibility with the original JTN002 style:

```c
#include "jtn002.h"

static char * test_foo() {
    mu_assert("error, foo != 7", foo == 7);
    return 0;
}

static char * all_tests() {
    mu_run_test(test_foo);
    return 0;
}

int main(int argc, char **argv) {
    UNUSED(argc);
    UNUSED(argv);

    char *result = all_tests();
    printf("%s\n", result ? result : "ALL TESTS PASSED");
    printf("Tests run: %d\n", tests_run);
    return result != 0;
}
```

## Available Macros

### Core Assertions
- `mu_check(condition)`
- `mu_fail(message)`
- `mu_assert(condition, message)`
- `mu_assert_int_eq(expected, result)`
- `mu_assert_double_eq(expected, result)`
- `mu_assert_string_eq(expected, result)`

### Verbose Assertions
- `mu_check_verbose(condition)`
- `mu_fail_verbose(message)`
- `mu_assert_verbose(condition, message)`
- `mu_assert_int_eq_verbose(expected, result)`
- `mu_assert_double_eq_verbose(expected, result)`
- `mu_assert_string_eq_verbose(expected, result)`

### Test Definition
- `MU_TEST(test_name)`
- `MU_TEST_VERBOSE(test_name)`
- `MU_TEST_SUITE(suite_name)`

### Test Running
- `MU_RUN_TEST(test)`
- `MU_RUN_TEST_VERBOSE(test)`
- `MU_RUN_SUITE(suite_name)`
- `MU_RUN_SUITE_VERBOSE(suite_name)`

### Setup and Teardown
- `MU_SUITE_CONFIGURE(setup_fun, teardown_fun)`

### Utilities
- `UNUSED(x)` - Silence unused parameter warnings

## Building

The project includes a Makefile with the following targets:

```bash
make all                    # Build all examples
make minunit_example       # Build basic example
make verbose_example      # Build verbose example
make jtn002_example      # Build JTN002 example
make run                  # Build and run all examples
make clean               # Remove build artifacts
```

## Authors

David Siñuela Pastor <siu.4coders@gmail.com>  
David Sewell <david.sewell+minunit@gmail.com>

## License

MIT License - See MIT-LICENSE.txt
