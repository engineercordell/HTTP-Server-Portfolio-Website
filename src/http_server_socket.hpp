#ifndef HTTP_SERVER
#define HTTP_SERVER

#include <sys/socket.h>
#include <netinet/in.h>

class HTTPServerSocket
{
private:
    int m_domain{};
    int m_type{};
    int m_protocol{};

public:
    inline HTTPServerSocket(int domain, int type, int protocol);

};

#endif