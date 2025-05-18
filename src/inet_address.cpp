#include "inet_address.hpp"

INetAddr::INetAddr(uint16_t sin_port, const std::string& ip_addr)
{
    m_address.sin_family = AF_INET;
    m_address.sin_port = htons(sin_port);
    inet_pton(AF_INET, ip_addr.c_str(), &m_address.sin_addr.s_addr);
}