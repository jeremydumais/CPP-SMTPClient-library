#ifndef COMMUNICATIONERROR_H
#define COMMUNICATIONERROR_H

#include <stdexcept>
#include <string>

namespace jed_utils
{
	class CommunicationError : std::exception
	{
	public:
		/**
		 *  @brief  Construct a new CommunicationError. 
		 *  @param pErrMsg The error message.
		 */
		explicit CommunicationError(const char *pErrMsg);
		
		/** The destructor of CommunicationError */
		~CommunicationError() override;
		
		/** CommunicationError copy constructor. */
		CommunicationError(const CommunicationError& other);
        
		/** CommunicationError copy assignment operator. */
		CommunicationError& operator=(const CommunicationError& other);

		/** CommunicationError move constructor. */
		CommunicationError(CommunicationError&& other) noexcept;

		/** CommunicationError move assignment operator. */
		CommunicationError& operator=(CommunicationError&& other) noexcept;

		/** Return a char array pointer containing the error message. */
		const char *what() const noexcept override;
	private:
	char *mErrorMessage;
	};
} // namespace jed_utils

#endif
