#include "messageaddress.hpp"
#include <algorithm>

using namespace jed_utils::cpp;

MessageAddress::MessageAddress(const std::string &pEmailAddress,
                               const std::string &pDisplayName)
    : jed_utils::MessageAddress(pEmailAddress.c_str(), pDisplayName.c_str()) {
}

MessageAddress::operator std::string() const {
    return jed_utils::MessageAddress::operator std::string();
}

std::string MessageAddress::getEmailAddress() const {
    return jed_utils::MessageAddress::getEmailAddress();
}

std::string MessageAddress::getDisplayName() const {
    return jed_utils::MessageAddress::getDisplayName();
}

jed_utils::MessageAddress MessageAddress::toStdMessageAddress() const {
    return jed_utils::MessageAddress(jed_utils::MessageAddress::getEmailAddress(),
                                     jed_utils::MessageAddress::getDisplayName());
}

