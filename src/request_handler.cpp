#include <filesystem>
#include <fstream>
#include <sstream>
#include "config.hpp"
#include "request_handler.hpp"
#include "http_request_header.hpp"
#include "http_response.hpp"
#include "logger.hpp"

std::string handle_request(HTTPRequestHeaders& headers)
{
    std::string method = headers.get_request_method();
    std::filesystem::path target = headers.get_request_target();

    Logger::get().info(
        "Received request: " + method + " " + 
        target.string() + " " + 
        "HTTP/" + headers.get_protocol_vers());

    // Handle particular request method (GET, POST, etc.)
    // Might somehow consider refactoring this into enum switch
    if (method == "GET")
    {
        // std::cout << "Start servicing..." << '\n';

        // obtain request target
        // std::cout << "Request target: " << target << '\n';

        // map root path to homepage
        if (target == "/") target = "/home/index.html"; // check if root is being accessed
        
        std::filesystem::path full_path = std::filesystem::weakly_canonical(Config::base_dir / target.string().substr(1));
        // std::cout << "Full path: " << full_path << '\n';
        Logger::get().info("Serving file: " + full_path.string());

        // sanitize & validate request target
        if (!Config::is_within_base_dir(full_path))
        {
            Logger::get().warning("UNAUTHORIZED ACCESS DETECTED: " + full_path.string());
            return make_http_response(403, "Forbidden");
        }
        
        std::ifstream web_file{full_path};
        if (!web_file)
        {
            Logger::get().warning("Requested file not found: " + full_path.string());
            make_http_response(404, "Not Found.\n");
        }

        std::stringstream web_file_buffer; // create buffer to hold data for a web page stored in disk
        web_file_buffer << web_file.rdbuf(); // read data from web page to buffer
        web_file.close(); // close the web file

        return make_success_http_response(full_path, web_file_buffer.str());
    }

    Logger::get().warning("Request " + method + "not allowed");
    return make_http_response(405, "Method Not Allowed");
}