#include "opportunisticsecuresmtpclient.h"
#include <openssl/err.h>
#include <string>
#include <utility>
#include "smtpserverstatuscodes.h"
#include "socketerrors.h"
#include "stringutils.h"

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

OpportunisticSecureSMTPClient::OpportunisticSecureSMTPClient(const char *pServerName, unsigned int pPort)
    : SecureSMTPClientBase(pServerName, pPort) {
}

// Assignment operator
OpportunisticSecureSMTPClient& OpportunisticSecureSMTPClient::operator=(const OpportunisticSecureSMTPClient& other) {
    if (this != &other) {
        SecureSMTPClientBase::operator=(other);
    }
    return *this;
}

// Move constructor
OpportunisticSecureSMTPClient::OpportunisticSecureSMTPClient(OpportunisticSecureSMTPClient&& other) noexcept
    : SecureSMTPClientBase(std::move(other)) {
}

// Move assignement operator
OpportunisticSecureSMTPClient& OpportunisticSecureSMTPClient::operator=(OpportunisticSecureSMTPClient&& other) noexcept {
    if (this != &other) {
        SecureSMTPClientBase::operator=(std::move(other));
    }
    return *this;
}

int OpportunisticSecureSMTPClient::establishConnectionWithServer() {
    int session_init_return_code = initializeSession();
    if (session_init_return_code != 0) {
        return session_init_return_code;
    }

    int server_greetings_return_code = checkServerGreetings();
    if (server_greetings_return_code != STATUS_CODE_SERVICE_READY) {
        return server_greetings_return_code;
    }

    int client_init_return_code = sendServerIdentification();
    if (client_init_return_code != STATUS_CODE_REQUESTED_MAIL_ACTION_OK_OR_COMPLETED) {
        return client_init_return_code;
    }

    if (isStartTLSSupported(getLastServerResponse())) {
        addCommunicationLogItem("Info: STARTTLS is available by the server, the communication will be encrypted.");
        int tls_init_return_code = upgradeToSecureConnection();
        if (tls_init_return_code != STATUS_CODE_SERVICE_READY) {
            return tls_init_return_code;
        }
        int tls_start_return_code = startTLSNegotiation();
        if (tls_start_return_code != 0) {
            return tls_start_return_code;
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
    } else {
        addCommunicationLogItem("Info: STARTTLS is not an available option by the server, the communication will then remain unencrypted.");
        setKeepUsingBaseSendCommands(true);
    }
    return 0;
}

int OpportunisticSecureSMTPClient::upgradeToSecureConnection() {
    std::string start_tls_cmd { "STARTTLS\r\n" };
    addCommunicationLogItem(start_tls_cmd.c_str());
    return sendRawCommand(start_tls_cmd.c_str(),
            SOCKET_INIT_CLIENT_SEND_STARTTLS_ERROR,
            SOCKET_INIT_CLIENT_SEND_STARTTLS_TIMEOUT);
}


bool OpportunisticSecureSMTPClient::isStartTLSSupported(const char *pServerResponse) {
    if (pServerResponse == nullptr) {
        return false;
    }
    std::string serverResponse { pServerResponse };
    if (serverResponse.length() == 0 || StringUtils::trim(serverResponse).empty()) {
        return false;
    }

    const std::string STARTTLS_LINE_PREFIX { "250-STARTTLS" };
    return serverResponse.find(STARTTLS_LINE_PREFIX) != std::string::npos;
}
