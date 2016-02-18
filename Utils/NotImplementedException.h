#pragma once

#include <stdexcept>

namespace Utils
{
class NotImplementedException : public std::runtime_error
{
public:
    NotImplementedException(const std::string& msg)
        : std::runtime_error("NotImplementedException: " + msg)
    {
    }
};

} // namespace Utils

