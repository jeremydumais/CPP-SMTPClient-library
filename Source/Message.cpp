#include "../Include/Message.h"

using namespace std;

namespace jed_utils
{
	message::message(message_address from,
		message_address to,
		const char *subject,
		const char *body,
		message_address *cc,
		message_address *bcc,
		attachment attachments[],
		const unsigned int attachments_size):
		from(from)
	{
		to_count = 1;
		this->to = new message_address[to_count];
		this->to[0] = to;

		this->subject = new char[strlen(subject) + 1];
		strcpy_s(this->subject, strlen(subject) + 1, subject);

		this->body = new char[strlen(body) + 1];
		strcpy_s(this->body, strlen(body) + 1, body);

		if (cc)
		{
			cc_count = 1;
			this->cc = new message_address[cc_count];
			this->cc[0] = *cc;
		}

		if (bcc)
		{
			bcc_count = 1;
			this->bcc = new message_address[bcc_count];
			this->bcc[0] = *bcc;
		}

		if (attachments)
		{
			attachments_count = attachments_size;
			this->attachments = new attachment[attachments_count];
			for (unsigned int index = 0; index < attachments_size; index++)
				this->attachments[index] = attachments[index];
		}
	}

	message::message(message_address from,
		message_address to[],
		const unsigned int to_size,
		const char *subject,
		const char *body,
		message_address cc[],
		const unsigned int cc_size,
		message_address bcc[],
		const unsigned int bcc_size,
		attachment attachments[],
		const unsigned int attachments_size)
		: from(from)
	{
		to_count = to_size;
		this->to = new message_address[to_count];
		for (unsigned int index = 0; index < to_size; index++)
			this->to[index] = to[index];

		this->subject = new char[strlen(subject) + 1];
		strcpy_s(this->subject, strlen(subject) + 1, subject);

		this->body = new char[strlen(body) + 1];
		strcpy_s(this->body, strlen(body) + 1, body);

		if (cc)
		{
			cc_count = cc_size;
			this->cc = new message_address[cc_count];
			for (unsigned int index = 0; index < cc_size; index++)
				this->cc[index] = cc[index];
		}

		if (bcc)
		{
			bcc_count = bcc_size;
			this->bcc = new message_address[bcc_count];
			for (unsigned int index = 0; index < bcc_size; index++)
				this->bcc[index] = bcc[index];
		}

		if (attachments)
		{
			attachments_count = attachments_size;
			this->attachments = new attachment[attachments_count];
			for (unsigned int index = 0; index < attachments_size; index++)
				this->attachments[index] = attachments[index];
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

	const char *message::get_subject() const
	{
		return subject;
	}

	const char *message::get_body() const
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
}