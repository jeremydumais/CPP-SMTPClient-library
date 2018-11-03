#ifndef ATTACHMENTERROR_H
#define ATTACHMENTERROR_H

#include <stdexcept>
#include <string>

#ifdef SMTPCLIENT_EXPORTS  
#define ATTACHMENTERROR_API __declspec(dllexport)   
#else  
#define ATTACHMENTERROR_API __declspec(dllimport)   
#endif  

namespace jed_utils
{
	class ATTACHMENTERROR_API AttachmentError
	{
	public:
		AttachmentError(const std::string &pErrMsg);
		~AttachmentError();
		std::string what() const throw();
	private:
		std::string *mErrorMessage = nullptr;
	};
}

#endif
