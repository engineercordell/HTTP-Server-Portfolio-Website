#ifndef HTTP_RESPONSE_HPP
#define HTTP_RESPONSE_HPP

#include <string>
#include <filesystem>

std::string make_http_response(int status, const std::string& message);
std::string make_success_http_response(const std::filesystem::path& path, const std::string& content);

#endif