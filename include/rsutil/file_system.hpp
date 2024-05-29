#ifndef RSUTIL_FILE_SYSTEM_HPP
#define RSUTIL_FILE_SYSTEM_HPP

#include <rsutil/fundamental.hpp>
#include <string_view>

#define RSUTIL_CURRENT_SOURCE_LOCATION                            \
    rsutil::source_location                                       \
    {                                                             \
        __FILE__, static_cast<rsutil::uint32>(__LINE__), __func__ \
    }

namespace rsutil
{

    struct source_location
    {
        std::string_view file_name;
        uint32           line_number;
        std::string_view function_name;
    };

} // namespace rsutil

#endif
