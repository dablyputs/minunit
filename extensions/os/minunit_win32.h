#ifndef MINUNIT_WIN32_H
#define MINUNIT_WIN32_H

#include "minunit.h"

/* Windows-specific includes */
#include <Windows.h>

/* Windows-specific compiler fixes
 * 
 * Microsoft Visual C++ (MSVC) versions before 2015 (v1900) have some differences
 * from standard C:
 * 
 * 1. snprintf: MSVC uses _snprintf instead of snprintf. This fix ensures
 *    consistent behavior across compilers by mapping _snprintf to snprintf.
 * 
 * 2. __func__: MSVC doesn't support the C99 __func__ macro. Instead, it uses
 *    __FUNCTION__. This fix provides the standard __func__ macro for older
 *    MSVC versions.
 */
#if defined(_MSC_VER) && _MSC_VER < 1900
    #define snprintf _snprintf
    #define __func__ __FUNCTION__
#endif

#endif /* MINUNIT_WIN32_H */
