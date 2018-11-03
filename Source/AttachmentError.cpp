#include "..\Include\AttachmentError.h"
#include <cstring>

namespace jed_utils
{
	AttachmentError::AttachmentError(const char *pErrMsg)
	{
		mErrorMessage = new char[strlen(pErrMsg) + 1];
		strcpy_s(mErrorMessage, strlen(pErrMsg) + 1, pErrMsg);
	}

	AttachmentError::~AttachmentError()
	{
		delete mErrorMessage;
	}

	const char *AttachmentError::what() const throw()
	{
		return mErrorMessage;
	}
}