#ifndef HTTP_CONNECTION
#define HTTP_CONNECTION

#include "server_socket.hpp"

class HTTPConnectionSocket
{
private:
    int m_connect_fd{ -1 };

public:
    HTTPConnectionSocket(HTTPServerSocket& server, INetAddr& addr);
    ~HTTPConnectionSocket();

    int get_fd() const { return m_connect_fd; } 
};

#endif