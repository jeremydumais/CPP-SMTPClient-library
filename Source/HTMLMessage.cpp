#include "../Include/HTMLMessage.h"

using namespace std;

namespace jed_utils
{
	html_message::html_message(message_address from,
		message_address to,
		const char *subject,
		const char *body,
		message_address *cc,
		message_address *bcc,
		attachment attachments[],
		const unsigned int attachments_size) :
		message(from, to, subject, body, cc, bcc, attachments, attachments_size)
	{
	}

	html_message::html_message(message_address from,
		message_address to[],
		const unsigned int to_size,
		const char *subject,
		const char *body,
		message_address cc[],
		const unsigned int cc_size,
		message_address bcc[],
		const unsigned int bcc_size,
		attachment attachments[],
		const unsigned int attachments_size) :
		message(from, to, to_size, subject, body, cc, cc_size, bcc, bcc_size, attachments, attachments_size)
	{
	}

	const char *html_message::get_mimetype()
	{
		return "text/html";
	}
}