#ifndef HTTP_SERVER
#define HTTP_SERVER

#include <sys/socket.h>

class HTTPServerSocket
{
// An HTTP Server Socket should be defaulted to the following parameters
private:
    int m_domain{ AF_INET };
    int m_type{ SOCK_STREAM };
    int m_protocol{ 0 };
    int m_server_fd { -1 };

    // "...store addresses for the Internet address family. 
    // Values of this type shall be cast by applications to struct sockaddr for use with socket functions." - opengroup.org  

public:
    HTTPServerSocket();
    HTTPServerSocket(int domain, int type, int protocol);
    ~HTTPServerSocket();

    HTTPServerSocket(const HTTPServerSocket&) = delete;
    HTTPServerSocket& operator=(const HTTPServerSocket&) = delete;


};

#endif