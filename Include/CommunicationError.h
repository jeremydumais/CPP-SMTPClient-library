#include <stdexcept>
#include <string>

#pragma once  

#ifndef COMMUNICATIONERROR_EXPORTS  
#define COMMUNICATIONERROR_API __declspec(dllexport)   
#else  
#define COMMUNICATIONERROR_API __declspec(dllimport)   
#endif  

namespace jed_utils
{
	class COMMUNICATIONERROR_API communication_error : public std::exception
	{
	public:
		communication_error(const std::string err_msg);
		const char *what() const throw();
	private:
		std::string error_message;
	};
}
