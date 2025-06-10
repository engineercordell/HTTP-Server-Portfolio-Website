#include "connection_handler.hpp"
#include "http_request_header.hpp"
#include "request_handler.hpp"

void handle_connection(HTTPConnectionSocket&& connection)
{
    ssize_t msg_size;
    while ((msg_size = recv(connection.get_fd(), connection.get_buffer(), connection.get_buffer_size(), 0)) > 0) {
        // std::cout << "Received request:\n" << buffer;
        connection.add_to_request_buffer(msg_size);
        if (connection.request_complete()) break;
    }

    // Handle parsing HTTP request data here from the buffer..
    std::cout << "\n<-----REQ BUFFER----->\n" << connection.get_request_buffer();
    auto headers = HTTPRequestHeaders::from_raw(connection.get_request_buffer());
    if (!headers) return;

    std::string response = handle_request(*headers); // might also need to make this a member variable for each connection
    send(connection.get_fd(), response.c_str(), response.length(), 0);
    std::cout << "Response sent.\n";
}