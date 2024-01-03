#ifndef OPPORTUNISTICSECURESMTPCLIENT_H
#define OPPORTUNISTICSECURESMTPCLIENT_H

#include "securesmtpclientbase.h"

#ifdef _WIN32
    #ifdef SMTPCLIENT_EXPORTS
        #define OPPORTUNISTICSECURESMTPCLIENT_API __declspec(dllexport)
    #else
        #define OPPORTUNISTICSECURESMTPCLIENT_API __declspec(dllimport)
    #endif
#else
    #define OPPORTUNISTICSECURESMTPCLIENT_API
#endif

namespace jed_utils {
/** @brief The OpportunisticSecureSMTPClient should be your default choice for
 *  communicating with modern SMTP servers. The communication is usually done
 *  via port 587.
 */
class OPPORTUNISTICSECURESMTPCLIENT_API OpportunisticSecureSMTPClient : public SecureSMTPClientBase {
 public:
    /**
     *  @brief  Construct a new OpportunisticSecureSMTPClient.
     *  @param pServerName The name of the server.
     *  Example: smtp.domainexample.com
     *  @param pPort The server port number.
     *  Example: 25, 465, 587
     */
    OpportunisticSecureSMTPClient(const char *pServerName, unsigned int pPort);

    /** Destructor of the OpportunisticSecureSMTPClient. */
    ~OpportunisticSecureSMTPClient() override = default;

    /** OpportunisticSecureSMTPClient copy constructor. */
    OpportunisticSecureSMTPClient(const OpportunisticSecureSMTPClient& other) = default;

    /** OpportunisticSecureSMTPClient copy assignment operator. */
    OpportunisticSecureSMTPClient& operator=(const OpportunisticSecureSMTPClient& other);

    /** OpportunisticSecureSMTPClient move constructor. */
    OpportunisticSecureSMTPClient(OpportunisticSecureSMTPClient&& other) noexcept;

    /** OpportunisticSecureSMTPClient move assignment operator. */
    OpportunisticSecureSMTPClient& operator=(OpportunisticSecureSMTPClient&& other) noexcept;

 protected:
    int establishConnectionWithServer() override;
    int upgradeToSecureConnection();
    static bool isStartTLSSupported(const char *pServerResponse);
};
}  // namespace jed_utils


#endif
