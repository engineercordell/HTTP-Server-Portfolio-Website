#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <string>
#include <fstream>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <thread>
#include <atomic>

enum class LogLevel
{
    DEBUG,
    INFO,
    WARNING,
    ERROR
};

struct LogMessage
{
    std::string message; // message contained here, no ref to anywhere else
    LogLevel level; // message severity
    std::chrono::system_clock::time_point timestamp; // time msg was logged to prevent delay when processing

    LogMessage(const std::string& msg, LogLevel lvl)
        : message{std::move(msg)}, level{lvl}, timestamp{std::chrono::system_clock::now()} {}
};

class Logger
{
private:
    Logger(); // should not be able to instantiate static obj
    ~Logger(); // should not be able to be manually deleted via 'delete'

    // assemble log msg string
    std::string format_message(const LogMessage& msg); 

    // log to terminal and/or file
    void log(LogLevel level, const std::string& msg); 
    
    // should strictly monitor the queue by popping and shifting the iterator
    void logging_thread_function();

    LogLevel current_level = LogLevel::DEBUG; // by default
    std::ofstream log_file; // be able to read from log_file stream if one choooses
    bool log_to_file = false;

    std::mutex log_mutex; // enable thread safety when writing to file
    std::condition_variable queue_cv; // control producer threads attempting to enqueue log messages
    std::queue<LogMessage> log_message_queue; 
    std::thread logger_thread; // consumer thread to process enqueued log messages
    std::atomic<bool> running;

public:
    static Logger& get(); // obtain Logger obj from anywhere without instantiation

    void set_level(LogLevel level); // user can set LogLevel for all messages
    void enable_file_output(const std::string& filename); // user can enable output to file 'filename'
    
    // public api to enqueue LogMessage
    void info(const std::string& msg); // user can log info msgs
    void error(const std::string& msg); // user can log errors msgs
    void debug(const std::string& msg); // user can log debug msgs
    void warning(const std::string& msg); // user can log warning msgs
};

#endif