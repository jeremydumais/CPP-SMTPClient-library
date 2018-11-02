// SMTPClient_Test.cpp : Defines the entry point for the console application.
#include <gtest/gtest.h>
#include "../../Include/SMTPClient.h"

#include <iostream>
#include <stdexcept>

using namespace jed_utils;
using namespace std;

void attachment_unittest();
void message_address_unittest();

int main(int argc, char**argv)
{
	/*attachment_unittest();
	message_address_unittest();
	
	cout << "Unit tests successful!" << endl;
	
	return 0;*/
	::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}