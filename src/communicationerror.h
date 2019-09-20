#ifndef COMMUNICATIONERROR_H
#define COMMUNICATIONERROR_H

#include <stdexcept>
#include <string>

namespace jed_utils
{
	class CommunicationError : std::exception
	{
	public:
		explicit CommunicationError(const char *pErrMsg);
		~CommunicationError() override;
		CommunicationError(const CommunicationError& other); //Copy constructor
        CommunicationError& operator=(const CommunicationError& other); //Copy assignment
		CommunicationError(CommunicationError&& other) noexcept; //Move constructor
		CommunicationError& operator=(CommunicationError&& other) noexcept; //Move assignement
		const char *what() const noexcept override;
	private:
	char *mErrorMessage;
	};
} // namespace jed_utils

#endif
