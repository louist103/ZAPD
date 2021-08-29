#pragma once

#include <string>

#if __has_include(<filesystem>)
#include <filesystem>
namespace fs = std::filesystem;
#else
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;
#endif

#include "StringHelper.h"

class Directory
{
public:
	static std::string GetCurrentDirectory();
	static bool Exists(const fs::path& path);
	static void CreateDirectory(const std::string& path);
};
