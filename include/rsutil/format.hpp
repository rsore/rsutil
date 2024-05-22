#ifndef RSUTIL_FORMAT_HPP
#define RSUTIL_FORMAT_HPP

#include <iomanip>
#include <optional>
#include <sstream>
#include <string>

namespace rsutil
{
    constexpr char fmt_begin        = '{';
    constexpr char fmt_end          = '}';
    constexpr char pad_char_symbol  = '>';
    constexpr char arg_char_symbol  = '%';
    constexpr char default_pad_char = ' ';

    template <typename... Args>
    [[nodiscard]] std::string format_string(std::string_view, Args &&...);

    template <typename type>
    void format_arg(std::ostringstream &, std::string_view, type);

    [[nodiscard]] int                extract_number(std::stringstream &ss);
    [[nodiscard]] char               extract_pad_char(std::stringstream &ss);
    [[nodiscard]] std::optional<int> extract_precision(std::stringstream &ss);
} // namespace rsutil

template <typename... Args>
std::string
rsutil::format_string(const std::string_view fmt, Args &&...args)
{
    std::ostringstream oss;

    std::size_t start{};
    std::size_t pos{};

    auto process_argument = [&](auto &&arg)
    {
        pos = fmt.find(fmt_begin, start);
        oss << fmt.substr(start, pos - start);
        start = pos + 1;

        pos             = fmt.find(fmt_end, start);
        const auto rest = fmt.substr(start, pos - start);
        if (pos == std::string::npos)
        {
            oss << rest;
        }
        else
        {
            format_arg(oss, rest, arg);
            start = pos + 1;
        }
    };

    (process_argument(std::forward<Args>(args)), ...);

    oss << fmt.substr(start);

    return oss.str();
}

template <typename type>
void
rsutil::format_arg(std::ostringstream &oss, std::string_view fmt, type arg)
{
    std::stringstream ss(std::string(fmt.substr(0)));

    char ch;
    while (ss.get(ch))
    {
        if (ch == pad_char_symbol)
        {
            const char pad_char  = extract_pad_char(ss);
            const auto pad_width = extract_number(ss);
            oss << std::string(pad_width, pad_char);
        }
        else if (ch == arg_char_symbol)
        {
            const auto precision = extract_precision(ss);
            if (precision.has_value())
            {
                const std::streamsize initial_precision = oss.precision();
                oss << std::fixed << std::setprecision(precision.value());
                oss << arg;
                oss << std::setprecision(static_cast<int>(initial_precision));
                oss.unsetf(std::ios_base::fixed);
            }
            else
            {
                oss << arg;
            }
        }
        else
        {
            oss << ch;
        }
    }
}

#endif
