#pragma once

#include "ThreadSafeQueue.h"

#include <thread>

namespace Utils
{

typedef std::function<void()> Task;

class ThreadPool
{
public:
    ThreadPool(size_t pool_size);
    ~ThreadPool();

    void submit(const Task& f);

private:
    ThreadSafeQueue<Task> m_queue;
    std::vector<std::thread> m_workers;
};

} // namespace Utils

