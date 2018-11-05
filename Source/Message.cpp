#include "../Include/Message.h"

using namespace std;

namespace jed_utils
{
	Message::Message(const MessageAddress &pFrom,
		const MessageAddress &pTo,
		const string &pSubject,
		const string &pBody,
		const vector<MessageAddress> &pCc,
		const vector<MessageAddress> &pBcc,
		const vector<Attachment> &pAttachments):
		mFrom(pFrom)
	{
		mTo = new vector<MessageAddress>();
		mTo->push_back(pTo);
		mSubject = new string(pSubject);
		mBody = new string(pBody);

		mCc = new vector<MessageAddress>();
		copy(pCc.begin(), pCc.end(), mCc->begin());

		mBcc = new vector<MessageAddress>();
		copy(pBcc.begin(), pBcc.end(), mBcc->begin());

		mAttachments = new vector<Attachment>();
		copy(pAttachments.begin(), pAttachments.end(), mAttachments->begin());
	}

	Message::Message(const MessageAddress &pFrom,
		const vector<MessageAddress> &pTo,
		const string &pSubject,
		const string &pBody,
		const vector<MessageAddress> &pCc,
		const vector<MessageAddress> &pBcc,
		const vector<Attachment> &pAttachments)
		: mFrom(pFrom)
	{
		mTo = new vector<MessageAddress>();
		copy(pTo.begin(), pTo.end(), mTo->begin());

		mSubject = new string(pSubject);
		mBody = new string(pBody);

		mCc = new vector<MessageAddress>();
		copy(pCc.begin(), pCc.end(), mCc->begin());

		mBcc = new vector<MessageAddress>();
		copy(pBcc.begin(), pBcc.end(), mBcc->begin());

		mAttachments = new vector<Attachment>();
		copy(pAttachments.begin(), pAttachments.end(), mAttachments->begin());
	}

	Message::Message(const Message &pItem)
	: mFrom(pItem.mFrom)
	{
		mTo = new vector<MessageAddress>();
		copy(pItem.mTo->begin(), pItem.mTo->end(), mTo->begin());

		mSubject = new string(*pItem.mSubject);
		mBody = new string(*pItem.mBody);

		mCc = new vector<MessageAddress>();
		copy(pItem.mCc->begin(), pItem.mCc->end(), mCc->begin());

		mBcc = new vector<MessageAddress>();
		copy(pItem.mBcc->begin(), pItem.mBcc->end(), mBcc->begin());

		mAttachments = new vector<Attachment>();
		copy(pItem.mAttachments->begin(), pItem.mAttachments->end(), mAttachments->begin());
	}

	Message::~Message()
	{
		if (mTo)
		{
			mTo->clear();
			delete mTo;
		}
		delete mSubject;
		delete mBody;
		if (mCc)
		{
			mCc->clear();
			delete mCc;
		}
		if (mBcc)
		{
			mBcc->clear();
			delete mBcc;
		}
		if (mAttachments)
		{
			mAttachments->clear();
			delete mAttachments;
		}
	}

	const Message& Message::operator=(const Message &msg)
	{
		if (this != &msg)
		{
			mTo->clear();
			delete mTo;
			delete mSubject;
			delete mBody;
			if (mCc)
			{
				mCc->clear();
				delete mCc;
				mCc = nullptr;
			}
			if (mBcc)
			{
				mBcc->clear();
				delete mBcc;
				mBcc = nullptr;
			}

			if (mAttachments)
			{
				mAttachments->clear();
				delete mAttachments;
				mAttachments = nullptr;
			}

			mFrom = msg.mFrom;

			mTo = new vector<MessageAddress>();
			copy(msg.mTo->begin(), msg.mTo->end(), mTo->begin());

			mSubject = new string(*msg.mSubject);
			mBody = new string(*msg.mBody);

			mCc = new vector<MessageAddress>();
			copy(msg.mCc->begin(), msg.mCc->end(), mCc->begin());

			mBcc = new vector<MessageAddress>();
			copy(msg.mBcc->begin(), msg.mBcc->end(), mBcc->begin());

			mAttachments = new vector<Attachment>();
			copy(msg.mAttachments->begin(), msg.mAttachments->end(), mAttachments->begin());
		}
		return *this;
	}

	const vector<MessageAddress> &Message::getTo() const
	{
		return *mTo;
	}

	const size_t Message::getToCount() const
	{
		return mTo->size();
	}

	const string &Message::getSubject() const
	{
		return *mSubject;
	}

	const string &Message::getBody() const
	{
		return *mBody;
	}

	const vector<MessageAddress> &Message::getCc() const
	{
		return *mCc;
	}

	const size_t Message::getCcCount() const
	{
		return mCc->size();
	}

	const vector<MessageAddress> &Message::getBcc() const
	{
		return *mBcc;
	}

	const size_t Message::getBccCount() const
	{
		return mBcc->size();
	}

	const MessageAddress Message::getFrom() const
	{
		return mFrom;
	}

	const vector<Attachment> &Message::getAttachments() const
	{
		return *mAttachments;
	}

	const size_t Message::getAttachmentsCount() const
	{
		return mAttachments->size();
	}
}