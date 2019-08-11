#include "../Include/AttachmentError.h"
#include <cstring>

using namespace jed_utils;
using namespace std;

AttachmentError::AttachmentError(const string &pErrMsg)
    : mErrorMessage(pErrMsg)
{
}

const char *AttachmentError::what() const noexcept 
{
    return mErrorMessage.c_str();
}
