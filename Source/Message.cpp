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
		for(auto &item : pCc)
			mCc->push_back(item);

		mBcc = new vector<MessageAddress>();
		for(auto &item : pBcc)
			mBcc->push_back(item);

		mAttachments = new vector<Attachment>();
		for(auto &item : pAttachments)
			mAttachments->push_back(item);
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
		for (auto &item : pTo)
			mTo->push_back(item);

		mSubject = new string(pSubject);
		mBody = new string(pBody);

		mCc = new vector<MessageAddress>();
		for(auto &item : pCc)
			mCc->push_back(item);

		mBcc = new vector<MessageAddress>();
		for(auto &item : pBcc)
			mBcc->push_back(item);

		mAttachments = new vector<Attachment>();
		for(auto &item : pAttachments)
			mAttachments->push_back(item);
	}

	Message::Message(const Message &pItem)
	{
		mFrom = pItem.mFrom;

		mTo = new vector<MessageAddress>();
		for (auto &item : *pItem.mTo)
			mTo->push_back(item);

		mSubject = new string(*pItem.mSubject);
		mBody = new string(*pItem.mBody);

		mCc = new vector<MessageAddress>();
		for(auto &item : *pItem.mCc)
			mCc->push_back(item);

		mBcc = new vector<MessageAddress>();
		for(auto &item : *pItem.mBcc)
			mBcc->push_back(item);

		mAttachments = new vector<Attachment>();
		for(auto &item : *pItem.mAttachments)
			mAttachments->push_back(item);
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
			for (auto &item : *msg.mTo)
				mTo->push_back(item);

			mSubject = new string(*msg.mSubject);
			mBody = new string(*msg.mBody);

			mCc = new vector<MessageAddress>();
			for(auto &item : *msg.mCc)
				mCc->push_back(item);

			mBcc = new vector<MessageAddress>();
			for(auto &item : *msg.mBcc)
				mBcc->push_back(item);

			mAttachments = new vector<Attachment>();
			for(auto &item : *msg.mAttachments)
				mAttachments->push_back(item);
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