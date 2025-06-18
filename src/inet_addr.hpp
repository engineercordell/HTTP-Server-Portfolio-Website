#ifndef INET_ADDR_HPP
#define INET_ADDR_HPP

#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string>

class INetAddr
{
private:
    sockaddr_in m_address{}; // IPv4 internet domain socket address
    socklen_t m_addrlen{sizeof(m_address)};
    std::string m_ip_addr;
    uint16_t m_port; 

public:
    // sin_family should always be AF_INET since the class deals with IPv4 addr
    INetAddr(unsigned short sin_port, const std::string& ip_addr);
    INetAddr(const sockaddr_in& addr);
    INetAddr() = default; // No custom work need be done in default constructor

    // moved-from INetAddr is still in a valid but unspecified state
    INetAddr(INetAddr&& src) noexcept;
    INetAddr& operator=(INetAddr&& src) noexcept;

    INetAddr(const INetAddr&) = delete;
    INetAddr& operator=(const INetAddr&) = delete;

    const sockaddr_in& get_sock_addr_in() const { return m_address; }
    const sockaddr* get_sock_addr() const { return reinterpret_cast<const sockaddr*>(&m_address); }
    sockaddr* get_sock_addr() { return reinterpret_cast<sockaddr*>(&m_address); } // const member function that should never manipulate the address of m_address
    socklen_t get_addrlen() { return m_addrlen; }
    socklen_t* get_addrlen_ptr() { return &m_addrlen; }
    const std::string& get_ip() const { return m_ip_addr; }
    uint16_t get_port() const { return m_port; }

    const std::string to_string() const { return m_ip_addr + ":" + std::to_string(m_port); }
    friend std::ostream& operator<<(std::ostream& out, const INetAddr& addr);
};

#endif