#ifndef LOQ_QUEUE_HPP
#define LOG_QUEUE_HPP

#include <mutex>
#include <queue>
#include "logger.hpp"

// queue of log "messages" from different clients
// queue must maintain a variety of different strings

class LogQueue
{
private:
    std::queue<LogMessage> log_msg_queue{};

};

#endif