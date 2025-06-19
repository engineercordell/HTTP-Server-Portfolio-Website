#ifndef THREAD_POOL_HPP
#define THREAD_POOL_HPP

#include <functional>
#include <thread>
#include <condition_variable>
#include <queue>
#include "http_connection_socket.hpp"

class ThreadPool
{
private:
    std::string m_thread_type;
    void thread_loop(int thread_idx);

    std::queue<std::function<void()>> jobs; // Keep track of jobs
    std::vector<std::thread> threads; // Keep track of threads
    bool should_terminate = false;   // Should threads look for job or not
    std::mutex queue_mutex;          // Prevent data races from simultaneous access and modification
    std::condition_variable queue_mutex_condition;
    static const unsigned int num_threads;
    
public:
    ThreadPool(const std::string& thread_type);
    void queue_job(std::function<void()>&& job);
    bool busy();
    void stop();
};

#endif