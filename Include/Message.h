#ifndef MESSAGE_H
#define MESSAGE_H

#include <cstring>
#include "MessageAddress.h"
#include "Attachment.h"
#include <vector>

#ifdef SMTPCLIENT_EXPORTS  
#define MESSAGE_API __declspec(dllexport)   
#else  
#define MESSAGE_API __declspec(dllimport)   
#endif  

namespace jed_utils
{
	class MESSAGE_API Message
	{
	public:
		Message(MessageAddress from,
			MessageAddress to,
			const char *subject,
			const char *body,
			MessageAddress *cc = nullptr,
			MessageAddress *bcc = nullptr,
			Attachment attachments[] = nullptr,
			const unsigned int attachments_size = 0);
		Message(MessageAddress from,
			MessageAddress to[],
			const unsigned int to_size,
			const char *subject,
			const char *body,
			MessageAddress cc[] = nullptr,
			const unsigned int cc_size = 0,
			MessageAddress bcc[] = nullptr,
			const unsigned int bcc_size = 0,
			Attachment attachments[] = nullptr,
			const unsigned int attachments_size = 0);
		Message(const Message &);
		~Message();
		const Message& operator=(const Message &msg);
		virtual const char *getMimeType() = 0;
		const MessageAddress getFrom() const;
		const MessageAddress *getToPtr() const;
		const unsigned int getToCount() const;
		const char *getSubject() const;
		const char *getBody() const;
		const MessageAddress *getCcPtr() const;
		const unsigned int getCcCount() const;
		const MessageAddress *getBccPtr() const;
		const unsigned int getBccCount() const;
		const Attachment *getAttachmentsPtr() const;
		const unsigned int getAttachmentsCount() const;
	protected:
		MessageAddress mFrom;
		MessageAddress *mTo = nullptr;
		unsigned int mToCount = 0;
		MessageAddress *mCc = nullptr;
		unsigned int mCcCount = 0;
		MessageAddress *mBcc = nullptr;
		unsigned int mBccCount = 0;
		char *mSubject = nullptr;
		char *mBody = nullptr;
		Attachment *mAttachments = nullptr;
		unsigned int mAttachmentsCount = 0;
	};
}

#endif