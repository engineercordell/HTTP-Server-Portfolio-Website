#include "logger.hpp"

#include <iostream>
#include <chrono>
#include <iomanip>
#include <ctime>
#include <thread>

void Logger::logging_thread_function()
{
    while (running)
    {
        std::unique_lock<std::mutex> lock{queue_mutex};
        // if not running or if queue isn't empty, return
        queue_cv.wait(lock, [this] { return !running || !log_message_queue.empty(); });

        // if empty, go back and wait
        while (!log_message_queue.empty())
        {
            LogMessage log = std::move(log_message_queue.front());
            log_message_queue.pop();
            lock.unlock();

            // obtain string of formatted msg
            std::string formatted = format_message(log);
            std::cout << formatted << std::endl; // output to terminal
            if (log_to_file && log_file.is_open())
            {
                log_file << formatted << std::endl;
            }

            lock.lock(); // reobtain lock to continue queue processing
        }
    }

    // if no longer running, flush remaining messages
    std::unique_lock<std::mutex> lock{queue_mutex};
    while (!log_message_queue.empty())
    {
        LogMessage log = std::move(log_message_queue.front());
        log_message_queue.pop();

        // obtain string of formatted msg
        std::string formatted = format_message(log);
        std::cout << formatted << std::endl; // output to terminal
        if (log_to_file && log_file.is_open())
        {
            log_file << formatted << std::endl;
        }
    }
}

Logger::Logger() 
    : logger_thread(&Logger::logging_thread_function, this)
    , running{true}
{
}

Logger::~Logger()
{
    if (log_file.is_open()) log_file.close(); // close file
    if (logger_thread.joinable()) logger_thread.join(); // wait for it to finish
    running = false;
    queue_cv.notify_all();
}

Logger& Logger::get()
{
    static Logger logger;
    return logger;
}

void Logger::set_level(LogLevel level)
{
    // threads wouldn't compete to set the level, so no need to mutex
    current_level = level;
}

void Logger::enable_file_output(const std::string& filename)
{
    log_file.open(filename, std::ios::app);
    if (log_file.is_open()) log_to_file = true;
    // otherwise error, failed to open log, defaulting to false
}

void Logger::log(LogLevel level, const std::string& msg)
{
    // ignore everything below the current_level by returning
    if (level < current_level) return;
    {
        std::lock_guard<std::mutex> lock{queue_mutex};
        LogMessage log{msg, level};
        log_message_queue.push(std::move(log)); // enqueue
    }
    queue_cv.notify_one();
}
void Logger::debug(const std::string& msg) { log(LogLevel::DEBUG, msg); }
void Logger::info(const std::string& msg) { log(LogLevel::INFO, msg); }
void Logger::warning(const std::string& msg) { log(LogLevel::WARNING, msg); }
void Logger::error(const std::string& msg) { log(LogLevel::ERROR, msg); }

std::string Logger::format_message(const LogMessage& msg)
{
    std::time_t current_time = std::chrono::system_clock::to_time_t(msg.timestamp);

    std::ostringstream string_output_buffer;
    // append time
    string_output_buffer << "[" << std::put_time(std::localtime(&current_time), "%m-%d-%Y %H:%M:%S") << "]";

    // append log level
    switch (msg.level) 
    {
        case LogLevel::DEBUG:
            string_output_buffer << " [DEBUG] ";
            break;
        case LogLevel::INFO:
            string_output_buffer << " [INFO] ";
            break;
        case LogLevel::WARNING:
            string_output_buffer << " [WARN] ";
            break;
        case LogLevel::ERROR:
            string_output_buffer << " [ERROR] ";
            break;
    }

    string_output_buffer << msg.message << '\n'; // and append message by user
    return string_output_buffer.str(); // output as string
}