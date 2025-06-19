#include <unordered_map>
#include "mime.hpp"

std::string get_mime_type(const std::filesystem::path& path)
{
    static const std::unordered_map<std::string, std::string> mime_map = {
        { ".html", "text/html" },
        { ".css", "text/css" },
        { ".js", "application/javascript" },
        { ".ico", "image/x-icon" },
        { ".png", "image/png" },
        { ".jpg", "image/jpeg" },
        { ".jpeg", "image/jpeg" },
        { ".svg", "image/svg+xml" },
        { ".json", "application/json" },
        { ".txt", "text/plain" }
    };

    std::string ext = path.extension().string();
    auto it = mime_map.find(ext);
    return (it != mime_map.end()) ? it->second : "application/octet-stream";
}