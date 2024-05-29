#ifndef RSUTIL_ASSERT_HPP
#define RSUTIL_ASSERT_HPP

#include <iostream>
#include <rsutil/file_system.hpp>
#include <rsutil/format.hpp>
#include <string>
#include <string_view>

#if RSUTIL_ENABLE_DYNAMIC_ASSERT

#    define RSUTIL_DYN_ASSERT(expr, msg) rsutil::dynamic_assert(expr, RSUTIL_CURRENT_SOURCE_LOCATION, msg)

namespace rsutil
{

    constexpr void dynamic_assert(bool, const source_location &, const std::string & = "") noexcept;

} // namespace rsutil

constexpr void
rsutil::dynamic_assert([[maybe_unused]] const bool expr, const source_location &loc,
                       [[maybe_unused]] const std::string &msg) noexcept
{
    if (!expr)
    {
        std::cout << format_string("[ {%} ( {%}:{%} ) ] Dynamic assertion failed: {%}", loc.function_name,
                                   loc.file_name, loc.line_number, msg);
        std::abort();
    }
}

#else

#    define RSUTIL_DYN_ASSERT(expr, msg)

#endif

#endif