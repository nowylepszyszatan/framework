#pragma once

#include <queue>
#include <mutex>
#include <condition_variable>

namespace Utils
{

// Thread safe queue for msg sending purpose
template<typename T>
class ThreadSafeQueue
{
public:
    ThreadSafeQueue();
    ThreadSafeQueue(const int max_size);

    void push(const T& x);
    T pop();


private:
    std::queue<T> m_queue;
    std::mutex m_queue_mtx;
    std::condition_variable m_pop_cond;
    std::condition_variable m_push_cond;
    int m_max_size;
};


template <typename T>
ThreadSafeQueue<T>::ThreadSafeQueue() :
    m_max_size(1024)
{
}

template <typename T>
ThreadSafeQueue<T>::ThreadSafeQueue(const int max_size) :
    m_max_size(max_size)
{
}

template <typename T>
void ThreadSafeQueue<T>::push(const T& x)
{
    std::unique_lock<std::mutex> lock(m_queue_mtx);

    while (!(m_queue.size() < m_max_size))
        m_push_cond.wait(lock);

    m_queue.push(x);
    m_pop_cond.notify_one();
}

template <typename T>
T ThreadSafeQueue<T>::pop()
{
    std::unique_lock<std::mutex> lock(m_queue_mtx);

    while (m_queue.empty())
    {
        m_pop_cond.wait(lock);
    }

    T ret = m_queue.front();
    m_queue.pop();

    m_push_cond.notify_one();

    return ret;
}

} // namespace Utils


