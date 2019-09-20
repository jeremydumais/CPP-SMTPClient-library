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

namespace jed_utils
{
    class STRINGUTILS_API StringUtils
    {
    public:
        static std::string trimLeft(const std::string &pString);
        static std::string trimRight(const std::string &pString);
        static std::string trim(const std::string &pString);
    };
} // namespace jed_utils


#endif // STRINGUTILS_H
