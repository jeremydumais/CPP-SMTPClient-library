#ifndef COMMUNICATIONERROR_H
#define COMMUNICATIONERROR_H

#include <stdexcept>
#include <string>

#ifdef _WIN32
	#ifdef SMTPCLIENT_EXPORTS  
		#define COMMUNICATIONERROR_API __declspec(dllexport)   
	#else  
		#define COMMUNICATIONERROR_API __declspec(dllimport)   
	#endif
#else
	#define COMMUNICATIONERROR_API
#endif

namespace jed_utils
{
	class COMMUNICATIONERROR_API CommunicationError
	{
	public:
		explicit CommunicationError(const std::string &pErrMsg);
		const std::string &what() const;
	private:
		std::string mErrorMessage;
	};
}

#endif
