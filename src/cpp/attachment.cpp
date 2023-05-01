#include "attachment.hpp"

using namespace jed_utils::cpp;

Attachment::Attachment(const std::string &pFilename, const std::string &pName)
    : jed_utils::Attachment(pFilename.c_str(), pName.c_str()) {
}

void Attachment::setContentId(std::string contentId) {
    return jed_utils::Attachment::setContentId((char*)contentId.c_str());
}

std::string Attachment::getName() const {
    return jed_utils::Attachment::getName();
}

std::string Attachment::getFilename() const {
    return jed_utils::Attachment::getFilename();
}

std::string Attachment::getContentId() const {
    return jed_utils::Attachment::getContentId();
}

std::string Attachment::getBase64EncodedFile() const {
    const char *retval = jed_utils::Attachment::getBase64EncodedFile();
    return retval == nullptr ? "" : retval;
}

std::string Attachment::getMimeType() const {
    return jed_utils::Attachment::getMimeType();
}

jed_utils::Attachment Attachment::toStdAttachment() const {
    return jed_utils::Attachment(jed_utils::Attachment::getFilename(),
                                 jed_utils::Attachment::getName());
}

