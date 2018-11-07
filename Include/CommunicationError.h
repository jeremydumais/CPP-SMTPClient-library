#ifndef COMMUNICATIONERROR_H
#define COMMUNICATIONERROR_H

#include <stdexcept>
#include <string>

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
		explicit CommunicationError(const std::string &pErrMsg);
		~CommunicationError();
		CommunicationError(const CommunicationError &);
		CommunicationError &operator=(const CommunicationError &pErrMsg);
		const std::string &what() const throw();
	private:
		std::string *mErrorMessage = nullptr;
	};
}

#endif