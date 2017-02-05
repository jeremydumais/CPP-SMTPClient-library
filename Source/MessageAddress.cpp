#include "../Include/MessageAddress.h"

using namespace std;

namespace jed_utils
{
	message_address::message_address(const char *email_address, const char *display_name)
	{
		if (strlen(email_address) == 0)
			throw invalid_argument("email_address");

		this->email_address = new char[strlen(email_address) + 1];
		strcpy_s(this->email_address, strlen(email_address) + 1, email_address);

		this->display_name = new char[strlen(display_name) + 1];
		strcpy_s(this->display_name, strlen(display_name) + 1, display_name);
	}

	message_address::message_address(const message_address &item)
	{
		email_address = new char[strlen(item.email_address) + 1];
		memcpy(email_address, item.email_address, strlen(item.email_address) + 1);

		display_name = new char[strlen(item.display_name) + 1];
		memcpy(display_name, item.display_name, strlen(item.display_name) + 1);
	}

	const message_address& message_address::operator=(const message_address &msg_add)
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

	message_address::operator string() const
	{
		ostringstream retval;
		if (display_name && strcmp(display_name, "") == 0)
			retval << email_address;
		else
			retval << display_name << " <" << email_address << ">";
		return retval.str();
	}

	message_address::~message_address()
	{
		delete email_address;
		delete display_name;
	}

	const char *message_address::get_email_address() const
	{
		return email_address;
	}

	const char *message_address::get_display_name() const
	{
		return display_name;
	}
}