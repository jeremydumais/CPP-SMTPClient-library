#Jed# C++ SMTP Client Library

##Jed# C++ SMTP Client Library is a simple SMTP client library built in C++.

###smtp_client class

####Available methods
```c++
smtp_client(const char *server_name, const unsigned int port);
void send_mail(message *msg);
const char *get_server_reply() const;
```	

###attachment class

####Available methods
```c++
attachment(const char *filename, const char *name = "");
const char *get_name() const;
const char *get_filename() const;
const char *get_base64_encoded_file() const;
const char *get_mime_type() const;
```	

###plaintext_message class

####Available methods
```c++
plaintext_message(message_address from,
	message_address to,
	const char *subject,
	const char *body,
	message_address *cc = nullptr,
	message_address *bcc = nullptr,
	attachment attachments[] = nullptr,
	const unsigned int attachments_size = 0);
plaintext_message(message_address from,
	message_address to[],
	const unsigned int to_size,
	const char *subject,
	const char *body,
	message_address cc[] = nullptr,
	const unsigned int cc_size = 0,
	message_address bcc[] = nullptr,
	const unsigned int bcc_size = 0,
	attachment attachments[] = nullptr,
	const unsigned int attachments_size = 0);
const char *get_mimetype();
const message_address get_from() const;
const message_address *get_to_ptr() const;
const unsigned int get_to_count() const;
const char *get_subject() const;
const char *get_body() const;
const attachment *get_attachments_ptr() const;
const unsigned int get_attachments_count() const;
```	

###html_message class

####Available methods
```c++
html_message(message_address from,
	message_address to,
	const char *subject,
	const char *body,
	message_address *cc = nullptr,
	message_address *bcc = nullptr,
	attachment attachments[] = nullptr,
	const unsigned int attachments_size = 0);
html_message(message_address from,
	message_address to[],
	const unsigned int to_size,
	const char *subject,
	const char *body,
	message_address cc[] = nullptr,
	const unsigned int cc_size = 0,
	message_address bcc[] = nullptr,
	const unsigned int bcc_size = 0,
	attachment attachments[] = nullptr,
	const unsigned int attachments_size = 0);
const char *get_mimetype();
const message_address get_from() const;
const message_address *get_to_ptr() const;
const unsigned int get_to_count() const;
const char *get_subject() const;
const char *get_body() const;
const attachment *get_attachments_ptr() const;
const unsigned int get_attachments_count() const;
```	

####Here's some examples

#####Send a plaintext email

```c++
#include <SMTPClient.h>
#include <iostream>

using namespace jed_utils;
using namespace std;

int main()
{
	smtp_client *client = new smtp_client("<your smtp server address>", 25);
	try
	{
		plaintext_message msg(message_address("myfromaddress@test.com", "Test Address Display"),
			message_address("youraddress@domain.com")
			"This is a test (Subject)",
			"Hello\nHow are you?");

		client->send_mail(&msg);
		cout << client->get_server_reply() << endl;
		cout << "Operation completed!" << endl;
	}
	catch (communication_error &err)
	{
		cerr << err.what() << endl;
	}
	catch (attachment_error &err)
	{
		cerr << err.what() << endl;
	}
	delete client;
    return 0;
}
```

#####Send an html email to 2 recipients with an attachment

```c++
#include <SMTPClient.h>
#include <iostream>

using namespace jed_utils;
using namespace std;

int main()
{
	smtp_client *client = new smtp_client("<your smtp server address>", 25);
	try
	{
		const int ATTACHMENT_COUNT = 1;
		const int TOADDR_COUNT = 2;

		attachment att1[ATTACHMENT_COUNT] = { attachment("C:\Temp\test.png", "test image.png") };

		message_address to_addr[TOADDR_COUNT] = { message_address("youraddress@domain.com"), 
		message_address("youraddress2@domain.com")
		};

		html_message msg(message_address("myfromaddress@test.com", "Test Address Display"),
			to_addr, TOADDR_COUNT,
			"This is a test (Subject)",
			"<html><body><h1>Hello,</h1><br/><br/>How are you?</body></html>", nullptr, 0, nullptr, 0, att1, ATTACHMENT_COUNT);

		client->send_mail(&msg);
		cout << client->get_server_reply() << endl;
		cout << "Operation completed!" << endl;
	}
	catch (communication_error &err)
	{
		cerr << err.what() << endl;
	}
	catch (attachment_error &err)
	{
		cerr << err.what() << endl;
	}
	delete client;
    return 0;
}
```
