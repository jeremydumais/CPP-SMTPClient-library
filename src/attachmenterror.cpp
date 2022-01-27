#include "attachmenterror.h"
#include <cstring>

using namespace jed_utils;

AttachmentError::AttachmentError(const char *pErrMsg)
    : mErrorMessage(nullptr)
{
    size_t msg_len = std::strlen(pErrMsg);
    mErrorMessage = new char[msg_len+1];
    std::strncpy(mErrorMessage, pErrMsg, msg_len);
    mErrorMessage[msg_len+1] = '\0';
}

AttachmentError::~AttachmentError()
{
    delete[] mErrorMessage;
}

//Copy constructor
AttachmentError::AttachmentError(const AttachmentError& other)
	: mErrorMessage(new char[std::strlen(other.mErrorMessage) + 1])
{
    std::strncpy(mErrorMessage, other.mErrorMessage, std::strlen(other.mErrorMessage) + 1);
	mErrorMessage[std::strlen(other.mErrorMessage)] = '\0';
}

//Assignment operator
AttachmentError& AttachmentError::operator=(const AttachmentError& other)
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
AttachmentError::AttachmentError(AttachmentError&& other) noexcept
	: mErrorMessage(other.mErrorMessage)
{
	// Release the data pointer from the source object so that the destructor 
	// does not free the memory multiple times.
	other.mErrorMessage = nullptr;
}

//Move assignement operator
AttachmentError& AttachmentError::operator=(AttachmentError&& other) noexcept
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

const char *AttachmentError::what() const noexcept 
{
    return mErrorMessage;
}
