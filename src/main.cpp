#include <iostream>
#include <unistd.h>
#include <string>
#include <cstring>
#include <fstream>
#include <sstream>
#include "http_server_socket.hpp"
#include "inet_addr.hpp"
#include "http_connection_socket.hpp"
#include "http_request_header.hpp"

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

    // This entire I/O logic should probably be moved into the central while loop
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
    // std::cout << response << '\n';

    // Create server socket
    HTTPServerSocket server;
    INetAddr server_addr { 8091, "127.0.0.1" };

    server.bind_server(server_addr);
    server.listen_server();
    
    std::string request_buffer;
    ssize_t msg_size;
    char buffer[4096];

    while (true) {
        HTTPConnectionSocket connection { server };

        // Is there a concern that recv could potentially access data from different clients, which could accidentally bleed
        // together the data of multiple different requests?
        // Should each connection have access to their own buffer?

        // Perhaps that should be addressed later..

        while ((msg_size = recv(connection.get_fd(), buffer, sizeof(buffer), 0)) > 0) {
            // std::cout << "Received request:\n" << buffer;
            request_buffer.append(buffer, msg_size); // append 4096 chars from buffer to request_buffer
            if (request_buffer.find("\r\n\r\n") != std::string::npos) {
                break;
            }
        }

        std::ofstream httpRequest("HTTP Request.txt");
        if (httpRequest.is_open())
        {
            httpRequest << request_buffer;
            httpRequest.close();
            std::cout << "HTTP request saved to HTTP Request.txt" << std::endl;
        }

        // Handle parsing HTTP request data here from the buffer..
        try {
            HTTPRequestHeaders reqHeaders { request_buffer };
        } catch(const std::exception& e) {
            std::cerr << "Request error...\n";
            continue;
        }
        
        send(connection.get_fd(), response.c_str(), response.length(), 0);
        std::cout << "Response sent.\n";
    }

    return 0;
}