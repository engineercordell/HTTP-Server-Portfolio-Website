#ifndef HTTP_CONNECTION_SOCKET_HPP
#define HTTP_CONNECTION_SOCKET_HPP

#include "http_server_socket.hpp"

class HTTPConnectionSocket
{
private:
    int m_connect_fd{ -1 };
    INetAddr m_client_addr;
    char m_buffer[4096];

public:
    HTTPConnectionSocket(HTTPServerSocket& server);
    ~HTTPConnectionSocket();

    int get_fd() const { return m_connect_fd; }
    char* get_buffer() { return m_buffer; }
    size_t get_buffer_size() { return sizeof(m_buffer); }
};

#endif