#include "../Include/MessageAddress.h"
#include <stdexcept>
#include <cstring>

using namespace std;

namespace jed_utils
{
	MessageAddress::MessageAddress(const char *pEmailAddress, const char *pDisplayName)
	{
		if (strlen(pEmailAddress) == 0)
			throw invalid_argument("pEmailAddress");

		this->mEmailAddress = new char[strlen(pEmailAddress) + 1];
		strcpy_s(this->mEmailAddress, strlen(pEmailAddress) + 1, pEmailAddress);

		this->mDisplayName = new char[strlen(pDisplayName) + 1];
		strcpy_s(this->mDisplayName, strlen(pDisplayName) + 1, pDisplayName);
	}

	MessageAddress::MessageAddress(const MessageAddress &item)
	{
		mEmailAddress = new char[strlen(item.mEmailAddress) + 1];
		memcpy(mEmailAddress, item.mEmailAddress, strlen(item.mEmailAddress) + 1);

		mDisplayName = new char[strlen(item.mDisplayName) + 1];
		memcpy(mDisplayName, item.mDisplayName, strlen(item.mDisplayName) + 1);
	}

	const MessageAddress& MessageAddress::operator=(const MessageAddress &msg_add)
	{
		if (this != &msg_add)
		{
			delete mEmailAddress;
			delete mDisplayName;
			mEmailAddress = new char[strlen(msg_add.mEmailAddress) + 1];
			memcpy(mEmailAddress, msg_add.mEmailAddress, strlen(msg_add.mEmailAddress) + 1);

			mDisplayName = new char[strlen(msg_add.mDisplayName) + 1];
			memcpy(mDisplayName, msg_add.mDisplayName, strlen(msg_add.mDisplayName) + 1);
		}
		return *this;
	}

	bool MessageAddress::operator==(const MessageAddress &msg_comp) const
	{
		return (strcmp(mEmailAddress, msg_comp.mEmailAddress) == 0 && 
			strcmp(mDisplayName, msg_comp.mDisplayName) == 0);
	}

	MessageAddress::operator string() const
	{
		ostringstream retval;
		if (mDisplayName && strcmp(mDisplayName, "") == 0)
			retval << mEmailAddress;
		else
			retval << mDisplayName << " <" << mEmailAddress << ">";
		return retval.str();
	}

	MessageAddress::~MessageAddress()
	{
		delete mEmailAddress;
		delete mDisplayName;
	}

	const char *MessageAddress::getEmailAddress() const
	{
		return mEmailAddress;
	}

	const char *MessageAddress::getDisplayName() const
	{
		return mDisplayName;
	}
}