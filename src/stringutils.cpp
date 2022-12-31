#include "stringutils.h"
#include <algorithm>
#include <cctype>
#include <locale>

using namespace jed_utils;

// Trim from start
std::string StringUtils::trimLeft(const std::string &pString) {
    std::string s = pString;
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
                return !static_cast<bool>(std::isspace(ch));
                }));
    return s;
}

// Trim from end
std::string StringUtils::trimRight(const std::string &pString) {
    std::string s = pString;
    s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
                return !static_cast<bool>(std::isspace(ch));
                }).base(), s.end());
    return s;
}

// trim from both ends
std::string StringUtils::trim(const std::string &pString) {
    std::string s = pString;
    s = trimLeft(s);
    s = trimRight(s);
    return s;
}

std::string StringUtils::toLower(const std::string &pString) {
    std::string transformed_string { pString };
    std::transform(pString.begin(), pString.end(), transformed_string.begin(),
            [](unsigned char c){ return static_cast<char>(std::tolower(c)); });
    return transformed_string;
}

std::string StringUtils::toUpper(const std::string &pString) {
    std::string transformed_string { pString };
    std::transform(pString.begin(), pString.end(), transformed_string.begin(),
            [](unsigned char c){ return static_cast<char>(std::toupper(c)); });
    return transformed_string;
}
