#include "connection_socket.hpp"

HTTPConnectionSocket::HTTPConnectionSocket(HTTPServerSocket& server, INetAddr& addr)
{
    m_connect_fd = accept(server.get_fd(), addr.get_sock_addr(), addr.get_addrlen_ptr());
    if (m_connect_fd < 0)
    {
        std::runtime_error("accept() failed");
    }
    std::cout << "New client.\n";
}

HTTPConnectionSocket::~HTTPConnectionSocket()
{
    if (m_connect_fd >= 0) {
        ::close(m_connect_fd); // don't throw in destructor
    }   
}

