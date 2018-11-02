#include <gtest/gtest.h>
#include "../../Include/MessageAddress.h"
#include <assert.h>
#include <stdexcept>

using namespace jed_utils;
using namespace std;

TEST(message_address_constructor, FailEmptyParam)
{
	//Test with empty filename
	try
	{
		message_address msg_add("", "");
		FAIL();

	}
	catch (invalid_argument)
	{
	}
}

TEST(message_address_constructor, ValidParam)
{
	message_address msg_add("test@domain.com", "Test Address");
}

TEST(message_address_get_email_address, validDomain)
{
	message_address msg_add("test@domain.com", "Test Address");
	assert(_stricmp(msg_add.get_email_address(), "test@domain.com") == 0);
}

TEST(message_address_get_display_name, validDN)
{
	message_address msg_add("test@domain.com", "Test Address");
	assert(_stricmp(msg_add.get_display_name(), "Test Address") == 0);
}