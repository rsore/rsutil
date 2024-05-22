#ifndef RSUTIL_ASSERT_HPP
#define RSUTIL_ASSERT_HPP

#include <cassert>
#include <string>

namespace rsutil
{
    constexpr void dynamic_assert(bool, const std::string & = "");
}

constexpr void
rsutil::dynamic_assert([[maybe_unused]] const bool expr, [[maybe_unused]] const std::string &msg)
{
#if RSUTIL_ENABLE_DYNAMIC_ASSERT == 1
    assert(expr && msg.c_str());
#endif
}

#endif