#ifndef RSUTIL_FUNDAMENTAL_HPP
#define RSUTIL_FUNDAMENTAL_HPP

#include <cstdint>

namespace rsutil
{
    using uint64 = std::uint64_t;
    using uint32 = std::uint32_t;
    using uint16 = std::uint16_t;
    using uint8  = std::uint8_t;

    using int64 = std::int64_t;
    using int32 = std::int32_t;
    using int16 = std::int16_t;
    using int8  = std::int8_t;

    using high_precision_float = long double;
    using float64              = double;
    using float32              = float;
} // namespace rsutil

static_assert(sizeof(rsutil::uint32) == 4);
static_assert(sizeof(rsutil::uint32) == 4);
static_assert(sizeof(rsutil::uint16) == 2);
static_assert(sizeof(rsutil::uint8) == 1);

static_assert(sizeof(rsutil::int64) == 8);
static_assert(sizeof(rsutil::int32) == 4);
static_assert(sizeof(rsutil::int16) == 2);
static_assert(sizeof(rsutil::int8) == 1);

static_assert(sizeof(rsutil::float64) == 8);
static_assert(sizeof(rsutil::float32) == 4);
static_assert(sizeof(rsutil::high_precision_float) >= sizeof(rsutil::float64));

#endif