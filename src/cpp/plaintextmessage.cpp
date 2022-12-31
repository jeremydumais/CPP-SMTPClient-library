#include "plaintextmessage.hpp"
#include "message.hpp"

using namespace jed_utils::cpp;

PlaintextMessage::PlaintextMessage(const MessageAddress &pFrom,
                 const std::vector<MessageAddress> &pTo,
                 const std::string &pSubject,
                 const std::string &pBody,
                 const std::vector<MessageAddress> &pCc,
                 const std::vector<MessageAddress> &pBcc,
                 const std::vector<Attachment> &pAttachments)
    : Message(pFrom,
              pTo,
              pSubject,
              pBody,
              pCc,
              pBcc,
              pAttachments) {
}

std::string PlaintextMessage::getMimeType() const {
    return "text/plain";
}

PlaintextMessage::operator jed_utils::PlaintextMessage() const {
    const auto to = getStdMessageAddressVec(getTo());
    const auto cc = getStdMessageAddressVec(getCc());
    const auto bcc = getStdMessageAddressVec(getBcc());
    const auto att = getStdAttachmentVec(getAttachments());
    const jed_utils::PlaintextMessage msg (getFrom().toStdMessageAddress(),
                                  to.data(),
                                  to.size(),
                                  getSubject().c_str(),
                                  getBody().c_str(),
                                  cc.data(),
                                  cc.size(),
                                  bcc.data(),
                                  bcc.size(),
                                  att.data(),
                                  att.size());
    return msg;
}
