#include "logger.hpp"

#include <iostream>
#include <chrono>
#include <iomanip>
#include <ctime>
#include <thread>

void Logger::logging_thread_function()
{
    while (true)
    {
        std::cout << "Logger thread executing...\n";
        std::this_thread::sleep_for(std::chrono::seconds(3));

        std::unique_lock<std::mutex> lock{log_mutex};
        queue_cv.wait(lock, [this] {
            return !running || !log_message_queue.empty(); // if not running or if queue isn't empty, return
        });

        if(!running) break;

        // LogMessage log = std::move(log_message_queue.front());
        log_message_queue.pop();

        lock.unlock();
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
}

Logger& Logger::get()
{
    static Logger logger;
    return logger;
}

void Logger::set_level(LogLevel level)
{
    current_level = level;
}

void Logger::enable_file_output(const std::string& filename)
{
    log_file.open(filename, std::ios::app);
    if (log_file.is_open()) log_to_file = true;
    // otherwise error, failed to open log, defaulting to false
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
    string_output_buffer << "[" << std::put_time(std::localtime(&current_time), "%Y-%m-%d %H:%M:%S") << "]\n";

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

    string_output_buffer << msg.message; // and append message by user
    return string_output_buffer.str(); // output as string
}

void Logger::log(LogLevel level, const std::string& msg)
{
    // ignore everything below the current_level by returning
    if (level < current_level) return; 

    // obtain string of formatted msg
    LogMessage log{msg, level};
    std::string formatted = format_message(log);

    // mutex locked: thread logs to shared output file
    std::lock_guard<std::mutex> lock(log_mutex); // automatically unlocks when write() returns
    std::cout << formatted << std::endl; // output to terminal
    if (log_to_file && log_file.is_open())
    {
        log_file << formatted << std::endl;
    }
    // mutex unlocked
}