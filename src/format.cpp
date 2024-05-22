#include <rsutil/format.hpp>

int
rsutil::extract_number(std::stringstream &ss)
{
    std::string str;
    char        ch;

    while (ss.get(ch))
    {
        if (isdigit(ch))
        {
            str += ch;
        }
        else
        {
            ss.putback(ch);
            break;
        }
    }

    if (str.empty())
    {
        return 0;
    }

    return std::stoi(str);
}

char
rsutil::extract_pad_char(std::stringstream &ss)
{
    char ch;
    ss.get(ch);
    if (isascii(ch) && !isdigit(ch))
    {
        return ch;
    }
    else
    {
        ss.putback(ch);
        return default_pad_char;
    }
}

std::optional<int>
rsutil::extract_precision(std::stringstream &ss)
{
    char ch;
    ss.get(ch);

    if (ch != '.')
    {
        ss.putback(ch);
        return std::nullopt;
    }

    const int precision = extract_number(ss);
    return precision;
}
