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
	class HTMLMESSAGE_API html_message : public message
	{
	public:
		html_message(message_address from,
			std::vector<message_address> *to,
			std::string subject,
			std::string body,
			std::vector<message_address> *cc = NULL,
			std::vector<message_address> *bcc = NULL,
			std::vector<attachment> *attachments = NULL);
		virtual std::string get_mimetype();
	};
}

#endif