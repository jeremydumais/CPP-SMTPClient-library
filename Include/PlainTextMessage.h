#ifndef PLAINTEXTMESSAGE_H
#define PLAINTEXTMESSAGE_H

#include "Message.h"
#include <string>

#ifdef _WIN32
	#ifdef SMTPCLIENT_EXPORTS  
		#define PLAINTEXTMESSAGE_API __declspec(dllexport)   
	#else  
		#define PLAINTEXTMESSAGE_API __declspec(dllimport)   
	#endif
#else
	#define PLAINTEXTMESSAGE_API
#endif

namespace jed_utils
{
	class PLAINTEXTMESSAGE_API PlaintextMessage : public Message
	{
	public:
		PlaintextMessage(const MessageAddress &pFrom,
			const MessageAddress &pTo,
			const std::string &pSubject,
			const std::string &pBody,
			const std::vector<MessageAddress> &pCc = std::vector<MessageAddress>(),
			const std::vector<MessageAddress> &pBcc = std::vector<MessageAddress>(),
			const std::vector<Attachment> &pAttachments = std::vector<Attachment>());
		PlaintextMessage(const MessageAddress &pFrom,
			const std::vector<MessageAddress> &pTo,
			const std::string &pSubject,
			const std::string &pBody,
			const std::vector<MessageAddress> &pCc = std::vector<MessageAddress>(),
			const std::vector<MessageAddress> &pBcc = std::vector<MessageAddress>(),
			const std::vector<Attachment> &pAttachments = std::vector<Attachment>());
		const std::string getMimeType() const override;
	};
} // namespace jed_utils

#endif
