# Jed# C++ SMTP Client Library

## A simple SMTP client library built in C++ that support authentication and TLS 1.3 encryption*
###### * For TLS 1.3 support you must build the library against OpenSSL 1.1.1
\
\### How to build the SMTP client or integrate it in your application

Follow this [link](https://github.com/jeremydumais/CPP-SMTPClient-library/wiki/How-to-build-the-SMTP-client-or-integrate-it-in-your-application) for a quick guide on how to build the SMTP client and integrate it in your application.
#
## How it works

### Some examples

#### Send a plaintext email

```c++
#include "smtpclient.h"
#include <iostream>

using namespace jed_utils;
using namespace std;

int main()
{
	SmtpClient client("<your smtp server address>", 25);
	try
	{
		PlaintextMessage msg(MessageAddress("myfromaddress@test.com", "Test Address Display"),
			MessageAddress("youraddress@domain.com"),
			"This is a test (Subject)",
			"Hello\nHow are you?");

		int err_no = client.sendMail(msg);
		if (err_no != 0) {
			cerr << "An error occurred. Return code : " << err_no;
			return 1;
		}
		cout << client.getCommunicationLog() << endl;
		cout << "Operation completed!" << endl;
	}
	catch (invalid_argument &err)
	{
		cerr << err.what() << endl;
	}
    return 0;
}
```

#### Send an html email to 2 recipients with an attachment

```c++
#include "smtpclient.h"
#include <iostream>

using namespace jed_utils;
using namespace std;

int main()
{
	SmtpClient client("<your smtp server address>", 25);
	try
	{
		const int ATTACHMENT_COUNT = 1;
		const int TOADDR_COUNT = 2;

		Attachment att1[ATTACHMENT_COUNT] = { Attachment("C:\\Temp\\test.png", "test image.png") };

		MessageAddress to_addr[TOADDR_COUNT] = { MessageAddress("youraddress@domain.com"), 
		MessageAddress("youraddress2@domain.com")
		};

		HTMLMessage msg(MessageAddress("myfromaddress@test.com", "Test Address Display"),
			to_addr, TOADDR_COUNT,
			"This is a test (Subject)",
			"<html><body><h1>Hello,</h1><br/><br/>How are you?</body></html>", nullptr, 0, nullptr, 0, att1, ATTACHMENT_COUNT);

		int err_no = client.sendMail(msg);
		if (err_no != 0) {
			cerr << "An error occurred. Return code : " << err_no;
			return 1;
		}
		cout << client.getCommunicationLog() << endl;
		cout << "Operation completed!" << endl;
	}
	catch (invalid_argument &err)
	{
		cerr << err.what() << endl;
	}
    return 0;
}
```

#### Send a plaintext email via a secure server

```c++
#include "sslsmtpclient.h"
#include <iostream>

using namespace jed_utils;
using namespace std;

int main()
{
	SSLSmtpClient client("<your smtp server address>", 587);
	client.setCredentials(Credential("myfromaddress@test.com", "mypassword"));
	try
	{
		PlaintextMessage msg(MessageAddress("myfromaddress@test.com", "Test Address Display"),
			MessageAddress("youraddress@domain.com", "Another Adresse display"),
			"This is a test (Subject)",
			"Hello\nHow are you?");

		int err_no = client.sendMail(msg);
		if (err_no != 0) {
			cerr << "An error occurred. Return code : " << err_no;
			return 1;
		}
		cout << client.getCommunicationLog() << endl;
		cout << "Operation completed!" << endl;
	}
	catch (invalid_argument &err)
	{
		cerr << err.what() << endl;
	}
    return 0;
}
```

## Download latest binaries

### Windows

[v1.1.2 (x64)](https://github.com/jeremydumais/CPP-SMTPClient-library/releases/download/v1.1.2/CPP-SMTPClient-Library.1.1.2.x64.zip)

[v1.1.2 (x86)](https://github.com/jeremydumais/CPP-SMTPClient-library/releases/download/v1.1.2/CPP-SMTPClient-Library.1.1.2.x86.zip)

## Documentation

See the classes documentation [here](https://github.com/jeremydumais/CPP-SMTPClient-library/wiki/Classes-Documentation)

