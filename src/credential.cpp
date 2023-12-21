#include "credential.h"
#include <cstring>
#include <stdexcept>
#include <string>
#include "stringutils.h"

using namespace jed_utils;

Credential::Credential(const char *pUsername, const char *pPassword)
    : mUsername(nullptr),
      mPassword(nullptr),
      mRecommendedAuthMethod(RecommendedAuthenticationMethod::kImplicit) {
    std::string username_str { pUsername == nullptr ? "" : pUsername };
    if (pUsername == nullptr || strcmp(pUsername, "") == 0 || StringUtils::trim(username_str).empty()) {
        throw std::invalid_argument("Username cannot be null or empty");
    }

    if (pPassword == nullptr || strcmp(pPassword, "") == 0) {
        throw std::invalid_argument("Password cannot be null or empty");
    }

    size_t username_len = strlen(pUsername);
    mUsername = new char[username_len + 1];
    std::strncpy(mUsername, pUsername, username_len);
    mUsername[username_len] = '\0';

    size_t password_len = strlen(pPassword);
    mPassword = new char[password_len + 1];
    std::strncpy(mPassword, pPassword, password_len);
    mPassword[password_len] = '\0';
}

Credential::~Credential() {
    delete[] mUsername;
    delete[] mPassword;
    mUsername = nullptr;
    mPassword = nullptr;
}

// Copy constructor
Credential::Credential(const Credential& other)
    : mUsername(new char[strlen(other.mUsername) + 1]),
      mPassword(new char[strlen(other.mPassword) + 1]),
      mRecommendedAuthMethod{other.mRecommendedAuthMethod} {
    size_t username_len = strlen(other.mUsername);
    strncpy(mUsername, other.mUsername, username_len);
    mUsername[username_len] = '\0';

    size_t password_len = strlen(other.mPassword);
    strncpy(mPassword, other.mPassword, password_len);
    mPassword[password_len] = '\0';
}

Credential::Credential(const char *pUsername, const char *pPassword,
      RecommendedAuthenticationMethod authOption)
    : Credential(pUsername, pPassword) {
    mRecommendedAuthMethod = authOption;
}

// Assignment operator
Credential& Credential::operator=(const Credential& other) {
    if (this != &other) {
        delete[] mUsername;
        delete[] mPassword;
        // mUsername
        size_t username_len = strlen(other.mUsername);
        mUsername = new char[username_len + 1];
        strncpy(mUsername, other.mUsername, username_len);
        mUsername[username_len] = '\0';
        // mPassword
        size_t password_len = strlen(other.mPassword);
        mPassword = new char[password_len + 1];
        strncpy(mPassword, other.mPassword, password_len);
        mPassword[password_len] = '\0';

        mRecommendedAuthMethod = other.mRecommendedAuthMethod;
    }
    return *this;
}

// Move constructor
Credential::Credential(Credential&& other) noexcept
    : mUsername(other.mUsername),
      mPassword(other.mPassword),
      mRecommendedAuthMethod{other.mRecommendedAuthMethod} {
    // Release the data pointer from the source object so that the destructor
    // does not free the memory multiple times.
    other.mUsername = nullptr;
    other.mPassword = nullptr;
}

// Move assignement operator
Credential& Credential::operator=(Credential&& other) noexcept {
    if (this != &other) {
        delete[] mUsername;
        delete[] mPassword;
        // Copy the data pointer and its length from the source object.
        mUsername = other.mUsername;
        mPassword = other.mPassword;
        mRecommendedAuthMethod = other.mRecommendedAuthMethod;

        // Release the data pointer from the source object so that
        // the destructor does not free the memory multiple times.
        other.mUsername = nullptr;
        other.mPassword = nullptr;
    }
    return *this;
}


const char *Credential::getUsername() const {
    return mUsername;
}

const char *Credential::getPassword() const {
    return mPassword;
}

auto Credential::getRecommendedAuthOption() const
      -> RecommendedAuthenticationMethod {
    return mRecommendedAuthMethod;
}

void Credential::setUsername(const char *pUsername) {
    std::string username_str { pUsername == nullptr ? "" : pUsername };
    if (pUsername == nullptr || strcmp(pUsername, "") == 0 || StringUtils::trim(username_str).empty()) {
        throw std::invalid_argument("Username cannot be null or empty");
    }

    delete []mUsername;
    size_t username_len = strlen(pUsername);
    mUsername = new char[username_len + 1];
    strncpy(mUsername, pUsername, username_len);
    mUsername[username_len] = '\0';
}

void Credential::setPassword(const char *pPassword) {
    if (pPassword == nullptr || strcmp(pPassword, "") == 0) {
        throw std::invalid_argument("Password cannot be null or empty");
    }

    delete []mPassword;
    size_t password_len = strlen(pPassword);
    mPassword = new char[password_len + 1];
    strncpy(mPassword, pPassword, password_len);
    mPassword[password_len] = '\0';
}

void Credential::setRecommendedAuthOption(
    RecommendedAuthenticationMethod authOption) {
    mRecommendedAuthMethod = authOption;
}
