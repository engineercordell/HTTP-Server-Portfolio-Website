#ifndef CONFIG_H
#define CONFIG_H

#include <filesystem>

namespace Config
{
    // Define own base path to where static web pages live based on WSL file system
    const std::filesystem::path base_dir{ "/home/ceejay/web-server/public" };
    
}

#endif