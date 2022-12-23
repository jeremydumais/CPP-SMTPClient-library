#ifndef STRINGUTILS_H
#define STRINGUTILS_H

#include <string>

#ifdef _WIN32
    #ifdef SMTPCLIENT_EXPORTS
        #define STRINGUTILS_API __declspec(dllexport)
    #else
        #define STRINGUTILS_API __declspec(dllimport)
    #endif
#else
    #define STRINGUTILS_API
#endif

namespace jed_utils {
/** @brief The StringUtils class provides string utility fonctions
*/
class STRINGUTILS_API StringUtils {
 public:
    /**
     *  @brief  Remove space at the beginning of a string and return the result.
     *  @param pString The string that will be processed.
     */
    static std::string trimLeft(const std::string &pString);

    /**
     *  @brief  Remove space at the end of a string and return the result.
     *  @param pString The string that will be processed.
     */
    static std::string trimRight(const std::string &pString);

    /**
     *  @brief  Remove space at both the beginning and end of a string and return the result.
     *  @param pString The string that will be processed.
     */
    static std::string trim(const std::string &pString);

    /**
     *  @brief  Convert a string to lowercase and return the result.
     *  @param pString The string that will be processed.
     */
    static std::string toLower(const std::string &pString);

    /**
     *  @brief  Convert a string to uppercase and return the result.
     *  @param pString The string that will be processed.
     */
    static std::string toUpper(const std::string &pString);
};
}  // namespace jed_utils


#endif  // STRINGUTILS_H
