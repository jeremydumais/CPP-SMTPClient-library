#if !defined(STRINGUTILS_H)
#define STRINGUTILS_H

#include <string>

namespace jed_utils
{
    class StringUtils
    {
    public:
        static std::string trimLeft(const std::string &pString);
        static std::string trimRight(const std::string &pString);
        static std::string trim(const std::string &pString);
    };
}


#endif // STRINGUTILS_H
