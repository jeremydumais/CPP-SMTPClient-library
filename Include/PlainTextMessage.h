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
			message_address to,
			const char *subject,
			const char *body,
			message_address *cc = nullptr,
			message_address *bcc = nullptr,
			attachment attachments[] = nullptr,
			const unsigned int attachments_size = 0);
		plaintext_message(message_address from,
			message_address to[],
			const unsigned int to_size,
			const char *subject,
			const char *body,
			message_address cc[] = nullptr,
			const unsigned int cc_size = 0,
			message_address bcc[] = nullptr,
			const unsigned int bcc_size = 0,
			attachment attachments[] = nullptr,
			const unsigned int attachments_size = 0);
		virtual const char *get_mimetype();
	};
}

#endif