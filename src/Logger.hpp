#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <string>
#include <fstream>
#include <mutex>

enum class LogLevel
{
    DEBUG,
    INFO,
    WARNING,
    ERROR
};

class Logger
{
private:
    Logger();
    std::string format_message(LogLevel level, const std::string& msg);
    void write(LogLevel level, const std::string& msg);

    LogLevel current_level = LogLevel::DEBUG; // by default
    std::ofstream log_file; // be able to read from log_file stream if one choooses
    bool log_to_file = false;
    std::mutex log_mutex; // enable thread safety when writing to file

public:
    static Logger& get(); // return reference to this single Logger obj

    void set_level(LogLevel level); // user can set LogLevel for all messages
    void enable_file_output(const std::string& filename); // user can enable output to a file named 'filename'

    void info(const std::string& msg); // user can log info msgs
    void error(const std::string& msg); // user can log errors msgs
    void debug(const std::string& msg); // user can log debug msgs
    void warning(const std::string& msg); // user can log warning msgs
};

#endif