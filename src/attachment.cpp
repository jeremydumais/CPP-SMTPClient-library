#include "attachment.h"
#include <cstdint>
#include <ios>
#include <iostream>
#include <limits>
#include <string>
#include "stringutils.h"

using namespace jed_utils;

Attachment::Attachment(const char *pFilename, const char *pName, const char *pContentId)
    : mName(nullptr), mFilename(nullptr), mContentId(nullptr) {
    size_t pFileNameLength = strlen(pFilename);
    if (pFileNameLength == 0 || StringUtils::trim(std::string(pFilename)).length() == 0) {
        throw std::invalid_argument("filename");
    }

    size_t filename_len = pFileNameLength;
    mFilename = new char[filename_len+1];
    strncpy(mFilename, pFilename, filename_len);
    mFilename[filename_len] = '\0';

    size_t name_len = strlen(pName);
    mName = new char[name_len+1];
    strncpy(mName, pName, name_len);
    mName[name_len] = '\0';

    size_t contentid_len = strlen(pContentId);
    mContentId = new char[contentid_len+1];
    strncpy(mContentId, pContentId, contentid_len);
    mContentId[contentid_len] = '\0';
}

Attachment::~Attachment() {
    delete[] mName;
    mName = nullptr;
    delete[] mFilename;
    mFilename = nullptr;
    delete[] mContentId;
    mContentId = nullptr;
}

// Copy constructor
Attachment::Attachment(const Attachment& other)
    : mName(new char[strlen(other.mName) + 1]),
      mFilename(new char[strlen(other.mFilename) + 1]),
      mContentId(new char[strlen(other.mContentId) + 1]) {
    size_t name_len = strlen(other.mName);
    strncpy(mName, other.mName, name_len);
    mName[name_len] = '\0';
    size_t filename_len = strlen(other.mFilename);
    strncpy(mFilename, other.mFilename, filename_len);
    mFilename[filename_len] = '\0';
    size_t contentid_len = strlen(other.mContentId);
    strncpy(mContentId, other.mContentId, contentid_len);
    mContentId[contentid_len] = '\0';
}

// Assignment operator
Attachment& Attachment::operator=(const Attachment& other) {
    if (this != &other) {
        delete[] mName;
        delete[] mFilename;
        delete[] mContentId;
        // mName
        size_t name_len = strlen(other.mName);
        mName = new char[name_len + 1];
        strncpy(mName, other.mName, name_len);
        mName[name_len] = '\0';
        // mFilename
        size_t filename_len = strlen(other.mFilename);
        mFilename = new char[filename_len + 1];
        strncpy(mFilename, other.mFilename, filename_len);
        mFilename[filename_len] = '\0';
        // mContentId
        size_t contentid_len = strlen(other.mContentId);
        mContentId = new char[contentid_len + 1];
        strncpy(mContentId, other.mContentId, contentid_len);
        mContentId[contentid_len] = '\0';
    }
    return *this;
}

// Move constructor
Attachment::Attachment(Attachment&& other) noexcept
: mName(other.mName), mFilename(other.mFilename), mContentId(other.mContentId) {
    // Release the data pointer from the source object so that the destructor
    // does not free the memory multiple times.
    other.mName = nullptr;
    other.mFilename = nullptr;
    other.mContentId = nullptr;
}

// Move assignement operator
Attachment& Attachment::operator=(Attachment&& other) noexcept {
    if (this != &other) {
        delete[] mName;
        delete[] mFilename;
        delete[] mContentId;
        // Copy the data pointer and its length from the source object.
        mName = other.mName;
        mFilename = other.mFilename;
        mContentId = other.mContentId;
        // Release the data pointer from the source object so that
        // the destructor does not free the memory multiple times.
        other.mName = nullptr;
        other.mFilename = nullptr;
        other.mContentId = nullptr;
    }
    return *this;
}

void Attachment::setContentId(const char * pContentId) {
    size_t contentid_len = strlen(pContentId);
    mContentId = new char[contentid_len + 1];
    strncpy(mContentId, pContentId, contentid_len);
    mContentId[contentid_len] = '\0';
}

const char *Attachment::getName() const {
    return mName;
}

const char *Attachment::getFilename() const {
    return mFilename;
}

const char *Attachment::getContentId() const {
    return mContentId;
}

const char *Attachment::getBase64EncodedFile() const {
    // Open the file
    std::ifstream in(mFilename, std::ios::in | std::ios::binary);
    if (in) {
        std::string contents;
        in.seekg(0, std::ios::end);
        contents.resize(static_cast<unsigned int>(in.tellg()));
        in.seekg(0, std::ios::beg);
        if (static_cast<intmax_t>(contents.size()) <= std::numeric_limits<std::streamsize>::max()) {
            in.read(&contents[0], static_cast<std::streamsize>(contents.size()));
            in.close();
            std::string base64_result = Base64::Encode(reinterpret_cast<const unsigned char*>(contents.c_str()), contents.length());
            auto *base64_file = new char[base64_result.length() + 1];
            strncpy(base64_file, base64_result.c_str(), base64_result.length() + 1);
            return base64_file;
        }
        in.close();
    }

    std::cerr << "Could not open file " << mFilename << std::endl;
    return nullptr;
}

