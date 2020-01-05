#include "messageaddress.h"
#include "stringutils.h"
#include <regex>
#include <stdexcept>
#include <string>

using namespace std;
using namespace jed_utils;

MessageAddress::MessageAddress(const char *pEmailAddress, const char *pDisplayName)
    : mEmailAddress(nullptr), mDisplayName(nullptr)
{
    string email_address { pEmailAddress };
    //Check if the email address is not empty or white spaces
    if (email_address.length() == 0 || StringUtils::trim(email_address).empty()) {
        throw invalid_argument("pEmailAddress");
    }
    //Check is the email address is valid
    if (!isEmailAddressValid(email_address)) {
        throw invalid_argument("pEmailAddress");
    }

    size_t email_len = strlen(pEmailAddress);
    mEmailAddress = new char[email_len+1];
    strncpy(mEmailAddress, pEmailAddress, email_len);
    mEmailAddress[email_len] = '\0';

    size_t name_len = strlen(pDisplayName);
    mDisplayName = new char[name_len+1];
    strncpy(mDisplayName, pDisplayName, name_len);
    mDisplayName[name_len] = '\0';
}

MessageAddress::~MessageAddress()
{
    delete[] mEmailAddress;
    delete[] mDisplayName;
}

//Copy constructor
MessageAddress::MessageAddress(const MessageAddress& other)
	: mEmailAddress(new char[strlen(other.mEmailAddress) + 1]),
      mDisplayName(new char[strlen(other.mDisplayName) + 1])
{
	strncpy(mEmailAddress, other.mEmailAddress, strlen(other.mEmailAddress) + 1);
	mEmailAddress[strlen(other.mEmailAddress)] = '\0';

    strncpy(mDisplayName, other.mDisplayName, strlen(other.mDisplayName) + 1);
	mDisplayName[strlen(other.mDisplayName)] = '\0';
}

//Assignment operator
MessageAddress& MessageAddress::operator=(const MessageAddress& other)
{
	if (this != &other)
	{
		delete[] mEmailAddress;
		delete[] mDisplayName;
		//mEmailAddress
		mEmailAddress = new char[strlen(other.mEmailAddress) + 1];
		strncpy(mEmailAddress, other.mEmailAddress, strlen(other.mEmailAddress) + 1);
		mEmailAddress[strlen(other.mEmailAddress)] = '\0';
        //mDisplayName
		mDisplayName = new char[strlen(other.mDisplayName) + 1];
		strncpy(mDisplayName, other.mDisplayName, strlen(other.mDisplayName) + 1);
		mDisplayName[strlen(other.mDisplayName)] = '\0';
	}
	return *this;
}

//Move constructor
MessageAddress::MessageAddress(MessageAddress&& other) noexcept
	: mEmailAddress(other.mEmailAddress),
      mDisplayName(other.mDisplayName)
{
	// Release the data pointer from the source object so that the destructor 
	// does not free the memory multiple times.
	other.mEmailAddress = nullptr;
	other.mDisplayName = nullptr;
}

//Move assignement operator
MessageAddress& MessageAddress::operator=(MessageAddress&& other) noexcept
{
	if (this != &other)
	{
		delete[] mEmailAddress;
		delete[] mDisplayName;
		// Copy the data pointer and its length from the source object.
		mEmailAddress = other.mEmailAddress;
		mDisplayName = other.mDisplayName;
		// Release the data pointer from the source object so that
		// the destructor does not free the memory multiple times.
		other.mEmailAddress = nullptr;
		other.mDisplayName = nullptr;
	}
	return *this;
}

bool MessageAddress::operator==(const MessageAddress &pMsgComp) const
{
    return (strcmp(mEmailAddress, pMsgComp.mEmailAddress) == 0 && 
            strcmp(mDisplayName, pMsgComp.mDisplayName) == 0);
}

MessageAddress::operator string() const
{
    ostringstream retval;
    string display_name { mDisplayName };
    if (display_name.empty()) {
        retval << mEmailAddress;
    }
    else {
        retval << mDisplayName << " <" << mEmailAddress << ">";
    }
    return retval.str();
}

const char *MessageAddress::getEmailAddress() const
{
    return mEmailAddress;
}

const char *MessageAddress::getDisplayName() const
{
    return mDisplayName;
}

bool MessageAddress::isEmailAddressValid(const string &pEmailAddress) const
{
    regex emailPattern("^[_a-z0-9-]+(.[_a-z0-9-]+)*@[a-z0-9-]+(.[a-z0-9-]+)*(.[a-z]{2,4})$");
    return regex_match(StringUtils::toLower(pEmailAddress), emailPattern);
}

