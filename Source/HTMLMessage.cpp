#include "../Include/HTMLMessage.h"

using namespace std;

namespace jed_utils
{
	HTMLMessage::HTMLMessage(MessageAddress from,
		MessageAddress to,
		const char *subject,
		const char *body,
		MessageAddress *cc,
		MessageAddress *bcc,
		Attachment attachments[],
		const unsigned int attachments_size) :
		Message(from, to, subject, body, cc, bcc, attachments, attachments_size)
	{
	}

	HTMLMessage::HTMLMessage(MessageAddress from,
		MessageAddress to[],
		const unsigned int to_size,
		const char *subject,
		const char *body,
		MessageAddress cc[],
		const unsigned int cc_size,
		MessageAddress bcc[],
		const unsigned int bcc_size,
		Attachment attachments[],
		const unsigned int attachments_size) :
		Message(from, to, to_size, subject, body, cc, cc_size, bcc, bcc_size, attachments, attachments_size)
	{
	}

	const char *HTMLMessage::getMimeType()
	{
		return "text/html";
	}
}