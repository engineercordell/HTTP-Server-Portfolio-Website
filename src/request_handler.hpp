#ifndef REQUEST_HANDLER_HPP
#define REQUEST_HANDLER_HPP

#include "http_request_header.hpp"
#include <string>

std::string handle_request(HTTPRequestHeaders& headers);

#endif