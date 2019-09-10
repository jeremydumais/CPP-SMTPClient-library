#include <gtest/gtest.h>
#include "../../src/messageaddress.h"
#include <stdexcept>

using namespace jed_utils;
using namespace std;

TEST(MessageAddress_constructor, EmptyEmailAddrInvalidArgument)
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

TEST(MessageAddress_constructor, EmptyEmailAddressValidDNThrowInvalidArgument)
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

TEST(MessageAddress_constructor, WhiteSpacesEmailAddrInvalidArgument)
{
	//Test with empty filename
	try
	{
		MessageAddress msg_add(" ", "");
		FAIL();

	}
	catch (invalid_argument)
	{
	}
}

TEST(MessageAddress_constructor, OnlyPrefixEmailAddrInvalidArgument)
{
	//Test with empty filename
	try
	{
		MessageAddress msg_add("test", "");
		FAIL();

	}
	catch (invalid_argument)
	{
	}
}

TEST(MessageAddress_constructor, OnlyAtSignEmailAddrInvalidArgument)
{
	//Test with empty filename
	try
	{
		MessageAddress msg_add("@", "");
		FAIL();

	}
	catch (invalid_argument)
	{
	}
}

TEST(MessageAddress_constructor, NoSuffixEmailAddrInvalidArgument)
{
	//Test with empty filename
	try
	{
		MessageAddress msg_add("test@", "");
		FAIL();

	}
	catch (invalid_argument)
	{
	}
}

TEST(MessageAddress_constructor, NoExtensionEmailAddrValidParam)
{
	MessageAddress msg_add("test@domain", "Test Address");
}

TEST(MessageAddress_constructor, ValidParam)
{
	MessageAddress msg_add("test@domain.com", "Test Address");
}

TEST(MessageAddress_get_email_address, validDomain)
{
	MessageAddress msg_add("test@domain.com", "Test Address");
	ASSERT_STREQ("test@domain.com", msg_add.getEmailAddress());
}

TEST(MessageAddress_get_display_name, validDN)
{
	MessageAddress msg_add("test@domain.com", "Test Address");
	ASSERT_STREQ("Test Address", msg_add.getDisplayName());
}
