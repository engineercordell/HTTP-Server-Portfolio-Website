#include <iostream>
#include "http_server_socket.hpp"
#include "inet_addr.hpp"
#include "http_connection_socket.hpp"
#include "connection_handler.hpp"
#include "config.hpp"

int main()
{
    HTTPServerSocket server;
    INetAddr server_addr{Config::SERVER_PORT, "127.0.0.1"};
    server.bind_server(server_addr);
    server.listen_server();
    
    while (true) {
        HTTPConnectionSocket connection { server };
        handle_connection(connection);
    }
    return 0;
}

