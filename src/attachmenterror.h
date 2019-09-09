#ifndef ATTACHMENTERROR_H
#define ATTACHMENTERROR_H

#include <stdexcept>
#include <string>

#ifdef _WIN32
	#ifdef SMTPCLIENT_EXPORTS  
		#define ATTACHMENTERROR_API __declspec(dllexport)   
	#else  
		#define ATTACHMENTERROR_API __declspec(dllimport)   
	#endif  
#else
	#define ATTACHMENTERROR_API
#endif

namespace jed_utils
{
	class ATTACHMENTERROR_API AttachmentError : std::exception
	{
	public:
		explicit AttachmentError(const char *pErrMsg);
		~AttachmentError() override;
		AttachmentError(const AttachmentError& other); //Copy constructor
                AttachmentError& operator=(const AttachmentError& other); //Copy assignment
		AttachmentError(AttachmentError&& other) noexcept; //Move constructor
		AttachmentError& operator=(AttachmentError&& other) noexcept; //Move assignement
		const char *what() const noexcept override;
	private:
		char *mErrorMessage;
	};
} // namespace jed_utils

#endif
