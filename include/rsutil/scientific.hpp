#ifndef RSUTIL_SCIENTIFIC_HPP
#define RSUTIL_SCIENTIFIC_HPP

#include <rsutil/fundamental.hpp>

#include <array>

namespace rsutil
{

    enum class si_prefix
    {
        giga,
        mega,
        kilo,
        base,
        milli,
        micro,
        nano,

        _end_,
        _begin_ = giga
    };

    template <si_prefix, si_prefix, typename numeric>
    constexpr high_precision_float convert_si_prefix(numeric);
} // namespace rsutil

template <rsutil::si_prefix from, rsutil::si_prefix to, typename numeric>
constexpr rsutil::high_precision_float
rsutil::convert_si_prefix(const numeric amount)
{
    static_assert(std::is_floating_point_v<numeric> || std::is_integral_v<numeric>,
                  "[ rsutil::convert_si_prefix() ] numeric must be an integral or floating point type");

    static_assert(from != to, "[ rsutil::convert_si_prefix() ] Cannot convert to the same unit");

    constexpr auto unit_cnt = static_cast<std::size_t>(si_prefix::_end_) - static_cast<std::size_t>(si_prefix::_begin_);

    // clang-format off
        constexpr std::array<high_precision_float, unit_cnt> table{
            1.0 / 1000'000'000.0,
            1.0 / 1000'000.0,
            1.0 / 1000.0,
            1.0,
            1000.0,
            1000'000.0,
            1000'000'000.0
        };
    // clang-format on

    return amount * (table[static_cast<std::size_t>(to)] / table[static_cast<std::size_t>(from)]);
}

#endif
