#include "http_request_header.h"

HTTPRequestHeaders::HTTPRequestHeaders(std::string request)
    : m_request { std::move(request) }
{ 
    m_first_line = m_request.substr(0, m_request.find('\n'));
    std::cout << "First line: " + m_first_line << '\n';
}