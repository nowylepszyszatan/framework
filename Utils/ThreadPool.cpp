#include "ThreadPool.h"

namespace Utils
{

ThreadPool::ThreadPool(size_t pool_size)
{
    for (size_t i = 0; i < pool_size; i++)
        m_workers.emplace_back([this]
        {
            for (;;)
            {
                auto task = m_queue.pop();
                if (!task)
                    return; // use empty task to quit the worker
                task();
            }
        });
}

ThreadPool::~ThreadPool()
{
    for (size_t i = 0; i < m_workers.size(); i++) m_queue.push(Task());

    for (auto& worker : m_workers) worker.join();
}

void ThreadPool::submit(const Task& f)
{
    if (f)
        m_queue.push(f);
}

} // namespace Utils

