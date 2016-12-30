#include "..\Include\CommunicationError.h"

namespace jed_utils
{
	communication_error::communication_error(const std::string err_msg)
	{ 
		error_message = err_msg;
	}

	const char *communication_error::what() const throw()
	{
		return error_message.c_str();
	}
}
