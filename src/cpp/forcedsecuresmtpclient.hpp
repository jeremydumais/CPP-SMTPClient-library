#ifndef CPPFORCEDSECURESMTPCLIENT_H
#define CPPFORCEDSECURESMTPCLIENT_H

#include "credential.hpp"
#include "../forcedsecuresmtpclient.h"

#ifdef _WIN32
    #ifdef SMTPCLIENT_EXPORTS
        #define CPP_FORCEDSECURESMTPCLIENT_API __declspec(dllexport)
    #else
        #define CPP_FORCEDSECURESMTPCLIENT_API __declspec(dllimport)
    #endif
#else
    #define CPP_FORCEDSECURESMTPCLIENT_API
#endif

namespace jed_utils {
namespace cpp {
/** @brief The ForcedSecureSMTPClient should be your default choice for
 *  communicating with modern SMTP servers. The communication is usually done
 *  via port 587.
 */
class CPP_FORCEDSECURESMTPCLIENT_API ForcedSecureSMTPClient : private jed_utils::ForcedSecureSMTPClient {
 public:
    /**
     *  @brief  Construct a new ForcedSecureSMTPClient.
     *  @param pServerName The name of the server.
     *  Example: smtp.domainexample.com
     *  @param pPort The server port number.
     *  Example: 25, 465, 587
     */
    ForcedSecureSMTPClient(const std::string &pServerName, unsigned int pPort);

    /** Destructor of the ForcedSecureSMTPClient. */
    ~ForcedSecureSMTPClient() override = default;

    /** ForcedSecureSMTPClient copy constructor. */
    ForcedSecureSMTPClient(const ForcedSecureSMTPClient& other) = default;

    /** ForcedSecureSMTPClient copy assignment operator. */
    ForcedSecureSMTPClient& operator=(const ForcedSecureSMTPClient& other) = default;

    /** ForcedSecureSMTPClient move constructor. */
    ForcedSecureSMTPClient(ForcedSecureSMTPClient&& other) noexcept = default;

    /** ForcedSecureSMTPClient move assignment operator. */
    ForcedSecureSMTPClient& operator=(ForcedSecureSMTPClient&& other) noexcept = default;

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

    /** Return the accept self certificate flag. */
    bool getAcceptSelfSignedCert() const;

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
     *  @brief  Set the accept self signed certificate
     *  @param pValue Indicate if self signed certificate is accepted.
     *  Default: false
     */
    void setAcceptSelfSignedCert(bool pValue);

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
