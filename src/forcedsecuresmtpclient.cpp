#include "forcedsecuresmtpclient.h"
#include <openssl/err.h>
#include <utility>
#include "smtpclienterrors.h"
#include "smtpserverstatuscodes.h"
#include "socketerrors.h"
#include "sslerrors.h"

#ifdef _WIN32
    #include <WinSock2.h>
    #include <ws2tcpip.h>
    #include <BaseTsd.h>
    typedef SSIZE_T ssize_t;
    #include <windows.h>
    constexpr auto sleep = Sleep;
#else
    #include <fcntl.h>
    #include <netdb.h>
    #include <netinet/in.h>
    #include <openssl/bio.h> /* BasicInput/Output streams */
    #include <unistd.h>
#endif

using namespace jed_utils;

ForcedSecureSMTPClient::ForcedSecureSMTPClient(const char *pServerName, unsigned int pPort)
    : SecureSMTPClientBase(pServerName, pPort) {
}

// Assignment operator
ForcedSecureSMTPClient& ForcedSecureSMTPClient::operator=(const ForcedSecureSMTPClient& other) {
    if (this != &other) {
        SecureSMTPClientBase::operator=(other);
    }
    return *this;
}

// Move constructor
ForcedSecureSMTPClient::ForcedSecureSMTPClient(ForcedSecureSMTPClient&& other) noexcept
    : SecureSMTPClientBase(std::move(other)) {
}

// Move assignement operator
ForcedSecureSMTPClient& ForcedSecureSMTPClient::operator=(ForcedSecureSMTPClient&& other) noexcept {
    if (this != &other) {
        SecureSMTPClientBase::operator=(std::move(other));
    }
    return *this;
}

int ForcedSecureSMTPClient::establishConnectionWithServer() {
    int session_init_return_code = initializeSession();
    if (session_init_return_code != 0) {
        return session_init_return_code;
    }

    int tls_start_return_code = startTLSNegotiation();
    if (tls_start_return_code != 0) {
        return tls_start_return_code;
    }

    int server_greetings_return_code = checkServerGreetings();
    if (server_greetings_return_code != STATUS_CODE_SERVICE_READY) {
        return server_greetings_return_code;
    }

    int client_initSecure_return_code = getServerSecureIdentification();
    if (client_initSecure_return_code != STATUS_CODE_REQUESTED_MAIL_ACTION_OK_OR_COMPLETED) {
        return client_initSecure_return_code;
    }

    if (getCredentials() != nullptr) {
        int client_auth_return_code = authenticateClient();
        if (client_auth_return_code != STATUS_CODE_AUTHENTICATION_SUCCEEDED) {
            return client_auth_return_code;
        }
    }
    return 0;
}

int ForcedSecureSMTPClient::checkServerGreetings() {
    char outbuf[SERVERRESPONSE_BUFFER_LENGTH];
    unsigned int waitTime = 0;
    ssize_t bytes_received = 0;
    while ((bytes_received = BIO_read(getBIO(), outbuf, SERVERRESPONSE_BUFFER_LENGTH)) <= 0 && waitTime < getCommandTimeout()) {
        crossPlatformSleep(1);
        waitTime += 1;
    }
    if (waitTime < getCommandTimeout()) {
        outbuf[bytes_received-1] = '\0';
        addCommunicationLogItem(outbuf, "s");
        int status_code = extractReturnCode(outbuf);
        if (status_code == STATUS_CODE_SERVICE_READY) {
            addCommunicationLogItem("Connected!");
        }
        return status_code;
    }
    return SOCKET_INIT_SESSION_CONNECT_TIMEOUT;
}

