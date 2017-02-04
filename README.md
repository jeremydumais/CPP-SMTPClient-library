#Jed# C++ SMTP Client Library

##Jed# C++ SMTP Client Library is a simple SMTP client library built in C++.

###smtp_client class

####Available methods
```c++
smtp_client(const std::string server_name, const unsigned int port);
void send_mail(message *msg);
const std::string get_server_reply() const;
```	

###attachment class

####Available methods
```c++
attachment(const std::string filename, const std::string name = "");
std::string get_name() const;
std::string get_filename() const;
std::string get_base64_encoded_file() const;
std::string get_mime_type() const;
```	

###plaintext_message class

####Available methods
```c++
plaintext_message(message_address from,
	std::vector<message_address> *to,
	std::string subject,
	std::string body,
	std::vector<message_address> *cc = NULL,
	std::vector<message_address> *bcc = NULL,
	std::vector<attachment> *attachments = NULL);
std::string get_mimetype();
const message_address get_from() const;
const message_address *get_to_ptr() const;
const unsigned int get_to_count() const;
const std::string get_subject() const;
const std::string get_body() const;
const attachment *get_attachments_ptr() const;
const unsigned int get_attachments_count() const;
```	

###html_message class

####Available methods
```c++
html_message(message_address from,
	std::vector<message_address> *to,
	std::string subject,
	std::string body,
	std::vector<message_address> *cc = NULL,
	std::vector<message_address> *bcc = NULL,
	std::vector<attachment> *attachments = NULL);
std::string get_mimetype();
const message_address get_from() const;
const message_address *get_to_ptr() const;
const unsigned int get_to_count() const;
const std::string get_subject() const;
const std::string get_body() const;
const attachment *get_attachments_ptr() const;
const unsigned int get_attachments_count() const;
```	

####Here's an example

#####Send an html email with an attachment

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
		vector<attachment> attachments;
		attachment att("C:\Temp\test.png", "test image.png");
		attachments.push_back(att);

		vector<message_address> to;
		to.push_back(message_address("youraddress@domain.com"));

		html_message msg(message_address("myfromaddress@test.com", "Test Address Display"), 
			&to, 
			"This is a test (Subject)", 
			"<html><body>Hello,<br/><br/>How are you?</body></html>", NULL, NULL, &attachments);

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
