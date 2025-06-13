#include "thread_pool.hpp"
#include <thread>
#include <iostream>

const unsigned int ThreadPool::num_threads = std::thread::hardware_concurrency() / 2;

ThreadPool::ThreadPool()
{
    threads.reserve(num_threads); // allocate all needed mem upfront to prevent unnecessary reallocations
    for (size_t i = 0; i < num_threads; ++i)
    {
        threads.emplace_back(&ThreadPool::thread_loop, this, i);
        std::cout << "Thread " << i << " created.\n";
    }
}

void ThreadPool::thread_loop(int thread_idx)
{
    while (true)
    {
        std::function<void()> job;

        { // critical section
            std::unique_lock<std::mutex> lock(queue_mutex); // unlocks at end of scope
            queue_mutex_condition.wait(lock, [this, thread_idx] {
                std::cout << "Thread " << thread_idx << " waiting.\n";
                return !jobs.empty() || should_terminate; // either the queue is empty, or the thread should be terminated
                // if both false, unlocks mutex and puts thread to sleep (so other threads can push jobs)
                // sleep until notify_one() called
                // afterwards, predicate re-evaluated
                // pred must return true to repossess lock
            });
            // std::cout << "Thread not executing test.";

            if (should_terminate) return; // confirm that thread should be terminated

            job = jobs.front();
            jobs.pop();
        } // lock automatically unlock here

        job();
    }
}

void ThreadPool::queue_job(std::function<void()>&& job)
{
    { // critical section
        std::unique_lock<std::mutex> lock(queue_mutex);
        jobs.push(std::move(job));
    } // lock automatically unlocked here
    queue_mutex_condition.notify_one();
}

// called in main to allow thread threadpool to complete all tasks before calling destructor
bool ThreadPool::busy()
{
    bool pool_busy;
    { // critical section
        std::unique_lock<std::mutex> lock(queue_mutex);
        pool_busy = !jobs.empty();
    } // lock automatically unlocked here
    return pool_busy;
}

void ThreadPool::stop()
{
    {
        std::unique_lock<std::mutex> lock(queue_mutex);
        should_terminate = true;
    }
    queue_mutex_condition.notify_all();
    for (std::thread& active_thread : threads)
    {
        active_thread.join();
    }
    threads.clear();
}





