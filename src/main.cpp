#include <iostream>
#include <unistd.h>
#include <string>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fstream>
#include <sstream>
#include "server_socket.hpp"
#include "inet_address.hpp"
#include "connection_socket.hpp"

int main()
{
    // constexpr const char* html = R"(
    // <!DOCTYPE html>
    // <html>
    // <head>
    //     <title>Test Page</title>
    //     <link rel="stylesheet" href="/style.css">
    //     <script src="/script.js"></script>
    // </head>
    // <body>
    //     <h1>Welcome to my HTTP server!</h1> 
    // </body>
    // </html>
    // )";

    std::ifstream htmlFile("public/html/main.html");
    if (!htmlFile.is_open()) {
        std::cerr << "Could not open file." << std::endl;
        return 1;
    }

    std::stringstream html_file_buffer;
    html_file_buffer << htmlFile.rdbuf();
    std::string htmlContent = html_file_buffer.str();
    htmlFile.close();

    std::string header = 
        "HTTP/1.0 200 OK\r\n"
        "Content-Type: text/html\r\n"
        "Content-Length: " + std::to_string(htmlContent.length()) + "\r\n"
        "\r\n";

    std::string response = header + htmlContent;
    std::cout << response << '\n';

    // Create server socket
    HTTPServerSocket server;
    INetAddr server_addr { 8080, "127.0.0.1" };

    server.bind_server(server_addr);
    server.listen_server();
    
    char buffer[30000] = {0};

    while (true) {
        HTTPConnectionSocket connection { server };

        recv(connection.get_fd(), buffer, sizeof(buffer), 0);
        std::cout << "Received request:\n" << buffer;
    
        send(connection.get_fd(), response.c_str(), response.length(), 0);
        std::cout << "Response sent.\n";

        std::ofstream httpResponse("HTTP Response.txt");
        if (httpResponse.is_open())
        {
            httpResponse << buffer;
            httpResponse.close();
            std::cout << "HTTP request saved to HTTP Response.txt" << std::endl;
        }
    }

    return 0;
}