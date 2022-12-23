#ifndef PLAINTEXTMESSAGE_H
#define PLAINTEXTMESSAGE_H

#include <string>
#include "message.h"

#ifdef _WIN32
    #ifdef SMTPCLIENT_EXPORTS
        #define PLAINTEXTMESSAGE_API __declspec(dllexport)
    #else
        #define PLAINTEXTMESSAGE_API __declspec(dllimport)
    #endif
#else
    #define PLAINTEXTMESSAGE_API
#endif

namespace jed_utils {
/** @brief The PlaintextMessage class represents an email message in
 *  plain text format.
 */
class PLAINTEXTMESSAGE_API PlaintextMessage : public Message {
 public:
    /**
     *  @brief  Construct a new single recipient PlaintextMessage.
     *  @param pFrom The sender email address of the message.
     *  @param pTo The recipient email address of the message.
     *  @param pSubject The subject of the message.
     *  @param pBody The content of the message.
     *  @param pCc The carbon-copy recipient email address.
     *  @param pBcc The blind carbon-copy recipient email address.
     *  @param pAttachments The attachments array of the message
     *  @param pAttachmentsSize The number of attachments in the array.
     */
    PlaintextMessage(const MessageAddress &pFrom,
            const MessageAddress &pTo,
            const char *pSubject,
            const char *pBody,
            const MessageAddress *pCc = nullptr,
            const MessageAddress *pBcc = nullptr,
            const Attachment *pAttachments = nullptr,
            size_t pAttachmentsSize = 0);

    /**
     *  @brief  Construct a new multiple recipients PlaintextMessage.
     *  @param pFrom The sender email address of the message.
     *  @param pTo The recipients email address array of the message.
     *  @param pToCount The number of recipients email address in the array
     *  @param pSubject The subject of the message.
     *  @param pBody The content of the message.
     *  @param pCc The carbon-copy recipients email address array.
     *  @param pCcCount The number of carbon-copy recipients email address in the array
     *  @param pBcc The blind carbon-copy recipient email address.
     *  @param pBccCount The number of blind carbon-copy recipients email address in the array
     *  @param pAttachments The attachments array of the message
     *  @param pAttachmentsSize The number of attachments in the array.
     */
    PlaintextMessage(const MessageAddress &pFrom,
            const MessageAddress pTo[],
            size_t pToCount,
            const char *pSubject,
            const char *pBody,
            const MessageAddress pCc[] = nullptr,
            size_t pCcCount = 0,
            const MessageAddress pBcc[] = nullptr,
            size_t pBccCount = 0,
            const Attachment pAttachments[] = nullptr,
            size_t pAttachmentsSize = 0);
    const char *getMimeType() const override;
};
}  // namespace jed_utils

#endif
