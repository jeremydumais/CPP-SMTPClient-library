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
	/** @brief The HTMLMessage class represents an email message in
	 *  HTML format. 
	 */
	class HTMLMESSAGE_API HTMLMessage : public Message
	{
	public:		
		/**
		 *  @brief  Construct a new HTMLMessage. 
		 *  @param pFrom The sender email address of the message.
		 *  @param pTo The recipient email address of the message.
		 *  @param pSubject The subject of the message.
		 *  @param pBody The content of the message. 
		 *  @param pCc The carbon-copy recipient email address.
		 *  @param pBcc The blind carbon-copy recipient email address.
		 *  @param pAttachments The attachments array of the message
		 *  @param pAttachmentsSize The number of attachments in the array.
		 */
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
	};
} // namespace jed_utils

#endif
