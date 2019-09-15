# Jed# C++ SMTP Client Library

## A simple SMTP client library built in C++.

### SmtpClient class

#### Available methods
```c++
SmtpClient(const char *pServerName, unsigned int pPort);
void sendMail(const Message &pMsg);
const char *getServerReply() const;
```	

### MessageAddress class

#### Available methods
```c++
explicit MessageAddress(const char *pEmailAddress, const char *pDisplayName = "");
explicit operator std::string() const;
const char *getEmailAddress() const;
const char *getDisplayName() const;
```	

### Attachment class

#### Available methods
```c++
explicit Attachment(const char *pFilename, const char *pName = "");
const char *getName() const;
const char *getFilename() const;
const char *getBase64EncodedFile() const;
const char *getMimeType() const;
```	

### PlaintextMessage class

#### Available methods
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

### HTMLMessage class

#### Available methods
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

#### Here's some examples

##### Send a plaintext email

```c++
#include "SMTPClient.h"
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

		client.sendMail(msg);
		cout << client.getServerReply() << endl;
		cout << "Operation completed!" << endl;
	}
	catch (CommunicationError &err)
	{
		cerr << err.what() << endl;
	}
	catch (AttachmentError &err)
	{
		cerr << err.what() << endl;
	}
    return 0;
}
```

##### Send an html email to 2 recipients with an attachment

```c++
#include "SMTPClient.h"
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

		client.sendMail(msg);
		cout << client.getServerReply() << endl;
		cout << "Operation completed!" << endl;
	}
	catch (CommunicationError &err)
	{
		cerr << err.what() << endl;
	}
	catch (AttachmentError &err)
	{
		cerr << err.what() << endl;
	}
    return 0;
}
```
