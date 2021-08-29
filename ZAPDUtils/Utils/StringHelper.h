#pragma once

#include <cstring>
#include <stdarg.h>
#include <string>
#include <vector>

#ifndef __PRETTY_FUNCTION__
#ifdef _MSC_VER
#define __PRETTY_FUNCTION__ __FUNCSIG__
#else
#define __PRETTY_FUNCTION__ __func__
#endif
#endif

class StringHelper
{
public:
	static std::vector<std::string> Split(std::string s, const std::string& delimiter);
	static std::string Strip(std::string s, const std::string& delimiter);
	static std::string Replace(std::string str, const std::string& from, const std::string& to);
	static bool StartsWith(const std::string& s, const std::string& input);
	static bool Contains(const std::string& s, const std::string& input);
	static bool EndsWith(const std::string& s, const std::string& input);
	static std::string Sprintf(const char* format, ...);
	static std::string Implode(std::vector<std::string>& elements, const char* const separator);
	static int64_t StrToL(const std::string& str, int32_t base = 10);
	static std::string BoolStr(bool b);
	static bool HasOnlyDigits(const std::string& str);
};
