#include "Logger.hpp"

#include <iostream>
#include <chrono>
#include <iomanip>
#include <ctime>

Logger::Logger() {}

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
    if (log_file.is_open())
    {
        log_to_file = true;
    }
    // otherwise error, failed to open log, defaulting to false
}

void Logger::debug(const std::string& msg) { write(LogLevel::DEBUG, msg); }
void Logger::info(const std::string& msg) { write(LogLevel::INFO, msg); }
void Logger::warning(const std::string& msg) { write(LogLevel::WARNING, msg); }
void Logger::error(const std::string& msg) { write(LogLevel::ERROR, msg); }

std::string Logger::format_message(LogLevel level, const std::string& msg)
{
    auto now = std::chrono::system_clock::now();
    std::time_t current_time = std::chrono::system_clock::to_time_t(now);

    std::ostringstream string_output_buffer;

    // append time,
    string_output_buffer << "[" << std::put_time(std::localtime(&current_time), "%Y-%m-%d %H:%M:%S") << "]";


    switch (level) // append log level,
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

    string_output_buffer << msg; // and append message by user
    return string_output_buffer.str(); // output as string
}

void Logger::write(LogLevel level, const std::string& msg)
{
    if (level < current_level) return; // ignore everything below the current_level by returning

    std::string formatted = format_message(level, msg);

    std::lock_guard<std::mutex> lock(log_mutex);
    std::cout << formatted << std::endl; // output to terminal
    if (log_to_file && log_file.is_open())
    {
        log_file << formatted << std::endl;
    }
}