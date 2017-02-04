#include "../Include/MessageAddress.h"

using namespace jed_utils;
using namespace std;

message_address::message_address(string email_address, string display_name)
{
	if (email_address.length() == 0)
		throw invalid_argument("email_address");
	const std::string::size_type size_email_address = email_address.size();
	this->email_address = new char[size_email_address + 1];
	memcpy(this->email_address, email_address.c_str(), size_email_address + 1);

	const std::string::size_type size_display_name = display_name.size();
	this->display_name = new char[size_display_name + 1];
	memcpy(this->display_name, display_name.c_str(), size_display_name + 1);
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

std::string message_address::get_email_address() const
{
	return email_address;
}

std::string message_address::get_display_name() const
{
	return display_name;
}
