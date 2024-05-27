#ifndef RSUTIL_MATH_HPP
#define RSUTIL_MATH_HPP

#include <type_traits>

namespace rsutil
{

    template <typename integral, typename = std::enable_if_t<std::is_integral_v<integral>>>
    constexpr integral wrapping_mod(integral, integral);

}

template <typename integral, typename = std::enable_if_t<std::is_integral_v<integral>>>
constexpr integral
rsutil::wrapping_mod(const integral a, const integral b)
{
    return (a % b + b) % b;
}

#endif
