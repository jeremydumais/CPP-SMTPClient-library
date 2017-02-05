#include "..\Include\CommunicationError.h"

namespace jed_utils
{
	communication_error::communication_error(const char *err_msg)
	{ 
		error_message = new char[strlen(err_msg) + 1];
		strcpy_s(error_message, strlen(err_msg) + 1, err_msg);
	}

	communication_error::~communication_error()
	{
		delete error_message;
	}

	const char *communication_error::what() const throw()
	{
		return error_message;
	}
}
