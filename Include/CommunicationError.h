#include <stdexcept>
#include <string>

#pragma once  

#ifdef SMTPCLIENT_EXPORTS  
#define COMMUNICATIONERROR_API __declspec(dllexport)   
#else  
#define COMMUNICATIONERROR_API __declspec(dllimport)   
#endif  

namespace jed_utils
{
	class COMMUNICATIONERROR_API communication_error
	{
	public:
		communication_error(const std::string err_msg);
		~communication_error();
		const char *what() const throw();
	private:
		char *error_message = NULL;
	};
}
