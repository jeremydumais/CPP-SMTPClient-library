// SMTPClient_Test.cpp : Defines the entry point for the console application.

#include "../../Include/SMTPClient.h"
#include <iostream>

using namespace jed_utils;
using namespace std;

void attachment_unittest();
void message_address_unittest();

int main()
{
	attachment_unittest();
	message_address_unittest();
	
	cout << "Unit tests successful!" << endl;

	return 0;
}

