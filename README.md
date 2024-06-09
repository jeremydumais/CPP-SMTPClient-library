# Jed# C++ SMTP Client Library

[![Build status](https://github.com/jeremydumais/CPP-SMTPClient-library/actions/workflows/cmake.yml/badge.svg)](https://github.com/jeremydumais/CPP-SMTPClient-library/actions/workflows/cmake.yml)
![Latest version](https://img.shields.io/badge/latest_version-1.1.7-brightgreen)
![Dependencies](https://img.shields.io/badge/dependencies-openssl-brightgreen)

## A simple SMTP client library built in C++ that support authentication and secure connections (Opportunistic SSL/TLS and Forced SSL encryption).

##### For TLS 1.3 support you must build the library against OpenSSL 1.1.1

##### The library is cross-platform and has been tested on Linux and Windows.

### How to build the SMTP client or integrate it in your application

Follow this [link](https://github.com/jeremydumais/CPP-SMTPClient-library/wiki/How-to-build-the-SMTP-client-or-integrate-it-in-your-application) for a quick guide on how to build the SMTP client and integrate it in your application.

Follow these guides to build the library on [Windows](https://github.com/jeremydumais/CPP-SMTPClient-library/wiki/Build-the-CPP-SMTPClient-library-on-Windows)
and [Linux](https://github.com/jeremydumais/CPP-SMTPClient-library/wiki/Build-the-CPP-SMTPClient-library-on-Linux).

## ⬇ Download latest binaries

### Windows

<table>
<tr>
<th> Release </th>
<th> MD5 hash of smtpclient.dll </th>
</tr>

<tr>
<td>

[v1.1.7 (x64)](https://github.com/jeremydumais/CPP-SMTPClient-library/releases/download/v1.1.7/CPP-SMTPClient-Library.1.1.7.x64.zip)

</td>
<td>

fb041c2e377d6e399853b1fd4f0f2396

</td>
</tr>
<tr>
<td>

[v1.1.7 (x86)](https://github.com/jeremydumais/CPP-SMTPClient-library/releases/download/v1.1.7/CPP-SMTPClient-Library.1.1.7.x86.zip)

</td>
<td>

bb98d97a03451ff579226b0361c2a7ce

</td>
</tr>

<tr>
<td>

[v1.1.6 (x64)](https://github.com/jeremydumais/CPP-SMTPClient-library/releases/download/v1.1.6/CPP-SMTPClient-Library.1.1.6.x64.zip)

</td>
<td>

fc417d787a4533d3b6c99c1b5e852b5b

</td>
</tr>
<tr>
<td>

[v1.1.6 (x86)](https://github.com/jeremydumais/CPP-SMTPClient-library/releases/download/v1.1.6/CPP-SMTPClient-Library.1.1.6.x86.zip)

</td>
<td>

ffdd7f2adbf92b9a3dfd8bbf97c83008

</td>
</tr>

</table>

See the section
[Releases](https://github.com/jeremydumais/CPP-SMTPClient-library/releases)
for previous versions.

## 📰 What's new

- Version 1.1.8:
    - Some SMTP server send their list of supported extensions in multiple
buffers like Zoho Mail. The EHLO command when in uncrypted mode, now supports
receiving multiple buffers. In return, a delay of one second must be added for
each segment sent by the SMTP server. For SMTP servers that send the list of
supported extensions in a single segment like Gmail and Live, no additional
delay is added for the EHLO command. This doesn't affect the other commands.
    - Now when we send an email to multiple recipients (to or cc), the recipients
appears as a single mail header instead of multiple headers. The old method was
not RFC 5322 compliant.
- Version 1.1.7:
    - Added support for the XOAUTH2 authentication method.
This change has been made by rcosnita (https://github.com/rcosnita).
Many thanks!
    - Added a new flag in the different SMTP client classes to indicate whether we
want to send emails in batch (getBatchMode/setBatchMode). In this mode the connection to an
SMTP server will only be made once when the first email is sent and will
remain open until the client instance is destroy.
    - Added the authentication feature on the SMTPClient class.
    - Added a new flag on the ForcedSecureSMTPClient and OpportunisticSecureSMTPClient
to indicate whether we accept self signed certificate
(getAcceptSelfSignedCert/setAcceptSelfSignedCert).
    - Many more enhancements provided by ino-josh (https://github.com/ino-josh).
Many thanks!
- Version 1.1.6: Added support in the attachment class for Content-ID. It will
be really useful to uniquely identify and reference resources to embed in the
message.
This change has been made by hesa2020 (https://github.com/hesa2020).
Many thanks!

## ⚡️ Quickstart - The 3 client classes

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

## ⚙ How it works

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

![From in version 1.1.6+](https://img.shields.io/badge/From_in_version-1.1.6+-green)
- [Send an html email with an attachment using Content-ID via a secure server](#send-an-html-email-with-an-attachment-using-content-id-via-a-secured-server-opportunistic)

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

#### Send an html email with an attachment using Content-ID via a secured server (opportunistic)

*You will need to include cpp/htmlmessage.hpp*

```c++
OpportunisticSecureSMTPClient client("<your smtp server address>", 587);
client.setCredentials(Credential("myfromaddress@test.com", "mypassword"));

const MessageAddress from("myfromaddress@test.com", "Test Address Display");
const auto to = { MessageAddress("youraddress@domain.com") };
const auto subject = "This is a test (Subject)";
const auto body = "<html><body><img src='cid:a.png@test.com' /></body></html>";
const auto cc = { MessageAddress("youraddress2@domain.com") };
const std::vector<MessageAddress> bcc = {};
const auto attachment = { Attachment("C:\\Temp\\test.png", "test image.png", "a.png@test.com") };
HTMLMessage msg(from, to, subject, body, cc, bcc, attachment);

client.sendMail(msg);
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

## 🗝 Complete XOAUTH2 authentication example

We also provide a fully working example. See [send-mail.cpp](./src/cpp/example/send-mail.cpp).
Make sure you replace the username and password (access token) placeholders with correct values.

The example uses GMail smtp server with [XOauth2 authentication mechanism](https://developers.google.com/gmail/imap/xoauth2-protocol).

For testing purposes, you can obtain an OAuth access token for you gmail account by using the [OAuth 2.0 Playground](https://developers.google.com/oauthplayground/).
You can follow this procedure for more details: [Obtaining an access token for your gmail account](https://github.com/jeremydumais/CPP-SMTPClient-library/wiki/Obtain-An-Access-Token-Gmail)

## 🧪 Unit tests
[How to run the unit tests](https://github.com/jeremydumais/CPP-SMTPClient-library/wiki/Run-the-unit-tests)

## ❓ Documentation

See the classes documentation [here](https://github.com/jeremydumais/CPP-SMTPClient-library/wiki/Classes-Documentation)

## ⚖️ License

See [LICENSE](LICENSE)
