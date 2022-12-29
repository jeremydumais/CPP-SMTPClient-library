#include "attachment.hpp"

using namespace jed_utils::cpp;

Attachment::Attachment(const std::string &pFilename, const std::string &pName)
    : jed_utils::Attachment(pFilename.c_str(), pName.c_str()) {
}

std::string Attachment::getName() const {
    return jed_utils::Attachment::getName();
}

std::string Attachment::getFilename() const {
    return jed_utils::Attachment::getFilename();
}

std::string Attachment::getBase64EncodedFile() const {
    const char *retval = jed_utils::Attachment::getBase64EncodedFile();
    return retval == nullptr ? "" : retval;
}

std::string Attachment::getMimeType() const {
    return jed_utils::Attachment::getMimeType();
}
