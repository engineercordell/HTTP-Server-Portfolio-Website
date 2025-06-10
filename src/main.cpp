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
    
    while (true) {
        // A connection is it's own independent, executing entity
        // The server's job is to:
            // 1. Listen for incoming connections
            // 2. Accept connections
            // 3. Handle accepted connections
        HTTPConnectionSocket connection { server };
        

        handle_connection(connection);
    }
    return 0;
}

