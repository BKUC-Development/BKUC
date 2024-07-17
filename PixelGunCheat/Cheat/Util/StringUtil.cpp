#include "StringUtil.h"

#include <algorithm>

std::string StringUtil::StrLow(std::string str)
{
    std::ranges::transform(str, str.begin(), [](const unsigned char c){ return std::tolower(c); });
    return str;
}

std::wstring StringUtil::WStrLow(std::wstring str)
{
    std::ranges::transform(str, str.begin(), [](const unsigned char c){ return std::tolower(c); });
    return str;
}