#ifndef HTTP_CONNECTION_SOCKET
#define HTTP_CONNECTION_SOCKET

#include "http_server_socket.hpp"

class HTTPConnectionSocket
{
private:
    int m_connect_fd{ -1 };
    INetAddr m_client_addr;

public:
    HTTPConnectionSocket(HTTPServerSocket& server);
    ~HTTPConnectionSocket();

    int get_fd() const { return m_connect_fd; } 
};

#endif