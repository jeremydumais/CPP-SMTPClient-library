#include "..\Include\AttachmentError.h"
#include <cstring>

namespace jed_utils
{
	attachment_error::attachment_error(const char *err_msg)
	{
		error_message = new char[strlen(err_msg) + 1];
		strcpy_s(error_message, strlen(err_msg) + 1, err_msg);
	}

	attachment_error::~attachment_error()
	{
		delete error_message;
	}

	const char *attachment_error::what() const throw()
	{
		return error_message;
	}
}