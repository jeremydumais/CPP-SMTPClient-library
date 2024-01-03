#ifndef CPPSMTPCLIENT
#define CPPSMTPCLIENT

#include <string>
#include "credential.hpp"
#include "message.hpp"
#include "../serverauthoptions.h"
#include "../smtpclient.h"

#ifdef _WIN32
    #ifdef SMTPCLIENT_EXPORTS
        #define CPP_SMTPCLIENT_API __declspec(dllexport)
    #else
        #define CPP_SMTPCLIENT_API __declspec(dllimport)
    #endif
#else
    #define CPP_SMTPCLIENT_API
#endif

namespace jed_utils {
namespace cpp {
/** @brief The SmtpClient should be used to communicate with internal relay servers.
 *  This client doesn't provided encryption for communication.
 *  The communication is usually done via port 25.
 */
class CPP_SMTPCLIENT_API SmtpClient : private jed_utils::SmtpClient {
 public:
    /**
     *  @brief  Construct a new SmtpClient.
     *  @param pServerName The name of the server.
     *  Example: smtp.domainexample.com
     *  @param pPort The server port number.
     *  Example: 25, 465, 587
     */
    SmtpClient(const std::string &pServerName, unsigned int pPort);

    /** Destructor of the SmtpClient. */
    ~SmtpClient() override = default;

    /** SmtpClient copy constructor. */
    SmtpClient(const SmtpClient &other) = default;

    /** SmtpClient copy assignment operator. */
    SmtpClient& operator=(const SmtpClient &other) = default;

    /** SmtpClient move constructor. */
    SmtpClient(SmtpClient &&other) noexcept = default;

    /** SmtpClient move assignment operator. */
    SmtpClient& operator=(SmtpClient &&other) noexcept = default;

    /** Return the server name. */
    std::string getServerName() const;

    /** Return the server port number. */
    unsigned int getServerPort() const;

    /** Return the batch mode enable flag. */
    bool getBatchMode() const;

    /** Return the command timeout in seconds. */
    unsigned int getCommandTimeout() const;

    /** Return the communication log produced by the sendMail method. */
    std::string getCommunicationLog() const;

    /** Return the credentials configured. */
    const Credential *getCredentials() const;

    /**
     *  @brief  Set the server name.
     *  @param pServerName A std::string of the server name.
     *  Example: smtp.domainexample.com
     */
    void setServerName(const std::string &pServerName);

    /**
     *  @brief  Set the server port number.
     *  @param pPort The port number.
     *  Example: 25, 465, 587
     */
    void setServerPort(unsigned int pPort);

    /**
     *  @brief  Set the batch mode flag.
     *  @param pEnabled Indicate if the batch mode is enabled.
     *  Default: false
     */
    void setBatchMode(bool pEnabled);

    /**
     *  @brief  Set the command timeout in seconds.
     *  @param pTimeOutInSeconds The timeout in seconds.
     *  Default: 3 seconds
     */
    void setCommandTimeout(unsigned int pTimeOutInSeconds);

    /**
     *  @brief  Set the credentials.
     *  @param pCredential The credential containing the username and the password.
     */
    void setCredentials(const Credential &pCredential);

    /**
     *  @brief  Indicate if the class will keep using base send command even
     *  if a child class as overriden the sendCommand and sendCommandWithFeedback.
     *
     *  This is used for example if you are using a secure client class but
     *  the STARTTLS feature is not available. The communication will then
     *  remain unsecured.
     *  @param pValue True to enable this behavior, false for the default
     */
    void setKeepUsingBaseSendCommands(bool pValue);

    /**
     *  @brief  Retreive the error message string that correspond to
     *  the error code provided.
     *  @return A std::string containing the error message.
     */
    static std::string getErrorMessage(int errorCode);

    /**
     *  @brief  This is the reentrant version of the getErrorMessage method
     *  @param  errorCode  The error code return by the SMTP client.
     *  @param  errorMessagePtr  A pointer to an allocated char array
     *  @param  maxLength  The size of the allocated char array.
     *  @return Return 0 for success, -1 if an error occurred and a positive
     *  number representing the number of characters copied to errorMessagePtr
     *  if the message was longer than that allocated char array.
     *
     *  Retreive the error message string that correspond to the error code
     *  provided.
     */
    static int getErrorMessage_r(int errorCode,
                                 std::string &errorMessage);

    int sendMail(const jed_utils::Message &pMsg);

 protected:
    static int extractReturnCode(const std::string &pOutput);
    static jed_utils::ServerAuthOptions *extractAuthenticationOptions(const std::string &pEhloOutput);

 private:
    Credential* mCredential = nullptr;
};
}  // namespace cpp
}  // namespace jed_utils

#endif
