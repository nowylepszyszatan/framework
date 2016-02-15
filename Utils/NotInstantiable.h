#pragma once

namespace Utils
{

class NotInstantiable
{
private:
    NotInstantiable() = delete;
    NotInstantiable(const NotInstantiable&) = delete;
    NotInstantiable& operator= (const NotInstantiable&) = delete;
};

} // namespace Utils

