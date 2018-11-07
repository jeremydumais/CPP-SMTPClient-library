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

	CommunicationError::CommunicationError(const CommunicationError &pItem)
	{
		mErrorMessage = new string(*pItem.mErrorMessage);
	}

	CommunicationError &CommunicationError::operator=(const CommunicationError &pErrMsg)
	{
		if (this != &pErrMsg)
		{
			delete mErrorMessage;
			mErrorMessage = new string(*pErrMsg.mErrorMessage);
		}
		return *this;
	}

	const string &CommunicationError::what() const throw()
	{
		return *mErrorMessage;
	}
}
