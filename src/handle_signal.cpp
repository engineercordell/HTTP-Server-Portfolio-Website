#include "handle_signal.hpp"
#include "logger.hpp"

void handle_sigint(int)
{
    Logger::get().info("Caught SIGINT, shutting down gracefully...");

    std::exit(0);
}