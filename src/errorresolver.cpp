#include "errorresolver.h"

using namespace jed_utils;
using namespace std::literals::string_literals;

ErrorResolver::ErrorResolver(int pErrorCode)
    : mErrorCode(pErrorCode),
      mErrorMessage(""s)
{
    switch (mErrorCode) {
        case -1:
            mErrorMessage = "Unable to create the socket"s;
        break;
        case -2:
            mErrorMessage = "Unable to connect to the socket"s;
        break;
        case -3:
            mErrorMessage = "The connection attempt has timed out"s;
        break;
        case -4:
            mErrorMessage = "Unable to start WSA (Winsock)"s;
        break;
        case -5:
            mErrorMessage = "Unable to get address info (Winsock)"s;
        break;
        case -6:
            mErrorMessage = "Unable to get host by name"s;
        break;
        default:
            mErrorMessage = "No message correspond to this error code"s;
    }
}

int ErrorResolver::getErrorCode() const
{
    return mErrorCode;
}

const std::string &ErrorResolver::getErrorMessage() const
{
    return mErrorMessage;
}
