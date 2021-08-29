#pragma once

#if __has_include(<filesystem>)
#include <filesystem>
namespace fs = std::filesystem;
#else
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;
#endif

#include <fstream>
#include <string>
#include <vector>

class File
{
public:
	static bool Exists(const fs::path& filePath);
	static std::vector<uint8_t> ReadAllBytes(const fs::path& filePath);
	static std::string ReadAllText(const fs::path& filePath);
	static std::vector<std::string> ReadAllLines(const fs::path& filePath);
	static void WriteAllBytes(const fs::path& filePath, const std::vector<uint8_t>& data);
	static void WriteAllBytes(const std::string& filePath, const std::vector<char>& data);
	static void WriteAllBytes(const std::string& filePath, const char* data, int dataSize);
	static void WriteAllText(const fs::path& filePath, const std::string& text);
};
