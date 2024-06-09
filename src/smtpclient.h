#ifndef SMTPCLIENT_H
#define SMTPCLIENT_H

#include "smtpclientbase.h"

#ifdef _WIN32
    #ifdef SMTPCLIENT_EXPORTS
        #define SMTPCLIENT_API __declspec(dllexport)
    #else
        #define SMTPCLIENT_API __declspec(dllimport)
    #endif
#else
    #define SMTPCLIENT_API
#endif

namespace jed_utils {
/** @brief The SmtpClient should be used to communicate with internal relay servers.
 *  This client doesn't provided encryption for communication.
 *  The communication is usually done via port 25.
 */
class SMTPCLIENT_API SmtpClient : public SMTPClientBase {
 public:
    /**
     *  @brief  Construct a new SmtpClient.
     *  @param pServerName The name of the server.
     *  Example: smtp.domainexample.com
     *  @param pPort The server port number.
     *  Example: 25, 465, 587
     */
    SmtpClient(const char *pServerName, unsigned int pPort);

    /** Destructor of the SmtpClient. */
    ~SmtpClient() override;

    /** SmtpClient copy constructor. */
    SmtpClient(const SmtpClient &other) = default;

    /** SmtpClient copy assignment operator. */
    SmtpClient& operator=(const SmtpClient &other);

    /** SmtpClient move constructor. */
    SmtpClient(SmtpClient &&other) noexcept;

    /** SmtpClient move assignment operator. */
    SmtpClient& operator=(SmtpClient &&other) noexcept;

 protected:
    void cleanup() override;
    // Methods used to establish the connection with server
    int establishConnectionWithServer() override;
    // Methods to send commands to the server
    int sendCommand(const char *pCommand, int pErrorCode) override;
    int sendCommandWithFeedback(const char *pCommand, int pErrorCode, int pTimeoutCode) override;
    int getServerReply() override;
};
}  // namespace jed_utils

#endif
