#ifndef CPPATTACHMENT_H
#define CPPATTACHMENT_H

#include <fstream>
#include <string>
#include "../attachment.h"
#include "../base64.h"

#ifdef _WIN32
    #ifdef SMTPCLIENT_EXPORTS
        #define CPP_ATTACHMENT_API __declspec(dllexport)
    #else
    #define CPP_ATTACHMENT_API __declspec(dllimport)
    #endif
#else
    #define CPP_ATTACHMENT_API
#endif

namespace jed_utils {
namespace cpp {
/** @brief The Attachment class represent a file attachment in a
 *  message. It can be a picture, a document, a text file etc.
 */
class CPP_ATTACHMENT_API Attachment : private jed_utils::Attachment {
 public:
    /**
     *  @brief  Construct a new Attachment.
     *  @param pFilename The full path of the file.
     *  @param pName The display name of the file that will appear in
     *  the mail content
     */
    explicit Attachment(const std::string &pFilename, const std::string &pName = "", const std::string &pContentId = "");

    /** Destructor of the Attachment */
    ~Attachment() override = default;

    /** Attachment copy constructor. */
    Attachment(const Attachment& other) = default;

    /** Attachment copy assignment operator. */
    Attachment& operator=(const Attachment& other) = default;

    /** Attachment move constructor. */
    Attachment(Attachment&& other) noexcept = default;

    /** Attachment move assignment operator. */
    Attachment& operator=(Attachment&& other) noexcept = default;

    /** Set the attachment content id. */
    void setContentId(std::string pContentId);

    /** Return the display name. */
    std::string getName() const;

    /** Return the file name including the path. */
    std::string getFilename() const;

    /** Return the attachment content id. */
    std::string getContentId() const;

    /** Return the base64 representation of the file content. */
    std::string getBase64EncodedFile() const;

    /** Return the MIME type corresponding to the file extension. */
    std::string getMimeType() const;

    jed_utils::Attachment toStdAttachment() const;
};
}  // namespace cpp
}  // namespace jed_utils

#endif
