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
	class SMTPCLIENT_API smtp_client
	{
	public:
		smtp_client(const std::string server_name, const unsigned int port);
		~smtp_client();
		void send_mail(message *msg);
		const std::string get_server_reply() const;
	protected:
		char *server_name;
		unsigned int port;
		char *server_reply;
		void write_command(const unsigned int sock,
			const std::string str,
			const std::string arg,
			const bool ask_for_reply = true);
		std::string create_attachments_text(const attachment *attachments, const unsigned int attachements_count);
	};
}

#endif