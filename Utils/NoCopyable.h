#pragma once

namespace Utils
{

class NoCopyable
{
protected:
    NoCopyable() {}
    ~NoCopyable() {}

private:
    NoCopyable(const NoCopyable&) = delete;
    const NoCopyable& operator=(const NoCopyable&) = delete;
};

} // namespace utils

