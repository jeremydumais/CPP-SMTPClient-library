#include "attachment.hpp"

using namespace jed_utils::cpp;

Attachment::Attachment(const std::string &pFilename, const std::string &pName, const std::string &pContentId)
    : jed_utils::Attachment(pFilename.c_str(), pName.c_str(), pContentId.c_str()) {
}

void Attachment::setContentId(std::string pContentId) {
    return jed_utils::Attachment::setContentId(pContentId.c_str());
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
                                 jed_utils::Attachment::getName(),
                                 jed_utils::Attachment::getContentId());
}

