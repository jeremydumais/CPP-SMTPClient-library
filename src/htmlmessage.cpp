#include "htmlmessage.h"

using namespace jed_utils;

HTMLMessage::HTMLMessage(const MessageAddress &pFrom,
        const MessageAddress &pTo,
        const char *pSubject,
        const char *pBody,
        const MessageAddress *pCc,
        const MessageAddress *pBcc,
        const Attachment *pAttachments,
        const size_t pAttachmentsSize)
    : Message(pFrom, pTo, pSubject, pBody, pCc, pBcc, pAttachments, pAttachmentsSize) {
}

HTMLMessage::HTMLMessage(const MessageAddress &pFrom,
        const MessageAddress pTo[],
        const size_t pToCount,
        const char *pSubject,
        const char *pBody,
        const MessageAddress pCc[],
        const size_t pCcCount,
        const MessageAddress pBcc[],
        const size_t pBccCount,
        const Attachment pAttachments[],
        const size_t pAttachmentsSize)
    : Message(pFrom, pTo, pToCount, pSubject, pBody, pCc, pCcCount, pBcc, pBccCount, pAttachments, pAttachmentsSize) {
}

const char *HTMLMessage::getMimeType() const {
    return "text/html";
}

