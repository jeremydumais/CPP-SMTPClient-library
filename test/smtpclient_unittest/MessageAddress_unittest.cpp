#include "../../Include/MessageAddress.h"
#include <assert.h>


using namespace jed_utils;
using namespace std;

void test_message_address_constructor()
{
	//Test with empty filename
	try
	{
		message_address msg_add("", "");
		assert(false);

	}
	catch (invalid_argument& err)
	{
		assert(strcmp(err.what(), "email_address") == 0);
	}
}

void test_message_address_get_email_address()
{
	message_address msg_add("test@domain.com", "Test Address");
	assert(_stricmp(msg_add.get_email_address(), "test@domain.com") == 0);
}

void test_message_address_get_display_name()
{
	message_address msg_add("test@domain.com", "Test Address");
	assert(_stricmp(msg_add.get_display_name(), "Test Address") == 0);
}

void message_address_unittest()
{
	test_message_address_constructor();
	test_message_address_get_email_address();
	test_message_address_get_display_name();
}