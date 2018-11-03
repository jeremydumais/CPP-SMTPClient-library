#Jed# C++ SMTP Client Library

##Jed# C++ SMTP Client Library is a simple SMTP client library built in C++.

###SmtpClient class

####Available methods
```c++
SmtpClient(const char *pServerName, const unsigned int pPort);
void sendMail(message *pMsg);
const char *getServerReply() const;
```	

###MessageAddress class

####Available methods
```c++
MessageAddress(const char *pEmailAddress, const char *pDisplayName = "");
operator std::string() const;
const char *getEmailAddress() const;
const char *getDisplayName() const;
```	

###Attachment class

####Available methods
```c++
Attachment(const char *pFilename, const char *pName = "");
const char *getName() const;
const char *getFilename() const;
const char *getBase64EncodedFile() const;
const char *getMimeType() const;
```	

###PlaintextMessage class

####Available methods
```c++
PlaintextMessage(MessageAddress from,
	MessageAddress to,
	const char *subject,
	const char *body,
	MessageAddress *cc = nullptr,
	MessageAddress *bcc = nullptr,
	attachment attachments[] = nullptr,
	const unsigned int attachments_size = 0);
PlaintextMessage(MessageAddress from,
	MessageAddress to[],
	const unsigned int to_size,
	const char *subject,
	const char *body,
	MessageAddress cc[] = nullptr,
	const unsigned int cc_size = 0,
	MessageAddress bcc[] = nullptr,
	const unsigned int bcc_size = 0,
	attachment attachments[] = nullptr,
	const unsigned int attachments_size = 0);
const char *getMimeType();
const MessageAddress getFrom() const;
const MessageAddress *getToPtr() const;
const unsigned int getToCount() const;
const MessageAddress *getCcPtr() const;
const unsigned int getCcCount() const;
const MessageAddress *getBccPtr() const;
const unsigned int getBccCount() const;
const char *getSubject() const;
const char *getBody() const;
const attachment *getAttachmentsPtr() const;
const unsigned int getAttachmentsCount() const;
```	

###HTMLMessage class

####Available methods
```c++
HTMLMessage(MessageAddress from,
	MessageAddress to,
	const char *subject,
	const char *body,
	MessageAddress *cc = nullptr,
	MessageAddress *bcc = nullptr,
	attachment attachments[] = nullptr,
	const unsigned int attachments_size = 0);
HTMLMessage(MessageAddress from,
	MessageAddress to[],
	const unsigned int to_size,
	const char *subject,
	const char *body,
	MessageAddress cc[] = nullptr,
	const unsigned int cc_size = 0,
	MessageAddress bcc[] = nullptr,
	const unsigned int bcc_size = 0,
	attachment attachments[] = nullptr,
	const unsigned int attachments_size = 0);
const char *getMimeType();
const MessageAddress getFrom() const;
const MessageAddress *getToPtr() const;
const unsigned int getToCount() const;
const MessageAddress *getCcPtr() const;
const unsigned int getCcCount() const;
const MessageAddress *getBccPtr() const;
const unsigned int getBccCount() const;
const char *getSubject() const;
const char *getBody() const;
const attachment *getAttachmentsPtr() const;
const unsigned int getAttachmentsCount() const;
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
	SmtpClient *client = new SmtpClient("<your smtp server address>", 25);
	try
	{
		PlaintextMessage msg(MessageAddress("myfromaddress@test.com", "Test Address Display"),
			MessageAddress("youraddress@domain.com")
			"This is a test (Subject)",
			"Hello\nHow are you?");

		client->sendMail(&msg);
		cout << client->getServerReply() << endl;
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
	SmtpClient *client = new SmtpClient("<your smtp server address>", 25);
	try
	{
		const int ATTACHMENT_COUNT = 1;
		const int TOADDR_COUNT = 2;

		Attachment att1[ATTACHMENT_COUNT] = { Attachment("C:\Temp\test.png", "test image.png") };

		MessageAddress to_addr[TOADDR_COUNT] = { MessageAddress("youraddress@domain.com"), 
		MessageAddress("youraddress2@domain.com")
		};

		HTMLMessage msg(MessageAddress("myfromaddress@test.com", "Test Address Display"),
			to_addr, TOADDR_COUNT,
			"This is a test (Subject)",
			"<html><body><h1>Hello,</h1><br/><br/>How are you?</body></html>", nullptr, 0, nullptr, 0, att1, ATTACHMENT_COUNT);

		client->sendMail(&msg);
		cout << client->getServerReply() << endl;
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
	delete client;
    return 0;
}
```
