#ifndef REQUEST_HANDLER_HPP
#define REQUEST_HANDLER_HPP

#include <string>
#include "http_request_header.hpp"

std::string handle_request(HTTPRequestHeaders& headers);

#endif