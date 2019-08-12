#ifndef HTMLMESSAGE_H
#define HTMLMESSAGE_H

#include "message.h"
#include <string>

#ifdef _WIN32
	#ifdef SMTPCLIENT_EXPORTS  
		#define HTMLMESSAGE_API __declspec(dllexport)   
	#else  
		#define HTMLMESSAGE_API __declspec(dllimport)   
	#endif
#else
	#define HTMLMESSAGE_API
#endif

namespace jed_utils
{
	class HTMLMESSAGE_API HTMLMessage : public Message
	{
	public:
		HTMLMessage(const MessageAddress &pFrom,
			const MessageAddress &pTo,
			const std::string &pSubject,
			const std::string &pBody,
			const std::vector<MessageAddress> &pCc = std::vector<MessageAddress>(),
			const std::vector<MessageAddress> &pBcc = std::vector<MessageAddress>(),
			const std::vector<Attachment> &pAttachments = std::vector<Attachment>());
		HTMLMessage(const MessageAddress &pFrom,
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
