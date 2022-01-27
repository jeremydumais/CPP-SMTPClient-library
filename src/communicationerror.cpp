#include "communicationerror.h"
#include <cstring>

using namespace jed_utils;

CommunicationError::CommunicationError(const char *pErrMsg)
    : mErrorMessage(nullptr)
{
    size_t msg_len = std::strlen(pErrMsg);
    mErrorMessage = new char[msg_len+1];
    std::strncpy(mErrorMessage, pErrMsg, msg_len);
    mErrorMessage[msg_len+1] = '\0';
}

CommunicationError::~CommunicationError()
{
    delete[] mErrorMessage;
}

//Copy constructor
CommunicationError::CommunicationError(const CommunicationError& other)
	: mErrorMessage(new char[std::strlen(other.mErrorMessage) + 1])
{
    std::strncpy(mErrorMessage, other.mErrorMessage, std::strlen(other.mErrorMessage) + 1);
	mErrorMessage[std::strlen(other.mErrorMessage)] = '\0';
}

//Assignment operator
CommunicationError& CommunicationError::operator=(const CommunicationError& other)
{
	if (this != &other)
	{
		delete[] mErrorMessage;
		//mErrorMessage
		mErrorMessage = new char[std::strlen(other.mErrorMessage) + 1];
        std::strncpy(mErrorMessage, other.mErrorMessage, std::strlen(other.mErrorMessage) + 1);
		mErrorMessage[std::strlen(other.mErrorMessage)] = '\0';
	}
	return *this;
}

//Move constructor
CommunicationError::CommunicationError(CommunicationError&& other) noexcept
	: mErrorMessage(other.mErrorMessage)
{
	// Release the data pointer from the source object so that the destructor 
	// does not free the memory multiple times.
	other.mErrorMessage = nullptr;
}

//Move assignement operator
CommunicationError& CommunicationError::operator=(CommunicationError&& other) noexcept
{
	if (this != &other)
	{
		delete[] mErrorMessage;
		// Copy the data pointer and its length from the source object.
		mErrorMessage = other.mErrorMessage;
		// Release the data pointer from the source object so that
		// the destructor does not free the memory multiple times.
		other.mErrorMessage = nullptr;
	}
	return *this;
}

const char *CommunicationError::what() const noexcept 
{
    return mErrorMessage;
}
