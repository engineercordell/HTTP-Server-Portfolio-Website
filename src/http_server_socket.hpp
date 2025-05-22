#ifndef HTTP_SERVER_SOCKET
#define HTTP_SERVER_SOCKET

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdexcept>
#include <unistd.h>
#include <iostream>
#include "inet_addr.hpp"

class HTTPServerSocket
{

private:
    // An HTTP Server Socket should be defaulted to the following parameters
    int m_domain{ AF_INET };
    int m_type{ SOCK_STREAM };
    int m_protocol{ 0 };
    int m_server_fd { -1 };

    // "...store addresses for the Internet address family. 
    // Values of this type shall be cast by applications to struct sockaddr for use with socket functions." - opengroup.org  

public:
    HTTPServerSocket();
    HTTPServerSocket(int domain, int type, int protocol);
    ~HTTPServerSocket();

    HTTPServerSocket(const HTTPServerSocket&) = delete;
    HTTPServerSocket& operator=(const HTTPServerSocket&) = delete;

    int get_fd() const { return m_server_fd; } 
    void bind_server(INetAddr& addr);
    void listen_server(int backlog = 3);
};

#endif