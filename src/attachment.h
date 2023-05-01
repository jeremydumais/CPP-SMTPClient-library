#ifndef ATTACHMENT_H
#define ATTACHMENT_H

#include <cstring>
#include <fstream>
#include "base64.h"

#ifdef _WIN32
    #ifdef SMTPCLIENT_EXPORTS
        #define ATTACHMENT_API __declspec(dllexport)
    #else
    #define ATTACHMENT_API __declspec(dllimport)
    #endif
#else
    #define ATTACHMENT_API
#endif

namespace jed_utils {
/** @brief The Attachment class represent a file attachment in a
 *  message. It can be a picture, a document, a text file etc.
 */
class ATTACHMENT_API Attachment {
 public:
    /**
     *  @brief  Construct a new Attachment.
     *  @param pFilename The full path of the file.
     *  @param pName The display name of the file that will appear in
     *  the mail content
     */
    explicit Attachment(const char *pFilename, const char *pName = "", const char *pContentId = "");

    /** Destructor of the Attachment */
    virtual ~Attachment();

    /** Attachment copy constructor. */
    Attachment(const Attachment& other);

    /** Attachment copy assignment operator. */
    Attachment& operator=(const Attachment& other);

    /** Attachment move constructor. */
    Attachment(Attachment&& other) noexcept;

    /** Attachment move assignment operator. */
    Attachment& operator=(Attachment&& other) noexcept;

    /** Set the attachment content id. */
    void setContentId(const char * pContentId);

    /** Return the display name. */
    const char *getName() const;

    /** Return the file name including the path. */
    const char *getFilename() const;

    /** Return the attachment content id. */
    const char *getContentId() const;

    /** Return the base64 representation of the file content. */
    const char *getBase64EncodedFile() const;

    /** Return the MIME type corresponding to the file extension. */
    const char *getMimeType() const;

    friend class Message;

 private:
    Attachment() = default;
    char *mName;
    char *mFilename;
    char *mContentId;
};
}  // namespace jed_utils

#endif
