#pragma once

#include <memory>
#include <mutex>

namespace Utils
{

template<class T>
class Singleton
{
public:
    static T& instance();

protected:
    inline explicit Singleton() 
    {
        s_instance = static_cast<T*>(this);
    };

private:

    Singleton(const Singleton<T>&) = delete;
    const Singleton<T>& operator=(const Singleton<T>&) = delete;

    static T* s_instance;
    static std::mutex s_mutex;
};

template<class T>
T& Singleton<T>::instance()
{
    std::lock_guard<std::mutex> lock(s_mutex);

    if (s_instance == nullptr)
    {
        s_instance = new T();
    }

    return s_instance;
}

template <class T> T* Singleton<T>::s_instance = nullptr;

} // namespace Utils

