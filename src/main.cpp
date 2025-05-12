#include <iostream>
#include <unistd.h>
#include <string>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>

int main()
{
    char buffer[30000] = {0};

    std::string response = 
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/plain\r\n"
        "Content-Length: 13\r\n"
        "\r\n"
        "Hello World!\r\n";

    int server = socket(AF_INET, SOCK_STREAM, 0);
    if (server < 1)
    {
        perror("socket() failed.");
        return 1;
    }

    // "...store addresses for the Internet address family. 
    // Values of this type shall be cast by applications to struct sockaddr for use with socket functions." - opengroup.org
    struct sockaddr_in address; // created on stack
    constexpr int port{8080};

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

    return 0;
}