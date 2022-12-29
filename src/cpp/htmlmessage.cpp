#include "htmlmessage.hpp"
#include "message.hpp"

using namespace jed_utils::cpp;

HTMLMessage::HTMLMessage(const MessageAddress &pFrom,
                 const std::vector<MessageAddress> &pTo,
                 const std::string &pSubject,
                 const std::string &pBody,
                 const std::vector<MessageAddress> pCc,
                 const std::vector<MessageAddress> pBcc,
                 const std::vector<Attachment> pAttachments)
    : Message(pFrom,
              pTo,
              pSubject,
              pBody,
              pCc,
              pBcc,
              pAttachments){
}

std::string HTMLMessage::getMimeType() const {
    return "text/html";
}
