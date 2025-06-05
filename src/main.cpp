#include <iostream>
#include "http_server_socket.hpp"
#include "inet_addr.hpp"
#include "http_connection_socket.hpp"
#include "connection_handler.hpp"
#include <thread>

static constexpr int server_port = 8081;

int main()
{
    HTTPServerSocket server;
    INetAddr server_addr{server_port, "127.0.0.1"};
    server.bind_server(server_addr);
    server.listen_server();
    std::cout << "Number of concurrent threads: " << std::thread::hardware_concurrency() << '\n';
    
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

