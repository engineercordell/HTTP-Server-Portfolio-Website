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

public:
    INetAddr(short sin_family, unsigned short sin_port, std::string& ip_addr);

};

#endif