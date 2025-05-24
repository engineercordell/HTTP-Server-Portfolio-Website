#include "http_request_header.h"

HTTPRequestHeaders::HTTPRequestHeaders(std::string request)
    : m_request { std::move(request) }
{ 
    parse_request_line();
    parse_headers();
}

void HTTPRequestHeaders::parse_request_line()
{
    std::string req_line = m_request.substr(0, m_request.find('\r'));
    // note that the first non-char of each line begins at '\r' not '\n'
    // std::cout << "First line: " << req_line << '\n';

    // NOTE: Recognize that a custom request could break the entire sever..security issue
    size_t start = 0;
    size_t end = m_request.find(' '); // pos = 3
    m_request_method = req_line.substr(start, end); // retrieves req_line[0, 3) = 'GET'

    start = end + 1; // pos = 4
    end = req_line.find(' ', start); // pos = 5 
    // std::cout << "request_target end: " << end << '\n';
    m_request_target = req_line.substr(start, end - start); // retrieves req_line[4, 5) = '\'
    // std::cout << request_target << '\n';

    start = end + 1; // pos = 6
    end = req_line.find('\r', start); // pos = ...
    // The '+ 5' offset accounts for 'HTTP/' in protocol
    m_protocol_vers = std::stof(req_line.substr(start + 5, end - start)); // retrives req_line[6, ...) = HTTP/1.1
    std::cout << "Protocol Version: " << m_protocol_vers << '\n';
}

void HTTPRequestHeaders::parse_headers()
{
    
}