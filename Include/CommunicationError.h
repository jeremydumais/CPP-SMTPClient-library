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
	class COMMUNICATIONERROR_API CommunicationError
	{
	public:
		CommunicationError(const char *pErrMsg);
		~CommunicationError();
		const char *what() const throw();
	private:
		char *error_message = nullptr;
	};
}

#endif