#include "http_response.hpp"
#include "mime.hpp"

std::string make_http_response(int status, const std::string& message)
{
    return 
        "HTTP/1.1 " + std::to_string(status) + " " + message + "\r\n"
        "Content-Type: text/plain\r\n"
        "Content-Length: " + std::to_string(message.length()) + "\r\n"
        "Connection: close\r\n"
        "\r\n" + message;
}

std::string make_success_http_response(const std::filesystem::path& path, const std::string& content)
{
    return 
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: " + get_mime_type(path) + "\r\n"
        "Content-Length: " + std::to_string(content.length()) + "\r\n"
        "Connection: close\r\n"
        "\r\n" + content;
}