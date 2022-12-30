#include "credential.hpp"

using namespace jed_utils::cpp;

Credential::Credential(const std::string &pUsername, const std::string &pPassword)
    : jed_utils::Credential(pUsername.c_str(), pPassword.c_str()) {
}

std::string Credential::getUsername() const {
    return jed_utils::Credential::getUsername();
}

std::string Credential::getPassword() const {
    return jed_utils::Credential::getPassword();
}

void Credential::setUsername(const std::string &pUsername) {
    jed_utils::Credential::setUsername(pUsername.c_str());
}

void Credential::setPassword(const std::string &pPassword) {
    jed_utils::Credential::setPassword(pPassword.c_str());
}
