#pragma once

#include "ThreadSafeQueue.h"

#include <thread>

namespace Utils
{

typedef std::function<void()> Task;

class ThreadPool
{
private:
    ThreadSafeQueue<Task> m_queue;
    std::vector<std::thread> m_workers;

public:
    ThreadPool(size_t pool_size);
    ~ThreadPool();

    void submit(const Task& f);
};

} // namespace Utils

