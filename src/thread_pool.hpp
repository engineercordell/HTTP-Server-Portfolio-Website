#ifndef THREAD_POOL_HPP
#define THREAD_POOL_HPP

#include <functional>


class ThreadPool
{
private:



public:
    void start();
    void queue_job(const std::function<void()>& job);


};

#endif