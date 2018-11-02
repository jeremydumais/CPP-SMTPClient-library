#ifndef MESSAGE_H
#define MESSAGE_H

#include <cstring>
#include "MessageAddress.h"
#include "Attachment.h"
#include <vector>

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
			message_address to,
			const char *subject,
			const char *body,
			message_address *cc = nullptr,
			message_address *bcc = nullptr,
			attachment attachments[] = nullptr,
			const unsigned int attachments_size = 0);
		message(message_address from,
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
		message(const message &);
		~message();
		const message& operator=(const message &msg);
		virtual const char *get_mimetype() = 0;
		const message_address get_from() const;
		const message_address *get_to_ptr() const;
		const unsigned int get_to_count() const;
		const char *get_subject() const;
		const char *get_body() const;
		const attachment *get_attachments_ptr() const;
		const unsigned int get_attachments_count() const;
	protected:
		message_address from;
		message_address *to = nullptr;
		unsigned int to_count = 0;
		message_address *cc = nullptr;
		unsigned int cc_count = 0;
		message_address *bcc = nullptr;
		unsigned int bcc_count = 0;
		char *subject = nullptr;
		char *body = nullptr;
		attachment *attachments = nullptr;
		unsigned int attachments_count = 0;
	};
}

#endif