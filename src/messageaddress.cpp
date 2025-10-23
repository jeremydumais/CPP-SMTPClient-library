#include "messageaddress.h"
#include <cstddef>
#include <cstring>
#include <regex>
#include <stdexcept>
#include <string>
#include "stringutils.h"

using namespace jed_utils;

MessageAddress::MessageAddress(const char *pEmailAddress, const char *pDisplayName)
    : mEmailAddress(nullptr), mDisplayName(nullptr), mDomainName(nullptr) {
    std::string email_address { pEmailAddress };
    // Check if the email address is not empty or white spaces
    if (email_address.length() == 0 || StringUtils::trim(email_address).empty()) {
        throw std::invalid_argument("pEmailAddress");
    }
    // Check is the email address is valid
    if (!isEmailAddressValid(email_address)) {
        throw std::invalid_argument("pEmailAddress");
    }

    size_t email_len = strlen(pEmailAddress);
    mEmailAddress = new char[email_len+1];
    strncpy(mEmailAddress, pEmailAddress, email_len);
    mEmailAddress[email_len] = '\0';

    size_t name_len = strlen(pDisplayName);
    mDisplayName = new char[name_len+1];
    strncpy(mDisplayName, pDisplayName, name_len);
    mDisplayName[name_len] = '\0';

    std::string emailAddress(mEmailAddress);
    auto atPos = emailAddress.find('@');
    if (atPos == std::string::npos || atPos == emailAddress.size() - 1) {
        mDomainName = new char[1];
        mDomainName[0] = '\0';
    } else {
        auto domainNamePart = emailAddress.substr(atPos + 1);
        mDomainName = new char[domainNamePart.length() +1];
        strncpy(mDomainName, domainNamePart.c_str(), domainNamePart.length());
        mDomainName[domainNamePart.length()] = '\0';
    }
}

MessageAddress::~MessageAddress() {
    delete[] mEmailAddress;
    delete[] mDisplayName;
    delete[] mDomainName;
}

// Copy constructor
MessageAddress::MessageAddress(const MessageAddress& other)
    : mEmailAddress(new char[strlen(other.mEmailAddress) + 1]),
      mDisplayName(new char[strlen(other.mDisplayName) + 1]),
      mDomainName(new char[strlen(other.mDomainName) + 1]) {
    size_t email_len = strlen(other.mEmailAddress);
    strncpy(mEmailAddress, other.mEmailAddress, email_len);
    mEmailAddress[email_len] = '\0';
    size_t name_len = strlen(other.mDisplayName);
    strncpy(mDisplayName, other.mDisplayName, name_len);
    mDisplayName[name_len] = '\0';
    size_t domain_len = strlen(other.mDomainName);
    strncpy(mDomainName, other.mDomainName, domain_len);
    mDomainName[domain_len] = '\0';
}

// Assignment operator
MessageAddress& MessageAddress::operator=(const MessageAddress& other) {
    if (this != &other) {
        delete[] mEmailAddress;
        delete[] mDisplayName;
        delete[] mDomainName;
        // mEmailAddress
        size_t email_len = strlen(other.mEmailAddress);
        mEmailAddress = new char[email_len + 1];
        strncpy(mEmailAddress, other.mEmailAddress, email_len);
        mEmailAddress[email_len] = '\0';
        // mDisplayName
        size_t name_len = strlen(other.mDisplayName);
        mDisplayName = new char[name_len + 1];
        strncpy(mDisplayName, other.mDisplayName, name_len);
        mDisplayName[name_len] = '\0';
        // mDomainName
        size_t domain_len = strlen(other.mDomainName);
        mDomainName = new char[domain_len + 1];
        strncpy(mDomainName, other.mDomainName, domain_len);
        mDomainName[domain_len] = '\0';
    }
    return *this;
}

// Move constructor
MessageAddress::MessageAddress(MessageAddress&& other) noexcept
    : mEmailAddress(other.mEmailAddress),
      mDisplayName(other.mDisplayName),
      mDomainName(other.mDomainName) {
    // Release the data pointer from the source object so that the destructor
    // does not free the memory multiple times.
    other.mEmailAddress = nullptr;
    other.mDisplayName = nullptr;
    other.mDomainName = nullptr;
}

// Move assignement operator
MessageAddress& MessageAddress::operator=(MessageAddress&& other) noexcept {
    if (this != &other) {
        delete[] mEmailAddress;
        delete[] mDisplayName;
        delete[] mDomainName;
        // Copy the data pointer and its length from the source object.
        mEmailAddress = other.mEmailAddress;
        mDisplayName = other.mDisplayName;
        mDomainName = other.mDomainName;
        // Release the data pointer from the source object so that
        // the destructor does not free the memory multiple times.
        other.mEmailAddress = nullptr;
        other.mDisplayName = nullptr;
        other.mDomainName = nullptr;
    }
    return *this;
}

bool MessageAddress::operator==(const MessageAddress &pMsgComp) const {
    return (strcmp(mEmailAddress, pMsgComp.mEmailAddress) == 0 &&
            strcmp(mDisplayName, pMsgComp.mDisplayName) == 0);
}

MessageAddress::operator std::string() const {
    std::ostringstream retval;
    std::string display_name { mDisplayName };
    if (display_name.empty()) {
        retval << mEmailAddress;
    } else {
        retval << mDisplayName << " <" << mEmailAddress << ">";
    }
    return retval.str();
}

const char *MessageAddress::getEmailAddress() const {
    return mEmailAddress;
}

const char *MessageAddress::getDisplayName() const {
    return mDisplayName;
}

const char *MessageAddress::getDomainName() const {
    return mDomainName;
}

bool MessageAddress::isEmailAddressValid(const std::string &pEmailAddress) const {
    std::regex emailPattern("^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9-]+(\\.[a-zA-Z0-9-]+)*$");
    return regex_match(StringUtils::toLower(pEmailAddress), emailPattern);
}

