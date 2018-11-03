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
		SmtpClient(const std::string &pServerName, const unsigned int pPort);
		~SmtpClient();
		void sendMail(const Message &pMsg);
		const std::string &getServerReply() const;
	protected:
		std::string *mServerName;
		unsigned int mPort;
		std::string *mServerReply;
		void writeCommand(const unsigned int sock,
			const std::string &str,
			const std::string &arg,
			const bool ask_for_reply = true);
		std::string createAttachmentsText(const std::vector<Attachment> &pAttachments);
	};
}

#endif