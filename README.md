# Jed# C++ SMTP Client Library

## A simple SMTP client library built in C++ that support authentication and TLS  1.2 encryption

### How to build the SMTP client or integrate it in your application

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
		cout << client.getServerReply() << endl;
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
		cout << client.getServerReply() << endl;
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

#
## Documentation
### Classes

#### SSLSmtpClient class
##### *OpenSSL is required

##### Available methods
```c++
SSLSmtpClient(const char *pServerName, unsigned int pPort);
unsigned int getCommandTimeout() const;
const char *getCommunicationLog() const;
const Credential *getCredentials() const;
const char *getServerName() const;
unsigned int getServerPort() const;
int sendMail(const Message &pMsg);
void setCommandTimeout(unsigned int pTimeOutInSeconds);
void setCredentials(const Credential &pCredential);
void setServerName(const char *pServerName);
void setServerPort(unsigned int pPort);
```

##### sendMail method Return Codes

See the files [socketerrors.h](https://github.com/jeremydumais/CPP-SMTPClient-library/blob/master/socketerrors.h) and [sslerrors.h](https://github.com/jeremydumais/CPP-SMTPClient-library/blob/master/sslerrors.h)

#### SmtpClient class

##### Available methods
```c++
SmtpClient(const char *pServerName, unsigned int pPort);
int sendMail(const Message &pMsg);
const char *getServerReply() const;
```

##### sendMail method Return Codes

| Code  | Status Text
|-------|-----------------------------------------------------
|   0   | Success
|   1   | Socket startup error. See the return code via cerr
|   2   | Socket getaddrinfo error. See the getaddrinfo return code via cerr
|   3   | Socket connect error. See the connect return code via cerr
|   4   | Socket close error. See the closesocket return code via cerr
|   5   | Socket send error. See the send error via cerr
|   6   | Unable to load the attachment

#### MessageAddress class

##### Available methods
```c++
explicit MessageAddress(const char *pEmailAddress, const char *pDisplayName = "");
explicit operator std::string() const;
const char *getEmailAddress() const;
const char *getDisplayName() const;
```	

#### Attachment class

##### Available methods
```c++
explicit Attachment(const char *pFilename, const char *pName = "");
const char *getName() const;
const char *getFilename() const;
const char *getBase64EncodedFile() const;
const char *getMimeType() const;
```	

#### PlaintextMessage class

##### Available methods
```c++
PlaintextMessage(const MessageAddress &pFrom,
	const MessageAddress &pTo,
	const char *pSubject,
	const char *pBody,
	const MessageAddress *pCc = nullptr,
	const MessageAddress *pBcc = nullptr,
	const Attachment pAttachments[] = nullptr,
	size_t pAttachmentsSize = 0);
PlaintextMessage(const MessageAddress &pFrom,
	const MessageAddress pTo[],
	size_t pToCount,
	const char *pSubject,
	const char *pBody,
	const MessageAddress pCc[] = nullptr,
	size_t pCcCount = 0,
	const MessageAddress pBcc[] = nullptr,
	size_t pBccCount = 0,
	const Attachment pAttachments[] = nullptr,
	size_t pAttachmentsSize = 0);
const char *getMimeType() const override;
const MessageAddress &getFrom() const;
MessageAddress **getTo() const;
size_t getToCount() const;
const char *getSubject() const;
const char *getBody() const;
MessageAddress **getCc() const;
size_t getCcCount() const;
MessageAddress **getBcc() const;
size_t getBccCount() const;
Attachment **getAttachments() const;
size_t getAttachmentsCount() const;
```	

#### HTMLMessage class

##### Available methods
```c++
HTMLMessage(const MessageAddress &pFrom,
	const MessageAddress &pTo,
	const char *pSubject,
	const char *pBody,
	const MessageAddress *pCc = nullptr,
	const MessageAddress *pBcc = nullptr,
	const Attachment *pAttachments = nullptr,
	size_t pAttachmentsSize = 0);
HTMLMessage(const MessageAddress &pFrom,
	const MessageAddress pTo[],
	size_t pToCount,
	const char *pSubject,
	const char *pBody,
	const MessageAddress pCc[] = nullptr,
	size_t pCcCount = 0,
	const MessageAddress pBcc[] = nullptr,
	size_t pBccCount = 0,
	const Attachment pAttachments[] = nullptr,
	size_t pAttachmentsSize = 0);
const char *getMimeType() const override;
const MessageAddress &getFrom() const;
MessageAddress **getTo() const;
size_t getToCount() const;
const char *getSubject() const;
const char *getBody() const;
MessageAddress **getCc() const;
size_t getCcCount() const;
MessageAddress **getBcc() const;
size_t getBccCount() const;
Attachment **getAttachments() const;
size_t getAttachmentsCount() const;
```	

#### Credential class

##### Available methods
```c++
Credential(const char *pUsername, const char *pPassword);
const char *getUsername() const;
const char *getPassword() const;
void setUsername(const char *pUsername);
void setPassword(const char *pPassword);
```