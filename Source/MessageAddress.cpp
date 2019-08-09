#include "../Include/MessageAddress.h"
#include "../Include/StringUtils.h"
#include <stdexcept>
#include <string>
#include <regex>

using namespace std;

namespace jed_utils
{
	MessageAddress::MessageAddress(const string &pEmailAddress, const string &pDisplayName)
        : mEmailAddress(""), mDisplayName("")
	{
		//Check if the email address is not empty or white spaces
		if (pEmailAddress.length() == 0 || StringUtils::trim(pEmailAddress).compare("") == 0)
			throw invalid_argument("pEmailAddress");
		//Check is the email address is valid
		if (!isEmailAddressValid(pEmailAddress))
			throw invalid_argument("pEmailAddress");

		mEmailAddress = pEmailAddress;
		mDisplayName = pDisplayName;
	}

	bool MessageAddress::operator==(const MessageAddress &msg_comp) const
	{
		return (mEmailAddress.compare(msg_comp.mEmailAddress) == 0 && 
			mDisplayName.compare(msg_comp.mDisplayName) == 0);
	}

	MessageAddress::operator string() const
	{
		ostringstream retval;
		if (mDisplayName.compare("") == 0)
			retval << mEmailAddress;
		else
			retval << mDisplayName << " <" << mEmailAddress << ">";
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
}
