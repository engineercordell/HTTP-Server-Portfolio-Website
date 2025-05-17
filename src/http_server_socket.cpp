#include "http_server_socket.hpp"
#include <stdexcept>
#include <unistd.h>

HTTPServerSocket::HTTPServerSocket(int domain, int type, int protocol)
    : m_domain { domain }
    , m_type { type }
    , m_protocol { protocol }
{
    m_server_fd = socket(m_domain, m_type, m_protocol);
    if (m_server_fd < 1)
    {
        throw std::runtime_error("Socket creation failed.");
    }
}

HTTPServerSocket::HTTPServerSocket()
    : HTTPServerSocket(AF_INET, SOCK_STREAM, 0)
{
}

HTTPServerSocket::~HTTPServerSocket()
{
    if (m_server_fd < 0) {
        throw std::runtime_error("Unable to close socket.");
    }
    ::close(m_server_fd);
}