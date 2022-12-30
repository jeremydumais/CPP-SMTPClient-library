#include "message.hpp"
#include <algorithm>
#include <stdexcept>
#include <vector>

using namespace jed_utils::cpp;

Message::Message(const MessageAddress &pFrom,
                 const std::vector<MessageAddress> &pTo,
                 const std::string &pSubject,
                 const std::string &pBody,
                 const std::vector<MessageAddress> &pCc,
                 const std::vector<MessageAddress> &pBcc,
                 const std::vector<Attachment> &pAttachments)
    : mFrom(pFrom),
      mTo(pTo),
      mSubject(pSubject),
      mBody(pBody),
      mCc(pCc),
      mBcc(pBcc),
      mAttachments(pAttachments) {
    if (pTo.empty()) {
        throw std::invalid_argument("To cannot be empty");
    }
}

const MessageAddress &Message::getFrom() const {
    return mFrom;
}

const std::vector<MessageAddress> &Message::getTo() const {
    return mTo;
}

size_t Message::getToCount() const {
    return mTo.size();
}

std::string Message::getSubject() const {
    return mSubject;
}

std::string Message::getBody() const {
    return mBody;
}

const std::vector<MessageAddress> &Message::getCc() const {
    return mCc;
}

size_t Message::getCcCount() const {
    return mCc.size();
}

const std::vector<MessageAddress> &Message::getBcc() const {
    return mBcc;
}

size_t Message::getBccCount() const {
    return mBcc.size();
}

const std::vector<Attachment> &Message::getAttachments() const {
    return mAttachments;
}

size_t Message::getAttachmentsCount() const {
    return mAttachments.size();
}

std::vector<jed_utils::MessageAddress> Message::getStdMessageAddressVec(const std::vector<MessageAddress> &src) const {
    std::vector<jed_utils::MessageAddress> retval = {};
    std::transform(src.cbegin(),
                   src.cend(),
                   std::back_inserter(retval),
                   [](const auto &recipient) { return recipient.toStdMessageAddress(); });
    return retval;
}

std::vector<jed_utils::Attachment> Message::getStdAttachmentVec(const std::vector<Attachment> &src) const {
    std::vector<jed_utils::Attachment> retval = {};
    std::transform(src.cbegin(),
                   src.cend(),
                   std::back_inserter(retval),
                   [](const auto &recipient) { return recipient.toStdAttachment(); });
    return retval;
}
