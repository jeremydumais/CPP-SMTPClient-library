#include <gtest/gtest.h>
#include "../../Include/MessageAddress.h"
#include <stdexcept>

using namespace jed_utils;
using namespace std;

TEST(MessageAddress_constructor, FailEmptyParam)
{
	//Test with empty filename
	try
	{
		MessageAddress msg_add("", "");
		FAIL();

	}
	catch (invalid_argument)
	{
	}
}

TEST(MessageAddress_constructor, ValidParam)
{
	MessageAddress msg_add("test@domain.com", "Test Address");
}

TEST(MessageAddress_constructor, EmptyEmailAddressThrowInvalidArgument)
{
	try
	{
		MessageAddress msg_add("", "Test Address");
		FAIL();
	}
	catch(invalid_argument)
	{

	}
}

TEST(MessageAddress_get_email_address, validDomain)
{
	MessageAddress msg_add("test@domain.com", "Test Address");
	ASSERT_EQ(msg_add.getEmailAddress().compare("test@domain.com"), 0);
}

TEST(MessageAddress_get_display_name, validDN)
{
	MessageAddress msg_add("test@domain.com", "Test Address");
	ASSERT_EQ(msg_add.getDisplayName().compare("Test Address"), 0);
}