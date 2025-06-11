#include <iostream>
#include "http_server_socket.hpp"
#include "inet_addr.hpp"
#include "http_connection_socket.hpp"
#include "connection_handler.hpp"
#include "thread_pool.hpp"

constexpr int server_port = 8081;
constexpr int max_pending_connections = 12;
constexpr size_t pool_size = 12;

int main()
{
    HTTPServerSocket server;
    INetAddr server_addr{server_port, "127.0.0.1"};
    server.bind_server(server_addr);
    server.listen_server(max_pending_connections);
    ThreadPool threads;
    
    while (true) 
    {
        HTTPConnectionSocket connection { server };

        auto conn_ptr = std::make_shared<HTTPConnectionSocket>(std::move(connection));

        threads.queue_job([conn_ptr]() mutable {
            handle_connection(std::move(*conn_ptr));
        });
    }
    return 0;
}