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
	class PLAINTEXTMESSAGE_API plaintext_message : public message
	{
	public:
		plaintext_message(message_address from,
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