#include "thread_pool.hpp"
#include <thread>

const unsigned int ThreadPool::num_threads = std::thread::hardware_concurrency();

ThreadPool::ThreadPool()
{
    threads.reserve(num_threads); // allocate all needed mem upfront to prevent unnecessary reallocations
    for (size_t i = 0; i < num_threads; ++i)
    {
        threads.emplace_back(&ThreadPool::thread_loop, this);
    }
}