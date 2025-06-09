#ifndef THREAD_POOL_HPP
#define THREAD_POOL_HPP

#include <functional>
#include <thread>
#include <condition_variable>
#include <queue>


class ThreadPool
{
private:
    void thread_loop();

    std::queue<std::function<void()>> jobs; // Keep track of jobs
    std::vector<std::thread> threads; // Keep track of threads
    bool should_terminate = false;   // Should threads look for job or not
    std::mutex queue_mutex;          // Prevent data races from simultaneous access and modification
    std::condition_variable queue_mutex_condition;
    static const unsigned int num_threads;
    
public:
    ThreadPool();
    void queue_job(const std::function<void()>& job);
    void stop();
    void busy();

};

#endif