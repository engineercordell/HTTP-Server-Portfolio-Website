#include <sstream>
#include "http_request_header.hpp"

std::optional<HTTPRequestHeaders> HTTPRequestHeaders::from_raw(std::string raw)
{
    try {
        HTTPRequestHeaders headers{raw};
        return headers;
    } catch (const std::exception& e) {
        std::cout << "Failed to parse request: " << e.what() << '\n';
        return std::nullopt;
    }
}

HTTPRequestHeaders::HTTPRequestHeaders(std::string request)
    : m_request {std::move(request)}
{
    parse_request_line();
    parse_headers();
}

void HTTPRequestHeaders::parse_request_line()
{
    std::string req_line = m_request.substr(0, m_request.find('\r'));

    // Retrieve method
    size_t start = 0;
    size_t end = m_request.find(' ');
    m_request_method = req_line.substr(start, end); // retrieves req_line[0, 3) = 'GET'

    // Retrieve target
    start = end + 1;
    end = req_line.find(' ', start);
    m_request_target = req_line.substr(start, end - start); // retrieves req_line[4, 5) = '\'

    // Retrieve protocol version
    start = end + 1;
    end = req_line.find('\r', start);
    m_protocol_vers = req_line.substr(start + 5, end - start); // retrives req_line[6, ...) = HTTP/1.1
}

void HTTPRequestHeaders::parse_headers()
{
    size_t start = m_request.find('\n') + 1;
    size_t end = m_request.find('\r', start);
    size_t header_end_boundary = m_request.find("\r\n\r\n");

    std::string header_line;
    std::string header;
    std::string value;
    size_t colon_idx;
    int i = 0;

    // Process headers
    while (end != std::string::npos && end <= header_end_boundary)
    {
        std::string header_line = m_request.substr(start, end - start); // first header line

        colon_idx = header_line.find(':');
        header = header_line.substr(0, colon_idx);

        value = header_line.substr(colon_idx + 2, end - colon_idx); // '+ 2' to exclude colon and space

        m_headers[header] = value;

        start = end + 2; // end 0: '\n' -> end 1: first char of next header
        end = m_request.find('\r', start);
        ++i;
    }
}