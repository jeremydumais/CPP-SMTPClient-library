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

void message_address_unittest()
{
	test_message_address_constructor();
}