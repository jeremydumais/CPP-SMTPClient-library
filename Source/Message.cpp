#include "../Include/Message.h"
#include <iterator>

using namespace std;

namespace jed_utils
{
	Message::Message(const MessageAddress &pFrom,
		const MessageAddress &pTo,
		const string &pSubject,
		const string &pBody,
		const vector<MessageAddress> &pCc,
		const vector<MessageAddress> &pBcc,
		const vector<Attachment> &pAttachments)
		: mFrom(pFrom),
          mTo(vector<MessageAddress>()),
          mCc(vector<MessageAddress>()),
          mBcc(vector<MessageAddress>()),
          mSubject(pSubject),
          mBody(pBody),
          mAttachments(vector<Attachment>())
	{
		mTo.push_back(pTo);
		copy(pCc.begin(), pCc.end(), back_inserter(mCc));
		copy(pBcc.begin(), pBcc.end(), back_inserter(mBcc));
		copy(pAttachments.begin(), pAttachments.end(), back_inserter(mAttachments));
	}

	Message::Message(const MessageAddress &pFrom,
		const vector<MessageAddress> &pTo,
		const string &pSubject,
		const string &pBody,
		const vector<MessageAddress> &pCc,
		const vector<MessageAddress> &pBcc,
		const vector<Attachment> &pAttachments)
		: mFrom(pFrom),
          mTo(vector<MessageAddress>()),
          mCc(vector<MessageAddress>()),
          mBcc(vector<MessageAddress>()),
          mSubject(pSubject),
          mBody(pBody),
          mAttachments(vector<Attachment>())
	{
		copy(pTo.begin(), pTo.end(), back_inserter(mTo));
        copy(pCc.begin(), pCc.end(), back_inserter(mCc));
		copy(pBcc.begin(), pBcc.end(), back_inserter(mBcc));
		copy(pAttachments.begin(), pAttachments.end(), back_inserter(mAttachments));
	}

    Message::~Message()
    {
    }

	const vector<MessageAddress> &Message::getTo() const
	{
		return mTo;
	}

	size_t Message::getToCount() const
	{
		return mTo.size();
	}

	const string &Message::getSubject() const
	{
		return mSubject;
	}

	const string &Message::getBody() const
	{
		return mBody;
	}

	const vector<MessageAddress> &Message::getCc() const
	{
		return mCc;
	}

	size_t Message::getCcCount() const
	{
		return mCc.size();
	}

	const vector<MessageAddress> &Message::getBcc() const
	{
		return mBcc;
	}

	size_t Message::getBccCount() const
	{
		return mBcc.size();
	}

	const MessageAddress &Message::getFrom() const
	{
		return mFrom;
	}

	const vector<Attachment> &Message::getAttachments() const
	{
		return mAttachments;
	}

	size_t Message::getAttachmentsCount() const
	{
		return mAttachments.size();
	}
}
