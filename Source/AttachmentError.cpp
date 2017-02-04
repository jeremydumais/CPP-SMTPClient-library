#include "..\Include\AttachmentError.h"

namespace jed_utils
{
	attachment_error::attachment_error(const std::string err_msg)
	{
		const std::string::size_type size_errormsg = err_msg.size();
		error_message = new char[size_errormsg + 1];
		memcpy(error_message, err_msg.c_str(), size_errormsg + 1);
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