#include "../Include/Message.h"

using namespace std;

namespace jed_utils
{
	Message::Message(MessageAddress from,
		MessageAddress to,
		const char *subject,
		const char *body,
		MessageAddress *cc,
		MessageAddress *bcc,
		Attachment attachments[],
		const unsigned int attachments_size):
		mFrom(from)
	{
		mToCount = 1;
		this->mTo = new MessageAddress[mToCount];
		this->mTo[0] = to;

		this->mSubject = new char[strlen(subject) + 1];
		strcpy_s(this->mSubject, strlen(subject) + 1, subject);

		this->mBody = new char[strlen(body) + 1];
		strcpy_s(this->mBody, strlen(body) + 1, body);

		if (cc)
		{
			mCcCount = 1;
			this->mCc = new MessageAddress[mCcCount];
			this->mCc[0] = *cc;
		}

		if (bcc)
		{
			mBccCount = 1;
			this->mBcc = new MessageAddress[mCcCount];
			this->mBcc[0] = *bcc;
		}

		if (attachments)
		{
			mAttachmentsCount = attachments_size;
			this->mAttachments = new Attachment[mAttachmentsCount];
			for (unsigned int index = 0; index < attachments_size; index++)
				this->mAttachments[index] = attachments[index];
		}
	}

	Message::Message(MessageAddress from,
		MessageAddress to[],
		const unsigned int to_size,
		const char *subject,
		const char *body,
		MessageAddress cc[],
		const unsigned int cc_size,
		MessageAddress bcc[],
		const unsigned int bcc_size,
		Attachment attachments[],
		const unsigned int attachments_size)
		: mFrom(from)
	{
		mToCount = to_size;
		this->mTo = new MessageAddress[mToCount];
		for (unsigned int index = 0; index < to_size; index++)
			this->mTo[index] = to[index];

		this->mSubject = new char[strlen(subject) + 1];
		strcpy_s(this->mSubject, strlen(subject) + 1, subject);

		this->mBody = new char[strlen(body) + 1];
		strcpy_s(this->mBody, strlen(body) + 1, body);

		if (cc)
		{
			mCcCount = cc_size;
			this->mCc = new MessageAddress[mCcCount];
			for (unsigned int index = 0; index < cc_size; index++)
				this->mCc[index] = cc[index];
		}

		if (bcc)
		{
			mBccCount = bcc_size;
			this->mBcc = new MessageAddress[mBccCount];
			for (unsigned int index = 0; index < bcc_size; index++)
				this->mBcc[index] = bcc[index];
		}

		if (attachments)
		{
			mAttachmentsCount = attachments_size;
			this->mAttachments = new Attachment[mAttachmentsCount];
			for (unsigned int index = 0; index < attachments_size; index++)
				this->mAttachments[index] = attachments[index];
		}
	}

	Message::Message(const Message &pItem)
	{
		mFrom = pItem.mFrom;

		mToCount = pItem.mToCount;
		mTo = new MessageAddress[mToCount];
		copy(pItem.mTo, pItem.mTo + mToCount, mTo);

		mSubject = new char[strlen(pItem.mSubject) + 1];
		memcpy(mSubject, pItem.mSubject, strlen(pItem.mSubject) + 1);

		mBody = new char[strlen(pItem.mBody) + 1];
		memcpy(mBody, pItem.mBody, strlen(pItem.mBody) + 1);

		mCcCount = pItem.mCcCount;
		if (mCcCount > 0)
		{
			mCc = new MessageAddress[mCcCount];
			copy(pItem.mCc, pItem.mCc + mCcCount, mCc);
		}

		mBccCount = pItem.mBccCount;
		if (mBccCount > 0)
		{
			mBcc = new MessageAddress[mBccCount];
			copy(pItem.mBcc, pItem.mBcc + mBccCount, mBcc);
		}

		mAttachmentsCount = pItem.mAttachmentsCount;
		if (mAttachmentsCount > 0)
		{
			mAttachments = new Attachment[mAttachmentsCount];
			copy(pItem.mAttachments, pItem.mAttachments + mAttachmentsCount, mAttachments);
		}
	}

	Message::~Message()
	{
		delete[] mTo;
		delete mSubject;
		delete mBody;
		if (mCc)
			delete[] mCc;
		if (mBcc)
			delete[] mBcc;
		if (mAttachments)
			delete[] mAttachments;
	}

	const Message& Message::operator=(const Message &msg)
	{
		if (this != &msg)
		{
			delete[] mTo;
			delete mSubject;
			delete mBody;
			if (mCc)
			{
				delete[] mCc;
				mCc = NULL;
			}
			if (mBcc)
			{
				delete[] mBcc;
				mBcc = NULL;
			}

			if (mAttachments)
			{
				delete[] mAttachments;
				mAttachments = NULL;
			}

			mFrom = msg.mFrom;

			mToCount = msg.mToCount;
			mTo = new MessageAddress[mToCount];
			copy(msg.mTo, msg.mTo + mToCount, mTo);

			mSubject = new char[strlen(msg.mSubject) + 1];
			memcpy(mSubject, msg.mSubject, strlen(msg.mSubject) + 1);

			mBody = new char[strlen(msg.mBody) + 1];
			memcpy(mBody, msg.mBody, strlen(msg.mBody) + 1);

			mCcCount = msg.mCcCount;
			if (mCcCount > 0)
			{
				mCc = new MessageAddress[mCcCount];
				copy(msg.mCc, msg.mCc + mCcCount, mCc);
			}

			mBccCount = msg.mBccCount;
			if (mBccCount > 0)
			{
				mBcc = new MessageAddress[mBccCount];
				copy(msg.mBcc, msg.mBcc + mBccCount, mBcc);
			}

			mAttachmentsCount = msg.mAttachmentsCount;
			if (mAttachmentsCount > 0)
			{
				mAttachments = new Attachment[mAttachmentsCount];
				copy(msg.mAttachments, msg.mAttachments + mAttachmentsCount, mAttachments);
			}
		}
		return *this;
	}

	const MessageAddress *Message::getToPtr() const
	{
		return mTo;
	}

	const unsigned int Message::getToCount() const
	{
		return mToCount;
	}

	const char *Message::getSubject() const
	{
		return mSubject;
	}

	const char *Message::getBody() const
	{
		return mBody;
	}

	const MessageAddress *Message::getCcPtr() const
	{
		return mCc;
	}

	const unsigned int Message::getCcCount() const
	{
		return mCcCount;
	}

	const MessageAddress *Message::getBccPtr() const
	{
		return mBcc;
	}

	const unsigned int Message::getBccCount() const
	{
		return mBccCount;
	}

	const MessageAddress Message::getFrom() const
	{
		return mFrom;
	}

	const Attachment *Message::getAttachmentsPtr() const
	{
		return mAttachments;
	}

	const unsigned int Message::getAttachmentsCount() const
	{
		return mAttachmentsCount;
	}
}