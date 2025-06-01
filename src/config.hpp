#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <filesystem>
#include <string>

namespace Config
{
    // Define own base path to where static web pages live based on WSL file system
    const std::filesystem::path base_dir{ "/home/ceejay/web-server/public" };
    const std::string root_path { "public/home/index.html" };

    bool is_within_base_dir(const std::filesystem::path& request)
    {
        std::cout << "Request relative: " << request.relative_path() << '\n';
        std::filesystem::path normalized_path = std::filesystem::canonical(base_dir / request.relative_path());
        std::cout << "Normalized path: " << normalized_path << '\n';
        if (normalized_path.string().rfind(base_dir.string(), 0) != 0) {
            return 0;
        }
        return 1;
    }
}

#endif