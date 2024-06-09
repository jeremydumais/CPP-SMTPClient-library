#ifndef SECURESMTPCLIENTBASE_H
#define SECURESMTPCLIENTBASE_H

#include <openssl/ssl.h>
#include "smtpclientbase.h"

#ifdef _WIN32
    #ifdef SMTPCLIENT_EXPORTS
        #define SECURESMTPCLIENTBASE_API __declspec(dllexport)
    #else
        #define SECURESMTPCLIENTBASE_API __declspec(dllimport)
    #endif
#else
    #define SECURESMTPCLIENTBASE_API
#endif

namespace jed_utils {
/** @brief The SecureSMTPClientBase represents the base class for SMTP client
 *  that will use encryption for communication.
 */
class SECURESMTPCLIENTBASE_API SecureSMTPClientBase : public SMTPClientBase {
 public:
    /**
     *  @brief  Construct a new SecureSMTPClientBase.
     *  @param pServerName The name of the server.
     *  Example: smtp.domainexample.com
     *  @param pPort The server port number.
     *  Example: 25, 465, 587
     */
    SecureSMTPClientBase(const char *pServerName, unsigned int pPort);

    /** Destructor of the SecureSMTPClientBase. */
    ~SecureSMTPClientBase();

    /** SecureSMTPClientBase copy constructor. */
    SecureSMTPClientBase(const SecureSMTPClientBase& other);

    /** SecureSMTPClientBase copy assignment operator. */
    SecureSMTPClientBase& operator=(const SecureSMTPClientBase& other);

    /** SecureSMTPClientBase move constructor. */
    SecureSMTPClientBase(SecureSMTPClientBase&& other) noexcept;

    /** SecureSMTPClientBase move assignment operator. */
    SecureSMTPClientBase& operator=(SecureSMTPClientBase&& other) noexcept;

    /** Return the accept self certificate flag. */
    bool getAcceptSelfSignedCert() const;

    /**
     *  @brief  Set the accept self signed certificate
     *  @param pValue Indicate if self signed certificate is accepted.
     *  Default: false
     */
    void setAcceptSelfSignedCert(bool pValue);

 protected:
    // Methods
    void cleanup() override;
    BIO *getBIO() const;
    // Methods used to establish the connection with server
    int getServerSecureIdentification();
    int startTLSNegotiation();
    void initializeSSLContext();
    // Methods to send commands to the server
    int sendCommand(const char *pCommand, int pErrorCode) override;
    int sendCommandWithFeedback(const char *pCommand, int pErrorCode, int pTimeoutCode) override;
    int getServerReply() override;

 private:
    // Attributes used to communicate with the server
    BIO *mBIO;
    SSL_CTX *mCTX;
    SSL *mSSL;
    bool mAcceptSelfSignedCert;
};
}  // namespace jed_utils

#endif
