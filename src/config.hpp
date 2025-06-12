#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <filesystem>
#include <string>

namespace Config
{
    constexpr int server_port = 8081;
    constexpr std::string ip_addr = "127.0.0.1";
    constexpr int max_pending_connections = 12;

    // Define own base path to where static web pages live based on WSL file system
    inline const std::filesystem::path base_dir{"/home/ceejay/web-server/public"};
    inline const std::string root_path{"/public/home/index.html"};
    
    inline bool is_within_base_dir(const std::filesystem::path& request) { return request.string().starts_with(base_dir.string()); }
}

#endif