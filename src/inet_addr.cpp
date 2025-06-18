#include "inet_addr.hpp"
#include <iostream>

INetAddr::INetAddr(uint16_t sin_port, const std::string& ip_addr)
    : m_ip_addr{ip_addr}
    , m_port{sin_port}
{
    m_address.sin_port = htons(sin_port);
    m_address.sin_family = AF_INET;
    inet_pton(AF_INET, ip_addr.c_str(), &m_address.sin_addr.s_addr);
}

INetAddr::INetAddr(const sockaddr_in& addr)
    : m_address{addr}
    , m_addrlen{sizeof(m_address)}
    , m_port{ntohs(addr.sin_port)}
{
    char ip_str[INET_ADDRSTRLEN] = {};
    if (!inet_ntop(AF_INET, &addr.sin_addr, ip_str, sizeof(ip_str)))
        throw std::runtime_error("inet_ntop failed | INetAddr constructor");

    m_ip_addr = std::string(ip_str);
}

INetAddr::INetAddr(INetAddr&& src) noexcept
    : m_address{src.m_address}
    , m_addrlen{src.m_addrlen}
    , m_ip_addr{std::move(src.m_ip_addr)}
    , m_port{src.m_port}
{
}

INetAddr& INetAddr::operator=(INetAddr&& src) noexcept
{
    if (this != &src)
    {
        m_address = src.m_address;
        m_addrlen = src.m_addrlen;
        m_ip_addr = std::move(src.m_ip_addr);
        m_port = src.m_port;
    }
    return *this;
}

std::ostream& operator<<(std::ostream& out, const INetAddr& addr)
{
    out << addr.get_ip() << ":" << addr.get_port();
    return out;
}