#include "../Include/HTMLMessage.h"

using namespace jed_utils;
using namespace std;

html_message::html_message(message_address from,
	vector<message_address> *to,
	string subject,
	string body,
	vector<message_address> *cc,
	vector<message_address> *bcc,
	std::vector<attachment> *attachments) :
	message(from, to, subject, body, cc, bcc, attachments)
{
}

string html_message::get_mimetype()
{
	return "text/html";
}