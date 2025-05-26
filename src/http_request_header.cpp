#include "http_request_header.hpp"
#include <sstream>

std::optional<HTTPRequestHeaders> HTTPRequestHeaders::from_raw(std::string raw)
{
    try {
        HTTPRequestHeaders headers { raw };
        return headers;
    } catch (const std::exception& e) {
        std::cout << "Failed to parse request: " << e.what() << '\n';
        return std::nullopt;
    }
}

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
    // std::cout << "Protocol Version: " << m_protocol_vers << '\n';
}

void HTTPRequestHeaders::parse_headers()
{
    size_t start = m_request.find('\n') + 1; // next line 0th idx
    // std::cout << "Initial start: " << start << '\n';

    size_t end = m_request.find('\r', start);
    // std::cout << "Initial end: " << end << '\n';

    size_t header_end_boundary = m_request.find("\r\n\r\n");

    std::string header_line;
    std::string header;
    std::string value;
    size_t colon_idx;
    int i = 0;

    while (end != std::string::npos && end <= header_end_boundary)
    {
        // Process header..
        std::string header_line = m_request.substr(start, end - start); // first header line
        // std::cout << "Header Line " << i << ": " << header_line << '\n';

        colon_idx = header_line.find(':');
        header = header_line.substr(0, colon_idx);
        // std::cout << "Header: " << header << '\n';

        value = header_line.substr(colon_idx + 2, end - colon_idx); // '+ 2' to exclude colon and space
        //std::cout << "Value: " << value << '\n';

        m_headers[header] = value;

        start = end + 2; // end 0: '\n' -> end 1: first char of next header
        end = m_request.find('\r', start);
        ++i;
    }
}