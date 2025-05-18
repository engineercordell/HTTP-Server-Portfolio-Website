#include <iostream>
#include <unistd.h>
#include <string>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include "server_socket.hpp"
#include "inet_address.hpp"
#include "connection_socket.hpp"

int main()
{
    constexpr const char* html = R"(
    <!DOCTYPE html>
    <html>
    <head>
        <title>Test Page</title>
        <link rel="stylesheet" href="/style.css">
        <script src="/script.js"></script>
    </head>
    <body>
        <h1>Welcome to my HTTP server!</h1> 
    </body>
    </html>
    )";

    std::string header = 
        "HTTP/1.0 200 OK\r\n"
        "Content-Type: text/html\r\n"
        "Content-Length:" + std::to_string(strlen(html)) + "\r\n"
        "\r\n";

    std::string response = header + html;
        
    // Create server socket
    HTTPServerSocket server;
    INetAddr server_addr { 8080, "127.0.0.1" };

    server.bind_server(server_addr);
    server.listen_server();
    
    HTTPConnectionSocket connection { server, server_addr };

    char buffer[30000] = {0};
    // while(recv(new_socket, buffer, sizeof(buffer), 0) > 0)
    // {
    //     std::cout << "Received request:\n" << buffer;
    // }
    recv(connection.get_fd(), buffer, sizeof(buffer), 0);
    std::cout << "Received request:\n" << buffer;
    
    send(connection.get_fd(), response.c_str(), response.length(), 0);
    std::cout << "Response sent.\n";

    return 0;
}