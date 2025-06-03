#ifndef MIME_HPP
#define MIME_HPP

#include <string>
#include <filesystem>

std::string get_mime_type(const std::filesystem::path& path);

#endif