const char *Attachment::getMimeType() const {
    std::string filename_str { mFilename };
    const std::string extension = StringUtils::toUpper(filename_str.substr(filename_str.find_last_of('.') + 1));
    // Images
    if (extension == "PNG") {
        return "image/png";
    }
    if (extension == "JPEG" || extension == "JPG" || extension == "JPE") {
        return "image/jpeg";
    }
    if (extension == "GIF") {
        return "image/gif";
    }
    if (extension == "TIFF" || extension == "TIF") {
        return "image/tiff";
    }
    if (extension == "ICO") {
        return "image/x-icon";
    }
    // Application
    if (extension == "XML" || extension == "XSL") {
        return "application/xml";
    }
    if (extension == "XHTML" || extension == "XHT") {
        return "application/xhtml+xml";
    }
    if (extension == "PDF") {
        return "application/pdf";
    }
    if (extension == "JS") {
        return "application/javascript";
    }
    // Text
    if (extension == "CSS") {
        return "text/css";
    }
    if (extension == "CSV") {
        return "text/csv";
    }
    if (extension == "HTML" || extension == "HTM") {
        return "text/html";
    }
    if (extension == "TXT" || extension == "TEXT" || extension == "CONF"
            || extension == "DEF" || extension == "LIST" || extension == "LOG"
            || extension == "IN") {
        return "text/plain";
    }
    // Videos
    if (extension == "MPEG" || extension == "MPG" || extension == "MPE"
            || extension == "M1V" || extension == "M2V") {
        return "video/mpeg";
    }
    if (extension == "MP4" || extension == "MP4V" || extension == "MPG4") {
        return "video/mp4";
    }
    if (extension == "QT" || extension == "MOV") {
        return "video/quicktime";
    }
    if (extension == "WMV") {
        return "video/x-ms-wmv";
    }
    if (extension == "AVI") {
        return "video/x-msvideo";
    }
    if (extension == "FLV") {
        return "video/x-flv";
    }
    if (extension == "WEBM") {
        return "video/webm";
    }
    // Audio
    if (extension == "WAV") {
        return "audio/wav";
    }
    if (extension == "MP3") {
        return "audio/mpeg";
    }
    if (extension == "OGA") {
        return "audio/ogg";
    }
    if (extension == "OPUS") {
        return "audio/opus";
    }
    if (extension == "AAC") {
        return "audio/aac";
    }
    // Archives
    if (extension == "ZIP") {
        return "application/zip";
    }
    if (extension == "RAR") {
        return "application/x-rar-compressed";
    }
    // Documents
    if (extension == "ODT") {
        return "application/vnd.oasis.opendocument.text";
    }
    if (extension == "ODS") {
        return "application/vnd.oasis.opendocument.spreadsheet";
    }
    if (extension == "ODP") {
        return "application/vnd.oasis.opendocument.presentation";
    }
    if (extension == "ODG") {
        return "application/vnd.oasis.opendocument.graphics";
    }
    if (extension == "XLS" || extension == "XLM" || extension == "XLA"
            || extension == "XLC" || extension == "XLT" || extension == "XLW") {
        return "application/vnd.ms-excel";
    }
    if (extension == "XLAM") {
        return "application/vnd.ms-excel.addin.macroenabled.12";
    }
    if (extension == "XLSB") {
        return "application/vnd.ms-excel.sheet.binary.macroenabled.12";
    }
    if (extension == "XLSM") {
        return "application/vnd.ms-excel.sheet.macroenabled.12";
    }
    if (extension == "XLTM") {
        return "application/vnd.ms-excel.template.macroenabled.12";
    }
    if (extension == "XLSX") {
        return "application/vnd.openxmlformats-officedocument.spreadsheetml.sheet";
    }
    if (extension == "XLTX") {
        return "application/vnd.openxmlformats-officedocument.spreadsheetml.template";
    }
    if (extension == "PPT" || extension == "PPS" || extension == "POT") {
        return "application/vnd.ms-powerpoint";
    }
    if (extension == "PPAM") {
        return "application/vnd.ms-powerpoint.addin.macroenabled.12";
    }
    if (extension == "PPTM") {
        return "application/vnd.ms-powerpoint.presentation.macroenabled.12";
    }
    if (extension == "SLDM") {
        return "application/vnd.ms-powerpoint.slide.macroenabled.12";
    }
    if (extension == "PPSM") {
        return "application/vnd.ms-powerpoint.slideshow.macroenabled.12";
    }
    if (extension == "POTM") {
        return "application/vnd.ms-powerpoint.template.macroenabled.12";
    }
    if (extension == "PPTX") {
        return "application/vnd.openxmlformats-officedocument.presentationml.presentation";
    }
    if (extension == "SLDX") {
        return "application/vnd.openxmlformats-officedocument.presentationml.slide";
    }
    if (extension == "PPSX") {
        return "application/vnd.openxmlformats-officedocument.presentationml.slideshow";
    }
    if (extension == "POTX") {
        return "application/vnd.openxmlformats-officedocument.presentationml.template";
    }
    if (extension == "DOC") {
        return "application/msword";
    }
    if (extension == "DOT") {
        return "application/msword";
    }
    if (extension == "DOCX") {
        return "application/vnd.openxmlformats-officedocument.wordprocessingml.document";
    }
    if (extension == "DOTX") {
        return "application/vnd.openxmlformats-officedocument.wordprocessingml.template";
    }
    if (extension == "XUL") {
        return "application/vnd.mozilla.xul+xml";
    }

    return "";
}
