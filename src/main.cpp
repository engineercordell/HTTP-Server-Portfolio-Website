#include <iostream>
#include <unistd.h>
#include <string>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>

int main()
{
    std::string response = 
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/html\r\n"
        "Content-Length:" + std::to_string(response.length()) + "\r\n"
        "\r\n"
        "Testing!\r\n";

    int server = socket(AF_INET, SOCK_STREAM, 0);
    if (server < 1)
    {
        perror("socket() failed.");
        return 1;
    }

    // "...store addresses for the Internet address family. 
    // Values of this type shall be cast by applications to struct sockaddr for use with socket functions." - opengroup.org
    struct sockaddr_in address; // created on stack
    constexpr int port{8081};

    socklen_t addrlen = sizeof(address);
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);
    if (bind(server, (struct sockaddr*)&address, addrlen) < 0)
    {
        perror("bind() failed");
        return 1;
    }

    if (listen(server, 3) < 0)
    {
        perror("listen() failed");
        return 1;
    }

    std::cout << "Server listening on port " << port << "...\n";

    int new_socket;
    new_socket = accept(server, (struct sockaddr*)&address, &addrlen);
    if (new_socket < 0) {
        perror("accept() failed");
        return 1;
    }

    char buffer[30000] = {0};

    recv(new_socket, buffer, sizeof(buffer), 0);
    std::cout << "Received request:\n" << buffer;

    send(new_socket, response.c_str(), response.length(), 0);
    std::cout << "Response sent.\n";

    close(new_socket);
    close(server);
    return 0;
}