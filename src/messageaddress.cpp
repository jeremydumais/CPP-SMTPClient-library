#include "messageaddress.h"
#include "stringutils.h"
#include <regex>
#include <stdexcept>
#include <string>

using namespace std;

using namespace jed_utils;

MessageAddress::MessageAddress(const string &pEmailAddress, const string &pDisplayName)
    : mEmailAddress(""), mDisplayName("")
{
    //Check if the email address is not empty or white spaces
    if (pEmailAddress.length() == 0 || StringUtils::trim(pEmailAddress).empty()) {
        throw invalid_argument("pEmailAddress");
    }
    //Check is the email address is valid
    if (!isEmailAddressValid(pEmailAddress)) {
        throw invalid_argument("pEmailAddress");
    }

    mEmailAddress = pEmailAddress;
    mDisplayName = pDisplayName;
}

bool MessageAddress::operator==(const MessageAddress &pMsgComp) const
{
    return (mEmailAddress == pMsgComp.mEmailAddress && 
            mDisplayName == pMsgComp.mDisplayName);
}

MessageAddress::operator string() const
{
    ostringstream retval;
    if (mDisplayName.empty()) {
        retval << mEmailAddress;
    }
    else {
        retval << mDisplayName << " <" << mEmailAddress << ">";
    }
    return retval.str();
}

const string &MessageAddress::getEmailAddress() const
{
    return mEmailAddress;
}

const string &MessageAddress::getDisplayName() const
{
    return mDisplayName;
}

bool MessageAddress::isEmailAddressValid(const string &pEmailAddress) const
{
    regex emailPattern("^[_a-z0-9-]+(.[_a-z0-9-]+)*@[a-z0-9-]+(.[a-z0-9-]+)*(.[a-z]{2,4})$");
    return regex_match(pEmailAddress, emailPattern);
}

