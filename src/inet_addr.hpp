#ifndef INET_ADDR
#define INET_ADDR

#include <netinet/in.h>

class INetAddr
{
private:
    struct sockaddr_in m_address { AF_INET, INADDR_ANY }; // IPv4 interet domain socket address
    socklen_t m_addrlen = sizeof(m_address);
    
public:
    INetAddr();

};

#endif