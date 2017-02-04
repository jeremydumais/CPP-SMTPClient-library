#include "../Include/PlainTextMessage.h"

using namespace jed_utils;
using namespace std;

plaintext_message::plaintext_message(message_address from,
	vector<message_address> *to,
	string subject,
	string body,
	vector<message_address> *cc,
	vector<message_address> *bcc,
	std::vector<attachment> *attachments) :
	message(from, to, subject, body, cc, bcc, attachments)
{
}

string plaintext_message::get_mimetype()
{
	return "text/plain";
}