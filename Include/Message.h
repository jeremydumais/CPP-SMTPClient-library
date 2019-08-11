#ifndef MESSAGE_H
#define MESSAGE_H

#include "Attachment.h"
#include "MessageAddress.h"
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
			const std::string &pSubject,
			const std::string &pBody,
			const std::vector<MessageAddress> &pCc = std::vector<MessageAddress>(),
			const std::vector<MessageAddress> &pBcc = std::vector<MessageAddress>(),
			const std::vector<Attachment> &pAttachments = std::vector<Attachment>());
		Message(const MessageAddress &pFrom,
			const std::vector<MessageAddress> &pTo,
			const std::string &pSubject,
			const std::string &pBody,
			const std::vector<MessageAddress> &pCc = std::vector<MessageAddress>(),
			const std::vector<MessageAddress> &pBcc = std::vector<MessageAddress>(),
			const std::vector<Attachment> &pAttachments = std::vector<Attachment>());
		virtual ~Message() = default;
        Message(const Message& other) = default; //Copy constructor
        Message& operator=(const Message& other) = default; //Copy assignment
        Message(Message&&) noexcept = default; //Move constructor
        Message& operator=(Message&&) noexcept = default; //Move assignement
	 	virtual const std::string getMimeType() const = 0;
		const MessageAddress &getFrom() const;
		const std::vector<MessageAddress> &getTo() const;
		size_t getToCount() const;
		const std::string &getSubject() const;
		const std::string &getBody() const;
		const std::vector<MessageAddress> &getCc() const;
		size_t getCcCount() const;
		const std::vector<MessageAddress> &getBcc() const;
		size_t getBccCount() const;
		const std::vector<Attachment> &getAttachments() const;
		size_t getAttachmentsCount() const;
	protected:
		MessageAddress mFrom;
		std::vector<MessageAddress> mTo;
		std::vector<MessageAddress> mCc;
		std::vector<MessageAddress> mBcc;
		std::string mSubject;
		std::string mBody;
		std::vector<Attachment> mAttachments;
	};
} //namespace jed_utils

#endif
