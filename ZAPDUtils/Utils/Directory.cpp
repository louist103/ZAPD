#include "Directory.h"

#include <string>
#include <vector>
#include "StringHelper.h"

std::string Directory::GetCurrentDirectory()
{
	return fs::current_path().u8string();
}

bool Directory::Exists(const fs::path& path)
{
	return fs::exists(path);
}

void Directory::CreateDirectory(const std::string& path)
{
	std::string curPath = "";
	std::vector<std::string> split = StringHelper::Split(path, "/");

	for (std::string s : split)
	{
		curPath += s + "/";

		if (!Exists(curPath))
			fs::create_directory(curPath);
	}

	// fs::create_directory(path);
}
