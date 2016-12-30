#Jed# C++ SMTP Client Library

###Jed# C++ SMTP Client Library is a simple SMTP client library built in C++.

####Available methods
```c++
smtp_client(const std::string server_name, const unsigned int port);
void send_mail(const std::string from, 
			const std::string to, 
			const std::string subject,
			const std::string body);
const std::string get_server_reply();
```	

####Here's an example

#####Send plain text email

```c++
#include <SMTPClient.h>
#include <conio.h>
#include <iostream>

using namespace jed_utils;
using namespace std;

int main()
{
	smtp_client *client = new smtp_client("<your smtp server address>", 25);
	try
	{
		client->send_mail("myfromaddress@test.com", "youraddress@domain.com", "This is a test (Subject)", "This is the body content!");
		cout << client->get_server_reply() << endl;
		cout << "Operation completed!" << endl;
	}
	catch (communication_error &err)
	{
		cout << err.what() << endl;
	}
	delete client;
	_getch();
    return 0;
}
```
