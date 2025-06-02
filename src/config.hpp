#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <filesystem>
#include <string>

namespace Config
{
    // Define own base path to where static web pages live based on WSL file system
    const std::filesystem::path base_dir{ "/home/ceejay/web-server/public" };
    const std::string root_path { "/public/home/index.html" };

    bool is_within_base_dir(const std::filesystem::path& request) { return request.string().starts_with(base_dir.string()); }
}

#endif