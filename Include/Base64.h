#ifndef BASE64UTILS_H
#define BASE64UTILS_H

#include <string>

namespace jed_utils
{
	std::string base64_encode(unsigned char const *, unsigned int len);
	std::string base64_decode(std::string const &s);
}

#endif