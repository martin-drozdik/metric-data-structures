#ifndef ERROR_HANDLING_H
#define ERROR_HANDLING_H

#include <exception>
#include <cassert>
#include <iostream>

/// Implementation of the assert macros was inspired by:
/// http://cnicholson.net/2009/02/stupid-c-tricks-adventures-in-assert/

void handleError()
{
    std::cout << "Assertion failed." << std::endl;
    std::terminate();
}

#define REMOVE_UNUSED_VARIABLE_WARNING(condition) \
    do { (void)sizeof(condition); } while(0)

#ifdef CHECKING
#define MC_ASSERT(condition) \
    do \
    { \
        if (!(condition)) \
        { \
            handleError(); \
        } \
    } while(0)
#else
#define MC_ASSERT(condition) \
    REMOVE_UNUSED_VARIABLE_WARNING(0)
#endif

#endif // ERROR_HANDLING_H
