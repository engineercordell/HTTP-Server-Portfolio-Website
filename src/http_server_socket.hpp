#ifndef HTTP_SERVER_SOCKET_HPP
#define HTTP_SERVER_SOCKET_HPP

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
    int m_server_fd { -1 };

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