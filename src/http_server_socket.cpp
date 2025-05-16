#include "http_server_socket.hpp"

inline HTTPServerSocket::HTTPServerSocket(int domain, int type, int protocol)
    : m_domain { domain }
    , m_type { type }
    , m_protocol { protocol }
{}