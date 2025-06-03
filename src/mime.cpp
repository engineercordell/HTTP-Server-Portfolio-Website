#include "mime.hpp"
#include <unordered_map>

std::string get_mime_type(const std::string& path)
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

    std::size_t dot_idx = path.rfind('.');
    if (dot_idx != std::string::npos)
    {
        std::string ext = path.substr(dot_idx);
        auto it = mime_map.find(ext);
        if (it != mime_map.end())
        {
            return it->second;
        }
    }

    return "application/octet-stream";
}