#include "StringUtils.h"

namespace Utils
{

const char* const StringUtils::s_whitespaces = "\t\n\r\f\v\b\a\0";

// trim from start
std::string StringUtils::ltrim(const std::string& in, const char* const t)
{
    return in.substr(in.find_first_not_of(t));
}

// trim from end
std::string StringUtils::rtrim(const std::string& in, const char* const t)
{
    return in.substr(0, in.find_last_not_of(t) + 1);
}

// trim all
std::string StringUtils::trim(const std::string& in, const char* const t)
{
    return ltrim(rtrim(in, t), t);
}

std::vector<std::string> StringUtils::split(const std::string& in, const char separator)
{
    std::vector<std::string> output;
    size_t lastPos = 0;

    if (!in.empty())
    {
        while (true)
        {
            size_t nextPos = in.find(separator, lastPos);

            if (nextPos == std::string::npos)
            {
                break; // no more separators
            }
            else
            {
                output.push_back(in.substr(lastPos, nextPos - lastPos));
                lastPos = nextPos + 1;
            }
        }

        // if separator is in last posistion, add empty string at the end of vecotr
        // if there is no separator at all, vector will contain original string
        if (in.back() == separator)
            output.push_back(empty_string);
        else 
            output.push_back(in.substr(lastPos));
    }
    else
    {
        output.push_back(empty_string);
    }

    return output;
}


} // namespace Utils

