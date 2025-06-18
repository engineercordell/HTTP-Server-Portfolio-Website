#ifndef HTTP_CONNECTION_SOCKET_HPP
#define HTTP_CONNECTION_SOCKET_HPP

#include "http_server_socket.hpp"

class HTTPConnectionSocket
{
private:
    int m_connect_fd { -1 };
    INetAddr m_client_addr;
    char m_buffer[4096];
    std::string m_request_buffer;

public:
    HTTPConnectionSocket(const HTTPServerSocket& server);
    ~HTTPConnectionSocket();

    HTTPConnectionSocket(HTTPConnectionSocket&& src) noexcept;
    HTTPConnectionSocket& operator=(HTTPConnectionSocket&& src) noexcept;

    HTTPConnectionSocket(const HTTPConnectionSocket&) = delete;
    HTTPConnectionSocket& operator=(const HTTPConnectionSocket&) = delete;

    int get_fd() const { return m_connect_fd; }
    char* get_buffer() { return m_buffer; }
    size_t get_buffer_size() const { return sizeof(m_buffer); }
    const INetAddr& get_client_addr() const { return m_client_addr; }
    const std::string& get_request_buffer() const { return m_request_buffer; }
    void add_to_request_buffer(ssize_t size) { m_request_buffer.append(static_cast<const char*>(m_buffer), static_cast<size_t>(size)); }
    bool request_complete() const { return m_request_buffer.find("\r\n\r\n") != std::string::npos; }
};

#endif