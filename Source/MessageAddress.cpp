#include "MessageAddress.h"
#include "StringUtils.h"
#include <stdexcept>
#include <string>
#include <regex>

using namespace std;

namespace jed_utils
{
	MessageAddress::MessageAddress(const string &pEmailAddress, const string &pDisplayName)
	{
		//Check if the email address is not empty or white spaces
		if (pEmailAddress.length() == 0 || StringUtils::trim(pEmailAddress).compare("") == 0)
			throw invalid_argument("pEmailAddress");
		//Check is the email address is valid
		if (!isEmailAddressValid(pEmailAddress))
			throw invalid_argument("pEmailAddress");

		this->mEmailAddress = new string(pEmailAddress);
		this->mDisplayName = new string(pDisplayName);
	}

	MessageAddress::MessageAddress(const MessageAddress &item)
	{
		mEmailAddress = new string(*item.mEmailAddress);
		mDisplayName = new string(*item.mDisplayName);
	}

	MessageAddress& MessageAddress::operator=(const MessageAddress &msg_add)
	{
		if (this != &msg_add)
		{
			delete mEmailAddress;
			delete mDisplayName;
			mEmailAddress = new string(*msg_add.mEmailAddress);
			mDisplayName = new string(*msg_add.mDisplayName);
		}
		return *this;
	}

	bool MessageAddress::operator==(const MessageAddress &msg_comp) const
	{
		return (mEmailAddress->compare(*msg_comp.mEmailAddress) == 0 && 
			mDisplayName->compare(*msg_comp.mDisplayName) == 0);
	}

	MessageAddress::operator string() const
	{
		ostringstream retval;
		if (mDisplayName && mDisplayName->compare("") == 0)
			retval << mEmailAddress;
		else
			retval << mDisplayName << " <" << mEmailAddress << ">";
		return retval.str();
	}

	MessageAddress::~MessageAddress()
	{
		if (mEmailAddress)
			delete mEmailAddress;
		if (mDisplayName)
			delete mDisplayName;
	}

	const string &MessageAddress::getEmailAddress() const
	{
		return *mEmailAddress;
	}

	const string &MessageAddress::getDisplayName() const
	{
		return *mDisplayName;
	}

	bool MessageAddress::isEmailAddressValid(const string &pEmailAddress) const
	{
		regex emailPattern("^[_a-z0-9-]+(.[_a-z0-9-]+)*@[a-z0-9-]+(.[a-z0-9-]+)*(.[a-z]{2,4})$");
		return regex_match(pEmailAddress, emailPattern);
	}
}