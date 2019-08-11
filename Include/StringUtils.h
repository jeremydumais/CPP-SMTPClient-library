#ifndef STRINGUTILS_H
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
} // namespace jed_utils


#endif // STRINGUTILS_H
