#ifndef CPPMESSAGEADDRESS_H
#define CPPMESSAGEADDRESS_H

#include <cstring>
#include <sstream>
#include <string>
#include <vector>
#include "../messageaddress.h"

#ifdef _WIN32
    #ifdef SMTPCLIENT_EXPORTS
        #define CPP_MESSAGEADDRESS_API __declspec(dllexport)
    #else
        #define CPP_MESSAGEADDRESS_API __declspec(dllimport)
    #endif
#else
    #define CPP_MESSAGEADDRESS_API
#endif

namespace jed_utils {
namespace cpp {
/** @brief The MessageAddress class represents a sender or a recipient address containing
 *  the email address and the display name.
 *  Example : joeblow@domainexample.com Joe Blow
 */
class CPP_MESSAGEADDRESS_API MessageAddress : private jed_utils::MessageAddress {
 public:
    /**
     *  @brief  Construct a new MessageAddress.
     *  @param pEmailAddress The email address. The prefix appears to the left of the @ symbol.
     *  The domain appears to the right of the @ symbol.
     *  @param pDisplayName The display name of the address that will appear in
     *  the message. Example : Joe Blow
     */
    explicit MessageAddress(const std::string &pEmailAddress,
                            const std::string &pDisplayName = "");

    /** Destructor of the MessageAddress */
    ~MessageAddress() override = default;

    /** MessageAddress copy constructor. */
    MessageAddress(const MessageAddress& other) = default;

    /** MessageAddress copy assignment operator. */
    MessageAddress& operator=(const MessageAddress& other) = default;

    /** MessageAddress move constructor. */
    MessageAddress(MessageAddress&& other) noexcept = default;

    /** MessageAddress move assignment operator. */
    MessageAddress& operator=(MessageAddress&& other) noexcept = default;

    /** MessageAddress equality operator. */
    bool operator==(const MessageAddress &pMsgComp) const;

    /** MessageAddress implicit string conversion operator. */
    explicit operator std::string() const;

    /** Return the email address. */
    std::string getEmailAddress() const;

    /** Return the display name. */
    std::string getDisplayName() const;

    jed_utils::MessageAddress toStdMessageAddress() const;

    friend class Message;

 private:
    MessageAddress();
};
}  // namespace cpp
}  // namespace jed_utils

#endif

