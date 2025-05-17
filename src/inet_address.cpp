#include "inet_address.hpp"

INetAddr::INetAddr(short sin_family, uint16_t sin_port, std::string& ip_addr)
{
    m_address.sin_family = sin_family;
    m_address.sin_port = htons(sin_port);
    m_address.sin_addr.s_addr = inet_addr(ip_addr);
}