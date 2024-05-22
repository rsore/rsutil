#ifndef RSUTIL_ASSERT_HPP
#define RSUTIL_ASSERT_HPP

#include <cassert>
#include <string>

namespace rsutil
{
    constexpr void dynamic_assert(bool, const std::string & = "");
}

constexpr void
rsutil::dynamic_assert(const bool expr, const std::string &msg)
{
    assert(expr && msg.c_str());
}

#endif