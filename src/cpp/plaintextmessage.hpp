#ifndef CPPPLAINTEXTMESSAGE_H
#define CPPPLAINTEXTMESSAGE_H

#include <string>
#include <vector>
#include "attachment.hpp"
#include "message.hpp"
#include "messageaddress.hpp"
#include "../plaintextmessage.h"

#ifdef _WIN32
    #ifdef SMTPCLIENT_EXPORTS
        #define CPP_PLAINTEXTMESSAGE_API __declspec(dllexport)
    #else
        #define CPP_PLAINTEXTMESSAGE_API __declspec(dllimport)
    #endif
#else
    #define CPP_PLAINTEXTMESSAGE_API
#endif

namespace jed_utils {
namespace cpp {
/** @brief The Message class represents the base class of an email message. */
class CPP_PLAINTEXTMESSAGE_API PlaintextMessage : public Message {
 public:
    /**
     *  @brief  Construct a new single recipient PlaintextMessage class.
     *  @param pFrom The sender email address of the message.
     *  @param pTo The recipient email addresses of the message.
     *  @param pSubject The subject of the message.
     *  @param pBody The content of the message.
     *  @param pCc The carbon-copy recipient email addresses.
     *  @param pBcc The blind carbon-copy recipient email addresses.
     *  @param pAttachments The attachments of the message
     */
    PlaintextMessage(const MessageAddress &pFrom,
            const std::vector<MessageAddress> &pTo,
            const std::string &pSubject,
            const std::string &pBody,
            const std::vector<MessageAddress> &pCc = {},
            const std::vector<MessageAddress> &pBcc = {},
            const std::vector<Attachment> &pAttachments = {});

    /** The destructor of the Message */
    virtual ~PlaintextMessage() = default;

    /** Return the string MIME type of the message (Pure virtual function). */
    std::string getMimeType() const override;

    operator jed_utils::PlaintextMessage() const;

};
}  // namespace cpp
}  // namespace jed_utils

#endif
