#ifndef PLAINTEXTMESSAGE_H
#define PLAINTEXTMESSAGE_H

#include <string>
#include "Message.h"

#pragma once  

#ifdef SMTPCLIENT_EXPORTS  
#define PLAINTEXTMESSAGE_API __declspec(dllexport)   
#else  
#define PLAINTEXTMESSAGE_API __declspec(dllimport)   
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
		virtual const std::string getMimeType() const;
	};
}

#endif