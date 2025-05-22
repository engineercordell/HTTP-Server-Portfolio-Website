#include "http_server_socket.hpp"

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
    if (m_server_fd >= 0) {
        ::close(m_server_fd); // don't throw in destructor
    }
    
}

void HTTPServerSocket::bind_server(INetAddr& addr)
{
    if (bind(m_server_fd, addr.get_sock_addr(), addr.get_addrlen()) < 0)
    {
        std::runtime_error("bind() failed");
    }
}

void HTTPServerSocket::listen_server(int backlog)
{
    if (listen(m_server_fd, backlog) < 0)
    {
        std::runtime_error("listen() failed");
    }
    std::cout << "Listening on port...\n";
}