#include "stringutils.h"
#include <algorithm>
#include <cctype>
#include <locale>

using namespace std;
using namespace jed_utils;

//Trim from start 
string StringUtils::trimLeft(const string &pString) {
    string s = pString;
    s.erase(s.begin(), find_if(s.begin(), s.end(), [](int ch) {
                return !static_cast<bool>(std::isspace(ch));
                }));
    return s;
}

//Trim from end
string StringUtils::trimRight(const string &pString) 
{
    string s = pString;
    s.erase(find_if(s.rbegin(), s.rend(), [](int ch) {
                return !static_cast<bool>(std::isspace(ch));
                }).base(), s.end());
    return s;
}

// trim from both ends
string StringUtils::trim(const string &pString) 
{
    string s = pString;
    s = trimLeft(s);
    s = trimRight(s);
    return s;
}

