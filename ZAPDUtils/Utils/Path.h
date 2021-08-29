#pragma once

#include <string>

#if __has_include(<filesystem>)
#include <filesystem>
namespace fs = std::filesystem;
#else
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;
#endif

class Path
{
public:
	static std::string GetFileName(const std::string& input);
	static std::string GetFileNameWithoutExtension(const std::string& input);
	static std::string GetFileNameExtension(const std::string& input);
	static std::string GetPath(const std::string& input);
	static std::string GetDirectoryName(const fs::path& path);
};
