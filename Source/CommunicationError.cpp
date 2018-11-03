#include "..\Include\CommunicationError.h"
#include <cstring>

namespace jed_utils
{
	CommunicationError::CommunicationError(const char *pErrMsg)
	{ 
		error_message = new char[strlen(pErrMsg) + 1];
		strcpy_s(error_message, strlen(pErrMsg) + 1, pErrMsg);
	}

	CommunicationError::~CommunicationError()
	{
		delete error_message;
	}

	const char *CommunicationError::what() const throw()
	{
		return error_message;
	}
}
