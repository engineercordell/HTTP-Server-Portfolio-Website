#include "inet_addr.hpp"
#include <iostream>

INetAddr::INetAddr(uint16_t sin_port, const std::string& ip_addr)
{
    m_address.sin_port = htons(sin_port);
    m_address.sin_family = AF_INET;
    inet_pton(AF_INET, ip_addr.c_str(), &m_address.sin_addr.s_addr);
}

INetAddr::INetAddr(INetAddr&& src) noexcept
    : m_address{src.m_address},
      m_addrlen{src.m_addrlen}
{
}

INetAddr& INetAddr::operator=(INetAddr&& src) noexcept
{
    if (this != &src)
    {
        m_address = src.m_address;
        m_addrlen = src.m_addrlen;
    }
    return *this;
}