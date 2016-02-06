#pragma once

#include <string>
#include <stdexcept>

namespace Utils
{

class DuplicateItemException : public std::runtime_error
{
public:
    DuplicateItemException(const std::string& what)
        : std::runtime_error(what)
    {
    }
};

} // namespace Utils

