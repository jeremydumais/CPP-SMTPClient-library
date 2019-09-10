#ifndef PLAINTEXTMESSAGE_H
#define PLAINTEXTMESSAGE_H

#include "message.h"
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
			const char *pSubject,
			const char *pBody,
			const MessageAddress *pCc = nullptr,
			const MessageAddress *pBcc = nullptr,
			const Attachment *pAttachments = nullptr,
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
	};
} // namespace jed_utils

#endif
