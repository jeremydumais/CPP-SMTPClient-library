#include "../Include/CommunicationError.h"
#include <cstring>

using namespace jed_utils;
using namespace std;

CommunicationError::CommunicationError(const string &pErrMsg)
    : mErrorMessage(pErrMsg)
{ 
}

const char *CommunicationError::what() const noexcept 
{
    return mErrorMessage.c_str();
}
