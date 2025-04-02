/* This is the original code written by John Brewer when he described 
his idea for a mininal C unit test framework that uses no memory 
allocation and should "work fine under almost any circumstance" and 
which could be used to do unit testing in a constrained environment such as
an embedded system written in C such as a BIOS, EEPROM, etc. 

Link: https://jera.com/techinfo/jtns/jtn002 

You may use the code in his tech note for any purpose, with the understanding 
that it comes with NO WARRANTY. 
*/

#ifndef JTN002_H
#define JTN002_H

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

#define mu_assert(message, test) do { if (!(test)) return message; } while (0)
#define mu_run_test(test) do { char *message = test(); tests_run++; \
                                if (message) return message; } while (0)
#define mu_run_suite(suite) do { char *message = suite(); tests_run++; \
                                if (message) return message; } while (0)

extern int tests_run;

#endif