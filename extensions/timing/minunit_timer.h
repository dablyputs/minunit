#ifndef MINUNIT_TIMER_H
#define MINUNIT_TIMER_H

#include <time.h>
#include "minunit.h"

/* Timing variables */
static double minunit_real_timer = 0;
static double minunit_proc_timer = 0;

/**
 * Returns the real time, in seconds, or -1.0 if an error occurred.
 * 
 * Time is measured since an arbitrary and OS-dependent start time.
 * The returned real time is only useful for computing an elapsed time
 * between two calls to this function.
 * 
 * Uses POSIX clock_gettime with CLOCK_MONOTONIC for high-resolution,
 * monotonic timing across platforms. This provides microsecond
 * resolution and is not affected by system time changes.
 * 
 * @return The current real time in seconds, or -1.0 if an error occurred
 */
static double mu_timer_real(void)
{
    struct timespec ts;
    if (clock_gettime(CLOCK_MONOTONIC, &ts) != -1) {
        return (double)ts.tv_sec + (double)ts.tv_nsec / 1000000000.0;
    }
    return -1.0;
}

/**
 * Returns the amount of CPU time used by the current process,
 * in seconds, or -1.0 if an error occurred.
 * 
 * Uses POSIX clock_gettime with CLOCK_PROCESS_CPUTIME_ID for
 * high-resolution CPU time measurement. This provides microsecond
 * resolution and is not affected by system load.
 * 
 * @return The CPU time used by the current process in seconds, or -1.0 if an error occurred
 */
static double mu_timer_cpu(void)
{
    struct timespec ts;
    if (clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &ts) != -1) {
        return (double)ts.tv_sec + (double)ts.tv_nsec / 1000000000.0;
    }
    return -1.0;
}

#endif /* MINUNIT_TIMER_H */
