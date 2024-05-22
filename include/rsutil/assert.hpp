#ifndef RSUTIL_ASSERT_HPP
#define RSUTIL_ASSERT_HPP

#include <cassert>
#include <exception>
#include <string>
#include <string_view>

namespace rsutil
{
#if RSUTIL_ENABLE_DYNAMIC_ASSERT == 1
    class assert_exception : public std::exception
    {
      public:
        explicit assert_exception(std::string_view);

        [[nodiscard]] const char *what() const noexcept override;

      private:
        std::string _message;
    };
#endif

    constexpr void dynamic_assert(bool, const std::string & = "");
} // namespace rsutil

#if RSUTIL_ENABLE_DYNAMIC_ASSERT == 1
inline rsutil::assert_exception::assert_exception(const std::string_view message)
    : _message{ "Dynamic assertion failed: " + std::string(message) }
{}

inline const char *
rsutil::assert_exception::what() const noexcept
{
    return _message.c_str();
}
#endif

constexpr void
rsutil::dynamic_assert([[maybe_unused]] const bool expr, [[maybe_unused]] const std::string &msg)
{
#if RSUTIL_ENABLE_DYNAMIC_ASSERT == 1
    if (!expr)
    {
        throw assert_exception(msg);
    }
#endif
}

#endif