#include "http_connection_socket.hpp"
#include <cstring>

HTTPConnectionSocket::HTTPConnectionSocket(const HTTPServerSocket& server)
{
    m_connect_fd = accept(server.get_fd(), m_client_addr.get_sock_addr(), m_client_addr.get_addrlen_ptr());
    if (m_connect_fd < 0)
    {
        std::runtime_error("accept() failed");
    }
    std::cout << "New client.\n";
}

HTTPConnectionSocket::HTTPConnectionSocket(HTTPConnectionSocket&& src) noexcept
    : m_connect_fd { src.m_connect_fd },
      m_client_addr { std::move(src.m_client_addr) }, // INetAddr needs move semantics
      m_request_buffer { std::move(src.m_request_buffer) }
{
    // Copy buffer for now
    std::memcpy(m_buffer, src.m_buffer, sizeof(src.m_buffer));

    // Invalid original conn obj socket
    src.m_connect_fd = -1;
}

HTTPConnectionSocket& HTTPConnectionSocket::operator=(HTTPConnectionSocket&& src) noexcept
{
    if (this != &src)
    {
        // Close current socket if needed
        if (m_connect_fd != -1)
        {
            ::close(m_connect_fd);
        }

        m_connect_fd = src.m_connect_fd;
        m_client_addr = std::move(src.m_client_addr);
        m_request_buffer = std::move(src.m_request_buffer);
        std::memcpy(m_buffer, src.m_buffer, sizeof(m_buffer));

        src.m_connect_fd = -1;
    }
    return *this;
}

HTTPConnectionSocket::~HTTPConnectionSocket()
{
    if (m_connect_fd >= 0) {
        ::close(m_connect_fd); // don't throw in destructor
    }   
}

