#include "File.h"

#if __has_include(<filesystem>)
#include <filesystem>
namespace fs = std::filesystem;
#else
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;
#endif

#include <fstream>
#include <stdio.h>
#include <cstring>
#include <string>
#include <vector>
#include "StringHelper.h"

bool File::Exists(const fs::path& filePath)
{
	std::ifstream file(filePath, std::ios::in | std::ios::binary | std::ios::ate);
	return file.good();
}

std::vector<uint8_t> File::ReadAllBytes(const fs::path& filePath)
{
	std::ifstream file(filePath, std::ios::in | std::ios::binary | std::ios::ate);
	int32_t fileSize = (int32_t)file.tellg();
	file.seekg(0);
	char* data = new char[fileSize];
	file.read(data, fileSize);
	std::vector<uint8_t> result = std::vector<uint8_t>(data, data + fileSize);
	delete[] data;

	return result;
};

std::string File::ReadAllText(const fs::path& filePath)
{
	std::ifstream file(filePath, std::ios::in | std::ios::binary | std::ios::ate);
	int32_t fileSize = (int32_t)file.tellg();
	file.seekg(0);
	char* data = new char[fileSize + 1];
	memset(data, 0, fileSize + 1);
	file.read(data, fileSize);
	std::string str = std::string((const char*)data);
	delete[] data;

	return str;
};

std::vector<std::string> File::ReadAllLines(const fs::path& filePath)
{
	std::string text = ReadAllText(filePath);
	std::vector<std::string> lines = StringHelper::Split(text, "\n");

	return lines;
};

void File::WriteAllBytes(const fs::path& filePath, const std::vector<uint8_t>& data)
{
	std::ofstream file(filePath, std::ios::binary);
	file.write((char*)data.data(), data.size());
};

void File::WriteAllBytes(const std::string& filePath, const std::vector<char>& data)
{
	std::ofstream file(filePath, std::ios::binary);
	file.write((char*)data.data(), data.size());
};

void File::WriteAllBytes(const std::string& filePath, const char* data, int dataSize)
{
	std::ofstream file(filePath, std::ios::binary);
	file.write((char*)data, dataSize);
};

void File::WriteAllText(const fs::path& filePath, const std::string& text)
{
	std::ofstream file(filePath, std::ios::out);
	file.write(text.c_str(), text.size());
}
