#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>
#include "MessageAddress.h"
#include "Attachment.h"
#include <vector>

#pragma once  

#ifdef SMTPCLIENT_EXPORTS  
#define MESSAGE_API __declspec(dllexport)   
#else  
#define MESSAGE_API __declspec(dllimport)   
#endif  

namespace jed_utils
{
	class MESSAGE_API message
	{
	public:
		message(message_address from,
			std::vector<message_address> *to,
			std::string subject,
			std::string body,
			std::vector<message_address> *cc = NULL,
			std::vector<message_address> *bcc = NULL,
			std::vector<attachment> *attachments = NULL);
		message(const message &);
		~message();
		const message& operator=(const message &msg);
		virtual std::string get_mimetype() = 0;
		const message_address get_from() const;
		const message_address *get_to_ptr() const;
		const unsigned int get_to_count() const;
		const std::string get_subject() const;
		const std::string get_body() const;
		const attachment *get_attachments_ptr() const;
		const unsigned int get_attachments_count() const;
	protected:
		message_address from;
		message_address *to = NULL;
		unsigned int to_count = 0;
		message_address *cc = NULL;
		unsigned int cc_count = 0;
		message_address *bcc = NULL;
		unsigned int bcc_count = 0;
		char *subject = NULL;
		char *body = NULL;
		attachment *attachments = NULL;
		unsigned int attachments_count = 0;
	};
}

#endif