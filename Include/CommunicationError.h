#ifndef COMMUNICATIONERROR_H
#define COMMUNICATIONERROR_H

#include <stdexcept>

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
		communication_error(const char *err_msg);
		~communication_error();
		const char *what() const throw();
	private:
		char *error_message = nullptr;
	};
}

#endif