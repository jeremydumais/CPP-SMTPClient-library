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
		explicit AttachmentError(const std::string &pErrMsg);
		const char *what() const noexcept override;
	private:
		std::string mErrorMessage;
	};
} // namespace jed_utils

#endif
