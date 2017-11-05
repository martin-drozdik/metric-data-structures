#ifndef ARITHMETIC_UTILITIES_H
#define ARITHMETIC_UTILITIES_H

#include "arithmetic_definition.h"

#include <limits>

inline constexpr Real notAnumber()
{
    return std::numeric_limits<Real>::quiet_NaN();
}

inline constexpr Real positiveInfinity()
{
    return std::numeric_limits<Real>::infinity();
}

inline constexpr Real negativeInfinity()
{
    return -std::numeric_limits<Real>::infinity();
}

#endif // ARITHMETIC_UTILITIES_H
