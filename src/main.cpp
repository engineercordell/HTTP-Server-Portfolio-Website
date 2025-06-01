#include <iostream>
#include <unistd.h>
#include <string>
#include <cstring>
#include <fstream>
#include <sstream>
#include "config.hpp"
#include "http_server_socket.hpp"
#include "inet_addr.hpp"
#include "http_connection_socket.hpp"
#include "http_request_header.hpp"

int main()
{
    // Create server socket
    HTTPServerSocket server;
    INetAddr server_addr { 8081, "127.0.0.1" };

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

        std::ofstream httpRequest("../build/HTTP Request.txt");
        if (httpRequest.is_open())
        {
            httpRequest << request_buffer;
            httpRequest.close();
            std::cout << "HTTP request saved to HTTP Request.txt" << '\n';
        }

        // Handle parsing HTTP request data here from the buffer..
        // ...but main should not be responsible for this
        // main should only be worried about whether the request succeeded.
        auto headers = HTTPRequestHeaders::from_raw(request_buffer);
        if (!headers)
        {
            continue;
        }

        std::string response;
        
        // Handle particular request method (GET, POST, etc.)
        // Might somehow consider refactoring this into enum switch
        if ((headers->get_request_method()).compare("GET") == 0)
        {
            std::cout << "Start servicing..." << '\n';

            // obtain request target
            std::filesystem::path request_target = headers->get_request_target(); // target is either '/' or '/../..' 
            
            // sanitize & validate request target
            if (!Config::is_within_base_dir(request_target)) {
                std::cerr << "Request target not within base directory.\n";
                // Could perhaps add some later logic in here to reject the connecting client in future requests
                // 403
                continue;
            }

            // map root path to homepage
            if (request_target == "/") {
                request_target = Config::root_path; // check if root is being accessed
            }
            
            std::ifstream web_file;
            try {
                web_file.open(request_target);
                if (!web_file.is_open()) {
                    throw std::runtime_error("File not found/could not be opened.\n");
                }
            } catch (const std::exception& e) {
                std::cerr << "Web page doesn't exist or cannot be opened: " << e.what() << '\n';
                // 404
                continue;
            }

            // web_content <-- web page data from server file
            std::stringstream web_page_file_buffer;
            web_page_file_buffer << web_file.rdbuf();
            std::string web_content = web_page_file_buffer.str();
            web_file.close();
            
            std::string header = 
            "HTTP/1.0 200 OK\r\n"
            "Content-Type: text/html\r\n"
            "Content-Length: " + std::to_string(web_content.length()) + "\r\n"
            "\r\n";

            response = header + web_content;
        }

        send(connection.get_fd(), response.c_str(), response.length(), 0);
        std::cout << "Response sent.\n";
    }

    return 0;
}