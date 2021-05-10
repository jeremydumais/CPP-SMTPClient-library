#ifndef MESSAGE_H
#define MESSAGE_H

#include "attachment.h"
#include "messageaddress.h"
#include <cstring>
#include <vector>

#ifdef _WIN32
	#ifdef SMTPCLIENT_EXPORTS  
		#define MESSAGE_API __declspec(dllexport)   
	#else  
		#define MESSAGE_API __declspec(dllimport)   
	#endif
#else
	#define MESSAGE_API
#endif

namespace jed_utils
{
	class MESSAGE_API Message
	{
	public:
		Message(const MessageAddress &pFrom,
			const MessageAddress &pTo,
			const char *pSubject,
			const char *pBody,
			const MessageAddress *pCc = nullptr,
			const MessageAddress *pBcc = nullptr,
			const Attachment pAttachments[] = nullptr,
			size_t pAttachmentsSize = 0);
		Message(const MessageAddress &pFrom,
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
		virtual ~Message();
        Message(const Message &other); //Copy constructor
        Message& operator=(const Message &other); //Copy assignment
        Message(Message &&other) noexcept; //Move constructor
        Message& operator=(Message &&other) noexcept; //Move assignement
	 	virtual const char *getMimeType() const = 0;
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
	private:
		MessageAddress mFrom;
		MessageAddress **mTo;
		size_t mToCount;
		MessageAddress **mCc;
		size_t mCCCount;
		MessageAddress **mBcc;
		size_t mBCCCount;
		char *mSubject;
		char *mBody;
		Attachment **mAttachments;
		size_t mAttachmentCount;
	};
} //namespace jed_utils

#endif
