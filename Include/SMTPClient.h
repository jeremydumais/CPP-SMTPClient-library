#ifndef SMTPCLIENT_H
#define SMTPCLIENT_H

#include <string>
#include "CommunicationError.h"
#include "AttachmentError.h"
#include "Attachment.h"
#include "MessageAddress.h"
#include "PlainTextMessage.h"
#include "HTMLMessage.h"
#include <vector>
#include <sstream>

#pragma once  

#ifdef SMTPCLIENT_EXPORTS  
#define SMTPCLIENT_API __declspec(dllexport)   
#else  
#define SMTPCLIENT_API __declspec(dllimport)   
#endif  

namespace jed_utils
{
	class SMTPCLIENT_API SmtpClient
	{
	public:
		SmtpClient(const char *pServerName, const unsigned int pPort);
		~SmtpClient();
		void sendMail(Message *pMsg);
		const char *getServerReply() const;
	protected:
		char *mServerName;
		unsigned int mPort;
		char *mServerReply;
		void writeCommand(const unsigned int sock,
			const std::string str,
			const std::string arg,
			const bool ask_for_reply = true);
		std::string createAttachmentsText(const Attachment *pAttachments, const unsigned int pAttachementsCount);
	};
}

#endif