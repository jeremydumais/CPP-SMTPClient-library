#ifndef ATTACHMENTERROR_H
#define ATTACHMENTERROR_H

#include <stdexcept>
#include <string>

namespace jed_utils
{
	class AttachmentError : std::exception
	{
	public:
		/**
		 *  @brief  Construct a new AttachmentError. 
		 *  @param pErrMsg The error message.
		 */
		explicit AttachmentError(const char *pErrMsg);

		/** The destructor of AttachmentError */
		~AttachmentError() override;

		/** AttachmentError copy constructor. */
		AttachmentError(const AttachmentError& other);
        
		/** AttachmentError copy assignment operator. */
		AttachmentError& operator=(const AttachmentError& other);

		/** AttachmentError move constructor. */
		AttachmentError(AttachmentError&& other) noexcept;

		/** AttachmentError move assignment operator. */
		AttachmentError& operator=(AttachmentError&& other) noexcept;

		/** Return a char array pointer containing the error message. */
		const char *what() const noexcept override;
	private:
		char *mErrorMessage;
	};
} // namespace jed_utils

#endif
