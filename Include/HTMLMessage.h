#ifndef HTMLMESSAGE_H
#define HTMLMESSAGE_H

#include <string>
#include "Message.h"

#pragma once  

#ifdef SMTPCLIENT_EXPORTS  
#define HTMLMESSAGE_API __declspec(dllexport)   
#else  
#define HTMLMESSAGE_API __declspec(dllimport)   
#endif  

namespace jed_utils
{
	class HTMLMESSAGE_API HTMLMessage : public Message
	{
	public:
		HTMLMessage(MessageAddress from,
			MessageAddress to,
			const char *subject,
			const char *body,
			MessageAddress *cc = nullptr,
			MessageAddress *bcc = nullptr,
			Attachment attachments[] = nullptr,
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
			Attachment attachments[] = nullptr,
			const unsigned int attachments_size = 0);
		virtual const char *getMimeType();
	};
}

#endif