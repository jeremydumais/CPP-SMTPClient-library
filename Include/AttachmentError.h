#ifndef ATTACHMENTERROR_H
#define ATTACHMENTERROR_H

#include <stdexcept>

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
		AttachmentError(const char *pErrMsg);
		~AttachmentError();
		const char *what() const throw();
	private:
		char *mErrorMessage = nullptr;
	};
}

#endif
