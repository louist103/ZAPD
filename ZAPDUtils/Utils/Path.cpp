#include "Path.h"

#include <string>
#include "StringHelper.h"

std::string Path::GetFileName(const std::string& input)
{
	std::vector<std::string> split = StringHelper::Split(input, "/");
	return split[split.size() - 1];
}

std::string Path::GetFileNameWithoutExtension(const std::string& input)
{
	std::vector<std::string> split = StringHelper::Split(input, "/");
	return split[split.size() - 1].substr(0, split[split.size() - 1].find_last_of("."));
}

std::string Path::GetFileNameExtension(const std::string& input)
{
	return input.substr(input.find_last_of("."), input.length());
}

std::string Path::GetPath(const std::string& input)
{
	std::vector<std::string> split = StringHelper::Split(input, "/");
	std::string output = "";

	for (std::string str : split)
	{
		if (str.find_last_of(".") == std::string::npos)
			output += str + "/";
	}

	return output;
}

std::string Path::GetDirectoryName(const fs::path& path)
{
	return path.parent_path().u8string();
}
