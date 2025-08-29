#include "http_server_socket.hpp"

HTTPServerSocket::HTTPServerSocket(int domain, int type, int protocol)
{
    m_server_fd = socket(domain, type, protocol);
    if (m_server_fd < 1) throw std::runtime_error("Socket creation failed.\n");
    
    int opt = 1;
    setsockopt(m_server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    if (bind(m_server_fd, m_server_addr.get_sock_addr(), m_server_addr.get_addrlen()) < 0) throw std::runtime_error("bind() failed");
    
    sockaddr_in actual_addr{};
    socklen_t addrlen = sizeof(actual_addr);

    if (getsockname(m_server_fd, reinterpret_cast<sockaddr*>(&actual_addr), &addrlen) < 0)
        throw std::runtime_error("getsockname() failed\n");

    m_server_addr = INetAddr(actual_addr);
}

HTTPServerSocket::HTTPServerSocket()
    : HTTPServerSocket(AF_INET, SOCK_STREAM, 0)
{
}

HTTPServerSocket::~HTTPServerSocket()
{
    if (m_server_fd >= 0) ::close(m_server_fd); // don't throw in destructor
}

void HTTPServerSocket::listen_server(int backlog)
{
    if (listen(m_server_fd, backlog) < 0) throw std::runtime_error("listen() failed\n");
}