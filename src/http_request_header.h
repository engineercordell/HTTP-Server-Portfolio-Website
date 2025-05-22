#ifndef HTTP_REQUEST_HEADERS
#define HTTP_REQUEST_HEADERS

#include "http_connection_socket.hpp"
#include <unordered_map>

class HTTPRequestHeaders
{
private:
    std::string m_request{};
    std::string m_first_line{};
    std::unordered_map<std::string, std::string> m_headers{};

public:
    HTTPRequestHeaders(std::string request);


};

#endif