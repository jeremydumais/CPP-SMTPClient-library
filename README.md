# Jed# C++ SMTP Client Library

[![Build status](https://github.com/jeremydumais/CPP-SMTPClient-library/actions/workflows/cmake.yml/badge.svg)](https://github.com/jeremydumais/CPP-SMTPClient-library/actions/workflows/cmake.yml)
![Latest version](https://img.shields.io/badge/latest_version-1.1.5-brightgreen)
![Dependencies](https://img.shields.io/badge/dependencies-openssl-brightgreen)

## A simple SMTP client library built in C++ that support authentication and secure connections (Opportunistic SSL/TLS and Forced SSL encryption).

##### For TLS 1.3 support you must build the library against OpenSSL 1.1.1

##### The library is cross-platform and has been tested on Linux and Windows.

### How to build the SMTP client or integrate it in your application

Follow this [link](https://github.com/jeremydumais/CPP-SMTPClient-library/wiki/How-to-build-the-SMTP-client-or-integrate-it-in-your-application) for a quick guide on how to build the SMTP client and integrate it in your application.

Follow these guides to build the library on [Windows](https://github.com/jeremydumais/CPP-SMTPClient-library/wiki/Build-the-CPP-SMTPClient-library-on-Windows)
and [Linux](https://github.com/jeremydumais/CPP-SMTPClient-library/wiki/Build-the-CPP-SMTPClient-library-on-Linux).

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

See the section
[Releases](https://github.com/jeremydumais/CPP-SMTPClient-library/releases)
for previous versions.

## The 3 client classes

### OpportunisticSecureSMTPClient

The OpportunisticSecureSMTPClient **should be your default choice** for communicating
with modern SMTP servers. The communication is usually done via port 587.

In this mode, the communication starts unencrypted, then the client will asked the
server to provide the supported options and if the server supports encryption, the
STARTTLS command will be sent. Negotiation will take place between the server
and the client to find the most secure encryption to use for communication.

If the server does not support encryption, the communication will remain unencrypted
and it will be logged in the communication log.

This client can be used for newest SMTP servers like Google Gmail, Microsoft Office
365 or good old uncrypted SMTP servers.

### ForcedSecureSMTPClient

The ForcedSecureSMTPClient is useful to communicate with legacy systems which
requires that the communication be encrypted from the initial connection.
The communication is usually done via port 465.

### SmtpClient

The SmtpClient should be used to communicate with internal relay servers.
It does not support encryption of communications. The communication is usually done
via port 25.

## How it works

### 2-ways of consuming the library
![From in version 1.1.5+](https://img.shields.io/badge/From_in_version-1.1.5+-green)

You can consume objects in the library either using the C++ Interface
(the jed_utils::cpp namespace) or using the Pure C Interface
(the jed_utils namespace).

The Pure C Interface was designed primarily to maintain binary
compatibility between major versions of the MSVC compiler toolsets.
[C++ binary compatibility between Visual Studio versions](https://learn.microsoft.com/en-us/cpp/porting/binary-compat-2015-2017?view=msvc-170&viewFallbackFrom=vs-2019)

To see some usage examples with Pure C Interface refer to the wiki
[Some examples with Pure C Interface](https://github.com/jeremydumais/CPP-SMTPClient-library/wiki/Some-examples-with-pure-c-interface)

This problem has been resolved since 2015 so it is no longer an issue.

**The C++ Interface should then be your default choice.**

### Some examples with C++ Interface

![From in version 1.1.5+](https://img.shields.io/badge/From_in_version-1.1.5+-green)

- [Send a plaintext email via a secure server (opportunistic) -> SSL/TLS Port 587](#send-a-plaintext-email-via-a-secure-server-opportunistic)
- [Send an html email to 2 recipients with an attachment via a secure server](#send-an-html-email-to-2-recipients-with-an-attachment-via-a-secure-server-opportunistic)
- [Send a plaintext email via a secure server (forced) -> SSL/TLS Port 465](#send-a-plaintext-email-via-a-secure-server-forced)

#### Send a plaintext email via a secure server (opportunistic)

```c++
#include "cpp/opportunisticsecuresmtpclient.hpp"
#include "cpp/plaintextmessage.hpp"
#include <iostream>
#include <stdexcept>

using namespace jed_utils::cpp;

int main() {
	OpportunisticSecureSMTPClient client("<your smtp server address>", 587);
	client.setCredentials(Credential("myfromaddress@test.com", "mypassword"));
	try	{
		PlaintextMessage msg(MessageAddress("myfromaddress@test.com", "Test Address Display"),
			{ MessageAddress("youraddress@domain.com", "Another Address display") },
			"This is a test (Subject)",
			"Hello\nHow are you?");

		int err_no = client.sendMail(msg);
		if (err_no != 0) {
			std::cerr << client.getCommunicationLog() << '\n';
			std::string errorMessage = client.getErrorMessage(err_no);
			std::cerr << "An error occurred: " << errorMessage
                 << " (error no: " << err_no << ")" << '\n';
			return 1;
		}
		std::cout << client.getCommunicationLog() << '\n';
		std::cout << "Operation completed!" << std::endl;
	}
	catch (std::invalid_argument &err) {
		std::cerr << err.what() << std::endl;
	}
    return 0;
}
```

#### Send an html email to 2 recipients with an attachment via a secured server (opportunistic)

*You will need to include cpp/htmlmessage.hpp*

```c++
OpportunisticSecureSMTPClient client("<your smtp server address>", 587);
client.setCredentials(Credential("myfromaddress@test.com", "mypassword"));

const MessageAddress from("myfromaddress@test.com", "Test Address Display");
const auto to = { MessageAddress("youraddress@domain.com") };
const auto subject = "This is a test (Subject)";
const auto body = "<html><body><h1>Hello,</h1><br/><br/>How are you?</body></html>";
const auto cc = { MessageAddress("youraddress2@domain.com") };
const std::vector<MessageAddress> bcc = {};
const auto attachment = { Attachment("C:\\Temp\\test.png", "test image.png") };
HTMLMessage msg(from, to, subject, body, cc, bcc, attachment);

client.sendMail(msg);
```

#### Send a plaintext email via a secure server (forced)

*You will need to include cpp/forcedsecuresmtpclient.hpp*

```c++
ForcedSecureSMTPClient client("<your smtp server address>", 465);
client.setCredentials(Credential("myfromaddress@test.com", "mypassword"));

PlaintextMessage msg(MessageAddress("myfromaddress@test.com", "Test Address Display"),
    { MessageAddress("youraddress@domain.com", "Another Address display") },
    "This is a test (Subject)",
    "Hello\nHow are you?");

client.sendMail(msg);
}
```

## Complete communication log

The library keeps each exchange between the client and the server in the
communication log for easy diagnosis in the event of a communication problem.

Here's is an example communication log of a successful email send :

```log
c: Trying to connect to smtp.gmail.com on port 587
s: 220 smtp.gmail.com ESMTP v2-20020a05620a440200b006fed2788751sm17411101qkp.76 - gsmtp
c: Connected!
c: ehlo localhost\r\n
s: 250-smtp.gmail.com at your service, [129.222.207.110]
250-SIZE 35882577
250-8BITMIME
250-STARTTLS
250-ENHANCEDSTATUSCODES
250-PIPELINING
250-CHUNKING
250 SMTPUTF8
c: Info: STARTTLS is available by the server, the communication will be encrypted.
c: STARTTLS\r\n
s: 220 2.0.0 Ready to start TLS
c: <Start TLS negotiation>
c & s: <Negotiate a TLS session>
c & s: <Check result of negotiation>
c: TLS session ready!
c: Contacting the server again but via the secure channel...
c: ehlo localhost\r\n
s: 250-smtp.gmail.com at your service, [129.222.207.110]
250-SIZE 35882577
250-8BITMIME
250-AUTH LOGIN PLAIN XOAUTH2 PLAIN-CLIENTTOKEN OAUTHBEARER XOAUTH
250-ENHANCEDSTATUSCODES
250-PIPELINING
250-CHUNKING
250 SMTPUTF8
c: AUTH PLAIN ***************\r\n
s: 235 2.7.0 Accepted
c: MAIL FROM: <Test Address Display yourgmailaddress@gmail.com>\r\n
s: 250 2.1.0 OK v2-20020a05620a440200b006fed2788751sm17411101qkp.76 - gsmtp
c: RCPT TO: <youremailaddress@localhost>\r\n
s: 250 2.1.5 OK v2-20020a05620a440200b006fed2788751sm17411101qkp.76 - gsmtp
c: DATA\r\n
s: 354  Go ahead v2-20020a05620a440200b006fed2788751sm17411101qkp.76 - gsmtp
c: From: yourgmailaddress@gmail.com\r\n
c: To: youremailaddress@localhost\r\n
c: Subject: This is a test (Subject)\r\n
c: Content-Type: multipart/mixed; boundary=sep\r\n\r\n
c: --sep\r\nContent-Type: text/html; charset=UTF-8\r\n\r\n<html><body><p>Body sample</p></body></html>\r\n
c: \r\n.\r\n
s: 250 2.0.0 OK  1672495787 v2-20020a05620a440200b006fed2788751sm17411101qkp.76 - gsmtp
c: QUIT\r\n
Operation completed!
```

## Unit tests
[How to run the unit tests](https://github.com/jeremydumais/CPP-SMTPClient-library/wiki/Run-the-unit-tests)

## Documentation

See the classes documentation [here](https://github.com/jeremydumais/CPP-SMTPClient-library/wiki/Classes-Documentation)

