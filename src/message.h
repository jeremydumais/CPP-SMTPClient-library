#ifndef MESSAGE_H
#define MESSAGE_H

#include <cstring>
#include <vector>
#include "attachment.h"
#include "messageaddress.h"

#ifdef _WIN32
    #ifdef SMTPCLIENT_EXPORTS
        #define MESSAGE_API __declspec(dllexport)
    #else
        #define MESSAGE_API __declspec(dllimport)
    #endif
#else
    #define MESSAGE_API
#endif

namespace jed_utils {
/** @brief The Message class represents the base class of an email message. */
class MESSAGE_API Message {
 public:
    /**
     *  @brief  Construct a new single recipient Message base class.
     *  @param pFrom The sender email address of the message.
     *  @param pTo The recipient email address of the message.
     *  @param pSubject The subject of the message.
     *  @param pBody The content of the message.
     *  @param pCc The carbon-copy recipient email address.
     *  @param pBcc The blind carbon-copy recipient email address.
     *  @param pAttachments The attachments array of the message
     *  @param pAttachmentsSize The number of attachments in the array.
     */
    Message(const MessageAddress &pFrom,
            const MessageAddress &pTo,
            const char *pSubject,
            const char *pBody,
            const MessageAddress *pCc = nullptr,
            const MessageAddress *pBcc = nullptr,
            const Attachment pAttachments[] = nullptr,
            size_t pAttachmentsSize = 0);

    /**
     *  @brief  Construct a new multiple recipients Message base class.
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
    Message(const MessageAddress &pFrom,
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

    /** The destructor of the Message */
    virtual ~Message();

    /** Message copy constructor. */
    Message(const Message &other);

    /** Message copy assignment operator. */
    Message& operator=(const Message &other);

    /** Message move constructor. */
    Message(Message &&other) noexcept;

    /** Message move assignment operator. */
    Message& operator=(Message &&other) noexcept;

    /** Return the string MIME type of the message (Pure virtual function). */
    virtual const char *getMimeType() const = 0;

    /** Return the Sender MessageAddress of the message. */
    const MessageAddress &getFrom() const;

    /** Return the recipient MessageAddress array of the message  */
    MessageAddress **getTo() const;

    /** Return the number message recipients in the array. */
    size_t getToCount() const;

    /** Return the subject of the message. */
    const char *getSubject() const;

    /** Return the body of the message. */
    const char *getBody() const;

    /** Return the carbon-copy recipient MessageAddress array of the message  */
    MessageAddress **getCc() const;

    /** Return the number of message carbon-copy recipients in the array. */
    size_t getCcCount() const;

    /** Return the blind carbon-copy recipient MessageAddress array of the message  */
    MessageAddress **getBcc() const;

    /** Return the number of message blind carbon-copy recipients in the array. */
    size_t getBccCount() const;

    /** Return the attachment array of the message  */
    Attachment **getAttachments() const;

    /** Return the number of message attachments in the array. */
    size_t getAttachmentsCount() const;

 private:
    MessageAddress mFrom;
    MessageAddress **mTo;
    size_t mToCount;
    MessageAddress **mCc;
    size_t mCCCount;
    MessageAddress **mBcc;
    size_t mBCCCount;
    char *mSubject;
    char *mBody;
    Attachment **mAttachments;
    size_t mAttachmentCount;
};
}  // namespace jed_utils

#endif
