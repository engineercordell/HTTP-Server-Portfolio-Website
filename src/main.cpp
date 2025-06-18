#include <iostream>
#include "http_server_socket.hpp"
#include "inet_addr.hpp"
#include "http_connection_socket.hpp"
#include "connection_handler.hpp"
#include "thread_pool.hpp"
#include "config.hpp"
#include "logger.hpp"

int main()
{
    HTTPServerSocket server;
    Logger::get().enable_file_output("log.txt");
    Logger::get().info("Server started");

    INetAddr server_addr{Config::server_port, Config::ip_addr};
    server.bind_server(server_addr);
    server.listen_server(Config::max_pending_connections);

    ThreadPool handle_conn_threads;
    
    while (true) 
    {
        HTTPConnectionSocket connection{server};

        auto conn_ptr = std::make_shared<HTTPConnectionSocket>(std::move(connection));

        handle_conn_threads.queue_job([conn_ptr]() mutable {
            handle_connection(std::move(*conn_ptr));
        });
    }
    return 0;
}