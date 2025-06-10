#ifndef CONNECTION_HANDLER_HPP
#define CONNECTION_HANDLER_HPP

#include "http_connection_socket.hpp"

void handle_connection(HTTPConnectionSocket&& connection);

#endif