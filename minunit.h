/*
 * Copyright (c) 2012 David Siñuela Pastor, siu.4coders@gmail.com
 * Copyright (c) 2025 David Sewell, david.sewell+minunit@gmail.com
 * 
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 * 
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * This file is part of the minunit project, originally created by David Siñuela Pastor.
 * Modifications were made by David Sewell in 2025.
 */
#ifndef MINUNIT_MINUNIT_H
#define MINUNIT_MINUNIT_H

/* Feature test macros must come before any includes */
#if !defined(_POSIX_C_SOURCE) || _POSIX_C_SOURCE < 200809L
#define _POSIX_C_SOURCE 200809L
#endif

#if !defined(_XOPEN_SOURCE) || _XOPEN_SOURCE < 700
#define _XOPEN_SOURCE 700
#endif

#ifdef __cplusplus
	extern "C" {
#endif

#if defined(_WIN32)
#include <Windows.h>
#if defined(_MSC_VER) && _MSC_VER < 1900
  #define snprintf _snprintf
  #define __func__ __FUNCTION__
#endif

#elif defined(__unix__) || defined(__unix) || defined(unix) || (defined(__APPLE__) && defined(__MACH__))

#include <unistd.h>	/* POSIX flags */
#include <time.h>	/* clock_gettime(), time() */
#include <sys/time.h>	/* gethrtime(), gettimeofday() */
#include <sys/resource.h>
#include <sys/times.h>
#include <string.h>

/* Define clockid_t if it's not available */
#ifndef _CLOCKID_T_DEFINED_
#define _CLOCKID_T_DEFINED_
typedef int clockid_t;
#endif

#if defined(__MACH__) && defined(__APPLE__)
#include <mach/mach.h>
#include <mach/mach_time.h>
#endif

#if __GNUC__ >= 5 && !defined(__STDC_VERSION__)
#define __func__ __extension__ __FUNCTION__
#endif

#else
#error "Unable to define timers for an unknown OS."
#endif

#include <stdio.h>
#include <math.h>

/**
 * Macro to silence unused parameter warnings.
 * 
 * This macro is used to explicitly mark parameters as intentionally unused.
 * It works by casting the parameter to void, which is a no-op but tells the
 * compiler we're aware the parameter is unused.
 * 
 * Usage:
 *   void function(int used, int unused) {
 *       UNUSED(unused);  // Silence warning about unused parameter
 *       printf("%d\n", used);
 *   }
 * 
 * Benefits:
 * - Works with any C compiler
 * - Can be used with function pointers
 * - Can be used anywhere in the function body
 * - Makes intent clear to other developers
 * - Can be used for unused variables too
 */
#define UNUSED(x) ((void)(x))

/*  Maximum length of last message */
#define MINUNIT_MESSAGE_LEN 1024

/*  Misc. counters */
static int minunit_run = 0;
static int minunit_assert = 0;
static int minunit_fail = 0;
static int minunit_status = 0;

/*  Last message */
static char minunit_last_message[MINUNIT_MESSAGE_LEN];

/*  Test setup and teardown function pointers */
static void (*minunit_setup)(void) = NULL;
static void (*minunit_teardown)(void) = NULL;

/*  Definitions */
#define MU_TEST(method_name) static void method_name(void)
#define MU_TEST_SUITE(suite_name) static void suite_name(void)

#define MU__SAFE_BLOCK(block) do {\
    block\
} while(0)

/*  Run test suite and unset setup and teardown functions */
#define MU_RUN_SUITE(suite_name) MU__SAFE_BLOCK(\
    suite_name();\
    minunit_setup = NULL;\
    minunit_teardown = NULL;\
)

/*  Configure setup and teardown functions */
#define MU_SUITE_CONFIGURE(setup_fun, teardown_fun) MU__SAFE_BLOCK(\
    minunit_setup = setup_fun;\
    minunit_teardown = teardown_fun;\
)

/*  Test runner */
#define MU_RUN_TEST(test) MU__SAFE_BLOCK(\
    if (minunit_setup) (*minunit_setup)();\
    minunit_status = 0;\
    test();\
    minunit_run++;\
    if (minunit_status) {\
        minunit_fail++;\
        printf("F");\
        printf("\n%s\n", minunit_last_message);\
    }\
    (void)fflush(stdout);\
    if (minunit_teardown) (*minunit_teardown)();\
)

/*  Report */
#define MU_REPORT() MU__SAFE_BLOCK(\
    printf("\n\n%d tests, %d assertions, %d failures\n", minunit_run, minunit_assert, minunit_fail);\
)

/* Exit code for test programs */
#define MU_EXIT_CODE minunit_fail

/*  Basic assertions */
#define mu_check(test) MU__SAFE_BLOCK(\
    minunit_assert++;\
    if (!(test)) {\
        (void)snprintf(minunit_last_message, MINUNIT_MESSAGE_LEN, "%s failed:\n\t%s:%d: %s", __func__, __FILE__, __LINE__, #test);\
        minunit_status = 1;\
        printf("[CHECK FAILED] %s\n", minunit_last_message);\
    } else {\
        printf("[CHECK PASSED] %s\n", #test);\
    }\
)

#define mu_fail(message) MU__SAFE_BLOCK(\
    minunit_assert++;\
    (void)snprintf(minunit_last_message, MINUNIT_MESSAGE_LEN, "%s failed:\n\t%s:%d: %s", __func__, __FILE__, __LINE__, message);\
    minunit_status = 1;\
    printf("[FAIL] %s\n", minunit_last_message);\
)

#define mu_assert(test, message) MU__SAFE_BLOCK(\
    minunit_assert++;\
    if (!(test)) {\
        (void)snprintf(minunit_last_message, MINUNIT_MESSAGE_LEN, "%s failed:\n\t%s:%d: %s", __func__, __FILE__, __LINE__, message);\
        minunit_status = 1;\
        printf("[ASSERTION FAILED] %s\n", minunit_last_message);\
    } else {\
        printf("[ASSERTION PASSED] %s\n", message);\
    }\
)

#ifdef __cplusplus
}
#endif

#endif /* MINUNIT_MINUNIT_H */ 