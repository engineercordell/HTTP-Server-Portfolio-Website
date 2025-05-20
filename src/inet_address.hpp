#ifndef INET_ADDR
#define INET_ADDR

#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string>

class INetAddr
{
private:
    struct sockaddr_in m_address{}; // IPv4 interet domain socket address
    socklen_t m_addrlen { sizeof(m_address) };

public:
    // sin_family should always be AF_INET since the class deals with IPv4 addr
    INetAddr(unsigned short sin_port, const std::string& ip_addr);
    INetAddr() = default; // No custom work need be done in default constructor

    const sockaddr* get_sock_addr() const {return reinterpret_cast<const sockaddr*>(&m_address); }
    sockaddr* get_sock_addr() { return reinterpret_cast<sockaddr*>(&m_address); } // const member function that should never manipulate the address of m_address
    socklen_t get_addrlen() { return m_addrlen; }
    socklen_t* get_addrlen_ptr() { return &m_addrlen; }
    uint16_t get_port() const { return m_address.sin_port; }
};

#endif