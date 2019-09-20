#ifndef ATTACHMENTERROR_H
#define ATTACHMENTERROR_H

#include <stdexcept>
#include <string>

namespace jed_utils
{
	class AttachmentError : std::exception
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
