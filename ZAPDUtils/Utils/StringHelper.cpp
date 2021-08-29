#include "StringHelper.h"

#include <algorithm>
#include <cstring>
#include <numeric>
#include <stdarg.h>
#include <string>
#include <vector>

std::vector<std::string> StringHelper::Split(std::string s, const std::string& delimiter)
{
    std::vector<std::string> result;

    size_t pos = 0;
    std::string token;

    while ((pos = s.find(delimiter)) != std::string::npos)
    {
        token = s.substr(0, pos);
        result.push_back(token);
        s.erase(0, pos + delimiter.length());
    }

    if (s.length() != 0)
        result.push_back(s);

    return result;
}

std::string StringHelper::Strip(std::string s, const std::string& delimiter)
{
    size_t pos = 0;
    std::string token;

    while ((pos = s.find(delimiter)) != std::string::npos)
    {
        token = s.substr(0, pos);
        s.erase(pos, pos + delimiter.length());
    }

    return s;
}

std::string StringHelper::Replace(std::string str, const std::string& from, const std::string& to)
{
    size_t start_pos = str.find(from);

    if (start_pos == std::string::npos)
        return str;

    str.replace(start_pos, from.length(), to);
    return str;
}

bool StringHelper::StartsWith(const std::string& s, const std::string& input)
{
    return s.rfind(input, 0) == 0;
}

bool StringHelper::Contains(const std::string& s, const std::string& input)
{
    return s.find(input) != std::string::npos;
}

bool StringHelper::EndsWith(const std::string& s, const std::string& input)
{
    size_t inputLen = strlen(input.c_str());
    return s.rfind(input) == (s.size() - inputLen);
}

std::string StringHelper::Sprintf(const char* format, ...)
{
    char buffer[0x8000];
    // char buffer[0x800];
    std::string output = "";
    va_list va;

    va_start(va, format);
    vsprintf(buffer, format, va);
    va_end(va);

    output = buffer;
    return output;
}

std::string StringHelper::Implode(std::vector<std::string>& elements, const char* const separator)
{
    return std::accumulate(std::begin(elements), std::end(elements), std::string(),
                            [separator](std::string& ss, std::string& s) {
                                return ss.empty() ? s : ss + separator + s;
                            });
}

int64_t StringHelper::StrToL(const std::string& str, int32_t base)
{
    return std::strtoull(str.c_str(), nullptr, base);
}

std::string StringHelper::BoolStr(bool b) { return b ? "true" : "false"; }

bool StringHelper::HasOnlyDigits(const std::string& str)
{
    return std::all_of(str.begin(), str.end(), ::isdigit);
}
