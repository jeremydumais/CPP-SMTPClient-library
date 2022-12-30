#ifndef CPPMESSAGE_H
#define CPPMESSAGE_H

#include <string>
#include <vector>
#include "attachment.hpp"
#include "../message.h"
#include "messageaddress.hpp"

#ifdef _WIN32
    #pragma warning(disable: 4251)
    #ifdef SMTPCLIENT_EXPORTS
        #define CPP_MESSAGE_API __declspec(dllexport)
    #else
        #define CPP_MESSAGE_API __declspec(dllimport)
    #endif
#else
    #define CPP_MESSAGE_API
#endif

namespace jed_utils {
namespace cpp {
/** @brief The Message class represents the base class of an email message. */
class CPP_MESSAGE_API Message {
 public:
    /**
     *  @brief  Construct a new single recipient Message base class.
     *  @param pFrom The sender email address of the message.
     *  @param pTo The recipient email addresses of the message.
     *  @param pSubject The subject of the message.
     *  @param pBody The content of the message.
     *  @param pCc The carbon-copy recipient email addresses.
     *  @param pBcc The blind carbon-copy recipient email addresses.
     *  @param pAttachments The attachments of the message
     */
    Message(const MessageAddress &pFrom,
            const std::vector<MessageAddress> &pTo,
            const std::string &pSubject,
            const std::string &pBody,
            const std::vector<MessageAddress> &pCc = {},
            const std::vector<MessageAddress> &pBcc = {},
            const std::vector<Attachment> &pAttachments = {});

    /** The destructor of the Message */
    virtual ~Message() = default;

    /** Return the string MIME type of the message (Pure virtual function). */
    virtual std::string getMimeType() const = 0;

    /** Return the Sender MessageAddress of the message. */
    const MessageAddress &getFrom() const;

    /** Return the recipient MessageAddress vector of the message  */
    const std::vector<MessageAddress> &getTo() const;

    /** Return the number message recipients in the vector. */
    size_t getToCount() const;

    /** Return the subject of the message. */
    std::string getSubject() const;

    /** Return the body of the message. */
    std::string getBody() const;

    /** Return the carbon-copy recipient MessageAddress vector of the message  */
    const std::vector<MessageAddress> &getCc() const;

    /** Return the number of message carbon-copy recipients in the vector. */
    size_t getCcCount() const;

    /** Return the blind carbon-copy recipient MessageAddress vector of the message  */
    const std::vector<MessageAddress> &getBcc() const;

    /** Return the number of message blind carbon-copy recipients in the vector. */
    size_t getBccCount() const;

    /** Return the attachment vector of the message  */
    const std::vector<Attachment> &getAttachments() const;

    /** Return the number of message attachments in the vector. */
    size_t getAttachmentsCount() const;

 protected:
    std::vector<jed_utils::MessageAddress> getStdMessageAddressVec(const std::vector<MessageAddress> &src) const;
    std::vector<jed_utils::Attachment> getStdAttachmentVec(const std::vector<Attachment> &src) const;

 private:
    MessageAddress mFrom;
    std::vector<MessageAddress> mTo;
    std::string mSubject;
    std::string mBody;
    std::vector<MessageAddress> mCc;
    std::vector<MessageAddress> mBcc;
    std::vector<Attachment> mAttachments;
};
}  // namespace cpp
}  // namespace jed_utils

#endif
