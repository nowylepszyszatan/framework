#pragma once

namespace Utils
{

template<class T>
class Singleton
{
public:
    static T& instance();

private:
    Singleton();
    Singleton(const Singleton&) = delete;
    const Singleton& operator=(const Singleton&) = delete;

    static T* s_instance;
};

template<class T>
T& Singleton<T>::instance()
{
    if (s_instance == nullptr)
    {
        s_instance = new T();
    }

    return s_instance;
}

} // namespace Utils

