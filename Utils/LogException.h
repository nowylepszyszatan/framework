#pragma once

#include <stdexcept>

namespace Utils
{
class LogException : public std::runtime_error
{
public:
    LogException(const std::string& msg)
        : std::runtime_error("LogException: " + msg)
    {
    }
};

} // namespace Utils

