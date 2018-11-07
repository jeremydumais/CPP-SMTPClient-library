#include "AttachmentError.h"
#include <cstring>

using namespace std;

namespace jed_utils
{
	AttachmentError::AttachmentError(const string &pErrMsg)
	{
		mErrorMessage = new string(pErrMsg);
	}

	AttachmentError::~AttachmentError()
	{
		if (mErrorMessage)
			delete mErrorMessage;
	}

	AttachmentError::AttachmentError(const AttachmentError &pItem)
	{
		mErrorMessage = new string(*pItem.mErrorMessage);
	}

	AttachmentError &AttachmentError::operator=(const AttachmentError &pAttErr)
	{
		if (this != &pAttErr)
		{
			delete mErrorMessage;
			mErrorMessage = new string(*pAttErr.mErrorMessage);
		}
		return *this;
	}


	const string &AttachmentError::what() const throw()
	{
		return *mErrorMessage;
	}
}