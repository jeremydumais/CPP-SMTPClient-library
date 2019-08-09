#include "../Include/CommunicationError.h"
#include <cstring>

using namespace std;

namespace jed_utils
{
	CommunicationError::CommunicationError(const string &pErrMsg)
        : mErrorMessage(pErrMsg)
	{ 
	}

	const string &CommunicationError::what() const 
	{
		return mErrorMessage;
	}
}
