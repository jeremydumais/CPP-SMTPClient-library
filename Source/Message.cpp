#include "../Include/Message.h"

using namespace jed_utils;
using namespace std;

message::message(message_address from,
	vector<message_address> *to,
	string subject,
	string body,
	vector<message_address> *cc,
	vector<message_address> *bcc,
	vector<attachment> *attachments)
	: from(from)
{
	to_count = to->size();
	this->to = new message_address[to_count];
	int index = 0;
	for (vector<message_address>::iterator iter = (*to).begin(); iter != (*to).end(); iter++, index++)
		this->to[index] = *iter;

	const std::string::size_type size_subject = subject.size();
	this->subject = new char[size_subject + 1];
	memcpy(this->subject, subject.c_str(), size_subject + 1);

	const std::string::size_type size_body = body.size();
	this->body = new char[size_body + 1];
	memcpy(this->body, body.c_str(), size_body + 1);

	if (cc)
	{
		cc_count = cc->size();
		this->cc = new message_address[cc_count];
		index = 0;
		for (vector<message_address>::iterator iter = (*cc).begin(); iter != (*cc).end(); iter++, index++)
			this->cc[index] = *iter;
	}

	if (bcc)
	{
		bcc_count = bcc->size();
		this->bcc = new message_address[bcc_count];
		index = 0;
		for (vector<message_address>::iterator iter = (*bcc).begin(); iter != (*bcc).end(); iter++, index++)
			this->bcc[index] = *iter;
	}

	if (attachments)
	{
		attachments_count = attachments->size();
		this->attachments = new attachment[attachments_count];
		index = 0;
		for (vector<attachment>::iterator iter = (*attachments).begin(); iter != (*attachments).end(); iter++, index++)
			this->attachments[index] = *iter;
	}
}

message::message(const message &item)
{
	from = item.from;

	to_count = item.to_count;
	to = new message_address[to_count];
	copy(item.to, item.to + to_count, to);

	subject = new char[strlen(item.subject) + 1];
	memcpy(subject, item.subject, strlen(item.subject) + 1);

	body = new char[strlen(item.body) + 1];
	memcpy(body, item.body, strlen(item.body) + 1);

	cc_count = item.cc_count;
	if (cc_count > 0)
	{
		cc = new message_address[cc_count];
		copy(item.cc, item.cc + cc_count, cc);
	}

	bcc_count = item.bcc_count;
	if (bcc_count > 0)
	{
		bcc = new message_address[bcc_count];
		copy(item.bcc, item.bcc + bcc_count, bcc);
	}

	attachments_count = item.attachments_count;
	if (attachments_count > 0)
	{
		attachments = new attachment[attachments_count];
		copy(item.attachments, item.attachments + attachments_count, attachments);
	}
}

message::~message()
{
	delete[] to;
	delete subject;
	delete body;
	if (cc)
		delete[] cc;
	if (bcc)
		delete[] bcc;
	if (attachments)
		delete[] attachments;
}

const message& message::operator=(const message &msg)
{
	if (this != &msg)
	{
		delete[] to;
		delete subject;
		delete body;
		if (cc)
		{
			delete[] cc;
			cc = NULL;
		}
		if (bcc)
		{
			delete[] bcc;
			bcc = NULL;
		}

		if (attachments)
		{
			delete[] attachments;
			attachments = NULL;
		}
	
		from = msg.from;

		to_count = msg.to_count;
		to = new message_address[to_count];
		copy(msg.to, msg.to + to_count, to);

		subject = new char[strlen(msg.subject) + 1];
		memcpy(subject, msg.subject, strlen(msg.subject) + 1);

		body = new char[strlen(msg.body) + 1];
		memcpy(body, msg.body, strlen(msg.body) + 1);

		cc_count = msg.cc_count;
		if (cc_count > 0)
		{
			cc = new message_address[cc_count];
			copy(msg.cc, msg.cc + cc_count, cc);
		}

		bcc_count = msg.bcc_count;
		if (bcc_count > 0)
		{
			bcc = new message_address[bcc_count];
			copy(msg.bcc, msg.bcc + bcc_count, bcc);
		}

		attachments_count = msg.attachments_count;
		if (attachments_count > 0)
		{
			attachments = new attachment[attachments_count];
			copy(msg.attachments, msg.attachments + attachments_count, attachments);
		}
	}
	return *this;
}

const message_address *message::get_to_ptr() const
{
	return to;
}

const unsigned int message::get_to_count() const
{
	return to_count;
}

const std::string message::get_subject() const
{
	return subject;
}

const std::string message::get_body() const
{
	return body;
}

const message_address message::get_from() const
{
	return from;
}

const attachment *message::get_attachments_ptr() const
{
	return attachments;
}

const unsigned int message::get_attachments_count() const
{
	return attachments_count;
}