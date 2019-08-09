#include "../Include/AttachmentError.h"
#include <cstring>

using namespace std;

namespace jed_utils
{
	AttachmentError::AttachmentError(const string &pErrMsg)
        : mErrorMessage(pErrMsg)
	{
	}

	const string &AttachmentError::what() const 
	{
		return mErrorMessage;
	}
}
