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
	class ATTACHMENTERROR_API attachment_error
	{
	public:
		attachment_error(const char *err_msg);
		~attachment_error();
		const char *what() const throw();
	private:
		char *error_message = nullptr;
	};
}

#endif
