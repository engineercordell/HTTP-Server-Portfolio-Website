#include <iostream>
#include <csignal>
#include "http_server_socket.hpp"
#include "inet_addr.hpp"
#include "http_connection_socket.hpp"
#include "connection_handler.hpp"
#include "thread_pool.hpp"
#include "config.hpp"
#include "logger.hpp"
#include "handle_signal.hpp"

int main()
{
    // std::signal(SIGINT, handle_sigint);

    HTTPServerSocket server;
    // Logger::get().enable_file_output(Config::get_log_path());
    Logger::get().info("Server starting up on " + server.get_server_addr().to_string());

    server.listen_server(Config::max_pending_connections);
    // std::cout << server.get_server_addr() << '\n';

    ThreadPool handle_conn_threads;
    
    while (true) 
    {
        HTTPConnectionSocket connection{server};

        auto conn_ptr = std::make_shared<HTTPConnectionSocket>(std::move(connection));

        handle_conn_threads.queue_job([conn_ptr]() mutable {
            handle_connection(std::move(*conn_ptr));
        });
    }

    Logger::get().info("Shutting down server...");
    return 0;
}