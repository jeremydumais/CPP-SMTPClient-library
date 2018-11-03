#include "../Include/MessageAddress.h"
#include <stdexcept>
#include <cstring>

using namespace std;

namespace jed_utils
{
	MessageAddress::MessageAddress(const char *email_address, const char *display_name)
	{
		if (strlen(email_address) == 0)
			throw invalid_argument("email_address");

		this->email_address = new char[strlen(email_address) + 1];
		strcpy_s(this->email_address, strlen(email_address) + 1, email_address);

		this->display_name = new char[strlen(display_name) + 1];
		strcpy_s(this->display_name, strlen(display_name) + 1, display_name);
	}

	MessageAddress::MessageAddress(const MessageAddress &item)
	{
		email_address = new char[strlen(item.email_address) + 1];
		memcpy(email_address, item.email_address, strlen(item.email_address) + 1);

		display_name = new char[strlen(item.display_name) + 1];
		memcpy(display_name, item.display_name, strlen(item.display_name) + 1);
	}

	const MessageAddress& MessageAddress::operator=(const MessageAddress &msg_add)
	{
		if (this != &msg_add)
		{
			delete email_address;
			delete display_name;
			email_address = new char[strlen(msg_add.email_address) + 1];
			memcpy(email_address, msg_add.email_address, strlen(msg_add.email_address) + 1);

			display_name = new char[strlen(msg_add.display_name) + 1];
			memcpy(display_name, msg_add.display_name, strlen(msg_add.display_name) + 1);
		}
		return *this;
	}

	bool MessageAddress::operator==(const MessageAddress &msg_comp) const
	{
		return (strcmp(email_address, msg_comp.email_address) == 0 && 
			strcmp(display_name, msg_comp.display_name) == 0);
	}

	MessageAddress::operator string() const
	{
		ostringstream retval;
		if (display_name && strcmp(display_name, "") == 0)
			retval << email_address;
		else
			retval << display_name << " <" << email_address << ">";
		return retval.str();
	}

	MessageAddress::~MessageAddress()
	{
		delete email_address;
		delete display_name;
	}

	const char *MessageAddress::get_email_address() const
	{
		return email_address;
	}

	const char *MessageAddress::get_display_name() const
	{
		return display_name;
	}
}