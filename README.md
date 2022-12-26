# Jed# C++ SMTP Client Library

[![Build status](https://github.com/jeremydumais/CPP-SMTPClient-library/actions/workflows/cmake.yml/badge.svg)](https://github.com/jeremydumais/CPP-SMTPClient-library/actions/workflows/cmake.yml)

## A simple SMTP client library built in C++ that support authentication and secure connections (Forced SSL and Opportunistic SSL/TLS encryption).
##### For TLS 1.3 support you must build the library against OpenSSL 1.1.1
<br/>

### The library is cross-platform and has been tested on Linux and Windows.
\
\### How to build the SMTP client or integrate it in your application

Follow this [link](https://github.com/jeremydumais/CPP-SMTPClient-library/wiki/How-to-build-the-SMTP-client-or-integrate-it-in-your-application) for a quick guide on how to build the SMTP client and integrate it in your application.

#
## Download latest binaries

### Windows

<table>
<tr>
<th> Release </th>
<th> MD5 hash of smtpclient.dll </th>
</tr>
<tr>
<td>

[v1.1.4 (x64)](https://github.com/jeremydumais/CPP-SMTPClient-library/releases/download/v1.1.4/CPP-SMTPClient-Library.1.1.4.x64.zip)

</td>
<td>

c0c50a722e02dba488d6440ede046976

</td>
</tr>
<tr>
<td>

[v1.1.4 (x86)](https://github.com/jeremydumais/CPP-SMTPClient-library/releases/download/v1.1.4/CPP-SMTPClient-Library.1.1.4.x86.zip)

</td>
<td>

dce3b4c0704c8aafd4b2c5e8fdd3a701

</td>
</tr>
</table>

See the section [Releases](https://github.com/jeremydumais/CPP-SMTPClient-library/releases) for previous versions.

#
## The 3 client classes

### OpportunisticSecureSMTPClient

The OpportunisticSecureSMTPClient **should be your default choice** for communicating with modern SMTP servers. The communication is usually done via port 587.
<br/>

### ForcedSecureSMTPClient

The ForcedSecureSMTPClient is useful to communicate with legacy systems which requires that the communication be encrypted from the initial connection. The communication is usually done via port 465.
<br/>

### SmtpClient
The SmtpClient should be used to communicate with internal relay servers. The communication is usually done via port 25.

#
## How it works

### Some examples
- [Send a plaintext email via an unsecured server](#send-a-plaintext-email-via-an-unsecured-server)
- [Send an html email to 2 recipients with an attachment via an unsecured server](#send-an-html-email-to-2-recipients-with-an-attachment-via-an-unsecured-server)
- [Send a plaintext email via a secure server (opportunistic) -> SSL/TLS Port 587](#send-a-plaintext-email-via-a-secure-server-opportunistic)
- [Send a plaintext email via a secure server (forced) -> SSL/TLS Port 465](#send-a-plaintext-email-via-a-secure-server-forced)

<br/>

#### Send a plaintext email via an unsecured server

```c++
#include "smtpclient.h"
#include <iostream>
#include <memory>
#include <stdexcept>

using namespace jed_utils;

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
			std::cout << client.getCommunicationLog() << '\n';
			std::unique_ptr<char> errorMessage(client.getErrorMessage(err_no));
			std::cerr << "An error occurred: " << errorMessage.get()
                 << " (error no: " << err_no << ")" << '\n';
			return 1;
		}
		std::cout << client.getCommunicationLog() << '\n';
		std::cout << "Operation completed!" << std::endl;
	}
	catch (std::invalid_argument &err)
	{
		std::cerr << err.what() << std::endl;
	}
    return 0;
}
```

#### Send an html email to 2 recipients with an attachment via an unsecured server

```c++
#include "smtpclient.h"
#include <iostream>
#include <memory>
#include <stdexcept>

using namespace jed_utils;

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
			std::cout << client.getCommunicationLog() << '\n';
			std::unique_ptr<char> errorMessage(client.getErrorMessage(err_no));
			std::cerr << "An error occurred: " << errorMessage.get()
                 << " (error no: " << err_no << ")" << '\n';
			return 1;
		}
		std::cout << client.getCommunicationLog() << '\n';
		std::cout << "Operation completed!" << std::endl;
	}
	catch (std::invalid_argument &err)
	{
		std::cerr << err.what() << std::endl;
	}
    return 0;
}
```

#### Send a plaintext email via a secure server (opportunistic)

```c++
#include "opportunisticsecuresmtpclient.h"
#include <iostream>
#include <memory>
#include <stdexcept>

using namespace jed_utils;

int main()
{
	OpportunisticSecureSMTPClient client("<your smtp server address>", 587);
	client.setCredentials(Credential("myfromaddress@test.com", "mypassword"));
	try
	{
		PlaintextMessage msg(MessageAddress("myfromaddress@test.com", "Test Address Display"),
			MessageAddress("youraddress@domain.com", "Another Adresse display"),
			"This is a test (Subject)",
			"Hello\nHow are you?");

		int err_no = client.sendMail(msg);
		if (err_no != 0) {
			std::cout << client.getCommunicationLog() << '\n';
			std::unique_ptr<char> errorMessage(client.getErrorMessage(err_no));
			std::cerr << "An error occurred: " << errorMessage.get()
                 << " (error no: " << err_no << ")" << '\n';
			return 1;
		}
		std::cout << client.getCommunicationLog() << '\n';
		std::cout << "Operation completed!" << std::endl;
	}
	catch (std::invalid_argument &err)
	{
		std::cerr << err.what() << std::endl;
	}
    return 0;
}
```

#### Send a plaintext email via a secure server (forced)

```c++
#include "forcedsecuresmtpclient.h"
#include <iostream>
#include <memory>
#include <stdexcept>

using namespace jed_utils;

int main()
{
	ForcedSecureSMTPClient client("<your smtp server address>", 465);
	client.setCredentials(Credential("myfromaddress@test.com", "mypassword"));
	try
	{
		PlaintextMessage msg(MessageAddress("myfromaddress@test.com", "Test Address Display"),
			MessageAddress("youraddress@domain.com", "Another Adresse display"),
			"This is a test (Subject)",
			"Hello\nHow are you?");

		int err_no = client.sendMail(msg);
		if (err_no != 0) {
			std::cout << client.getCommunicationLog() << '\n';
			std::unique_ptr<char> errorMessage(client.getErrorMessage(err_no));
			std::cerr << "An error occurred: " << errorMessage.get()
                 << " (error no: " << err_no << ")" << '\n';
			return 1;
		}
		std::cout << client.getCommunicationLog() << '\n';
		std::cout << "Operation completed!" << std::endl;
	}
	catch (std::invalid_argument &err)
	{
		std::cerr << err.what() << std::endl;
	}
    return 0;
}
```

## Unit tests
[How to run the unit tests](https://github.com/jeremydumais/CPP-SMTPClient-library/wiki/Run-the-unit-tests)

## Documentation

See the classes documentation [here](https://github.com/jeremydumais/CPP-SMTPClient-library/wiki/Classes-Documentation)

