#pragma once

#include "NotInstantiable.h"

#include <vector>
#include <string>

namespace Utils
{

const std::string empty_string = std::string();

// Static class providing some usefull utilities
// for stdLLstring manipulation.
// All input paramters are const, and as result
// new instance of string is returned.
class StringUtils : NotInstantiable
{
public:

    // String trimming methods. As defult they trim whitespaces
    // If second paramter is provided, different letters can be trimed.
    static std::string ltrim(const std::string& in, const char* const t = s_whitespaces);
    static std::string rtrim(const std::string& in, const char* const t = s_whitespaces);
    static std::string  trim(const std::string& in, const char* const t = s_whitespaces);

    // Split string into vector of strings
    // using provided separator.
    static std::vector<std::string> split(const std::string& in, const char separator);

private:
    static const char* const s_whitespaces;
};

} // namespace Utils

