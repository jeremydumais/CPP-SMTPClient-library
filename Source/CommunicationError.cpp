#include "..\Include\CommunicationError.h"
#include <cstring>

using namespace std;

namespace jed_utils
{
	CommunicationError::CommunicationError(const string &pErrMsg)
	{ 
		mErrorMessage = new string(pErrMsg);
	}

	CommunicationError::~CommunicationError()
	{
		if (mErrorMessage)
			delete mErrorMessage;
	}

	const string &CommunicationError::what() const throw()
	{
		return *mErrorMessage;
	}
}
