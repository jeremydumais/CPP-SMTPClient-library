#ifndef IMPLICITSSLSMTPCLIENT_H
#define IMPLICITSSLSMTPCLIENT_H

#include "securesmtpclientbase.h"

#ifdef _WIN32
    #ifdef SMTPCLIENT_EXPORTS
       #define FORCEDSECURESMTPCLIENT_API __declspec(dllexport)
    #else
        #define FORCEDSECURESMTPCLIENT_API __declspec(dllimport)
    #endif
#else
    #define FORCEDSECURESMTPCLIENT_API
#endif

namespace jed_utils {
/** @brief The ForcedSecureSMTPClient is useful to communicate with legacy
 *  systems which requires that the communication be encrypted from the
 *  initial connection. The communication is usually done via port 465.
 */
class FORCEDSECURESMTPCLIENT_API ForcedSecureSMTPClient : public SecureSMTPClientBase {
 public:
    /**
     *  @brief  Construct a new ForcedSecureSMTPClient.
     *  @param pServerName The name of the server.
     *  Example: smtp.domainexample.com
     *  @param pPort The server port number.
     *  Example: 25, 465, 587
     */
    ForcedSecureSMTPClient(const char *pServerName, unsigned int pPort);

    /** Destructor of the ForcedSecureSMTPClient. */
    ~ForcedSecureSMTPClient() override = default;

    /** ForcedSecureSMTPClient copy constructor. */
    ForcedSecureSMTPClient(const ForcedSecureSMTPClient& other) = default;

    /** ForcedSecureSMTPClient copy assignment operator. */
    ForcedSecureSMTPClient& operator=(const ForcedSecureSMTPClient& other);

    /** ForcedSecureSMTPClient move constructor. */
    ForcedSecureSMTPClient(ForcedSecureSMTPClient&& other) noexcept;

    /** ForcedSecureSMTPClient move assignment operator. */
    ForcedSecureSMTPClient& operator=(ForcedSecureSMTPClient&& other) noexcept;

 protected:
    int establishConnectionWithServer() override;
    int checkServerGreetings() override;
};
}  // namespace jed_utils

#endif
