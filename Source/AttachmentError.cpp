#include "..\Include\AttachmentError.h"
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

	string AttachmentError::what() const throw()
	{
		return *mErrorMessage;
	}
}