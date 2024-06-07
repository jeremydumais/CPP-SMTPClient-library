#include "smtpclient.h"
#include "smtpserverstatuscodes.h"
#ifdef _WIN32
    #include <WinSock2.h>
    #include <ws2tcpip.h>
#else
    #include <netdb.h>
    #include <netinet/in.h>
    #include <sys/socket.h>
    #include <unistd.h>
#endif
#include <sstream>
#include <vector>
#include <utility>

using namespace jed_utils;

SmtpClient::SmtpClient(const char *pServerName, unsigned int pPort)
    : SMTPClientBase(pServerName, pPort) {
}

SmtpClient::~SmtpClient() {
    SmtpClient::cleanup();
}

// Assignment operator
SmtpClient& SmtpClient::operator=(const SmtpClient &other) {
    if (this != &other) {
        SMTPClientBase::operator=(other);
    }
    return *this;
}

// Move constructor
SmtpClient::SmtpClient(SmtpClient &&other) noexcept
    : SMTPClientBase(std::move(other)) {
}

// Move assignement
SmtpClient& SmtpClient::operator=(SmtpClient &&other) noexcept {
    if (this != &other) {
        SMTPClientBase::operator=(std::move(other));
    }
    return *this;
}

void SmtpClient::cleanup() {
    if (getBatchMode() && mIsConnected) {
        sendQuitCommand();
    }
    mIsConnected = false;
    int socket { getSocketFileDescriptor() };
    if (socket != 0) {
#ifdef _WIN32
        shutdown(socket, SD_BOTH);
        closesocket(socket);
#else
        close(socket);
#endif
    }
    clearSocketFileDescriptor();
#ifdef _WIN32
    if (isWSAStarted() && WSACleanup() != 0) {
        int wsa_retVal = WSAGetLastError();
        std::stringstream ssError;
        setLastSocketErrNo(wsa_retVal);
        ssError << "WSACleanup failed with error: " << wsa_retVal;
        addCommunicationLogItem(ssError.str().c_str());
    }
    setWSAStopped();
#endif
}

int SmtpClient::establishConnectionWithServer() {
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

    if (getCredentials() != nullptr) {
        int client_auth_return_code = authenticateClient();
        if (client_auth_return_code != STATUS_CODE_AUTHENTICATION_SUCCEEDED) {
            return client_auth_return_code;
        }
    }

    return 0;
}

int SmtpClient::sendCommand(const char *pCommand, int pErrorCode) {
    return sendRawCommand(pCommand, pErrorCode);
}

int SmtpClient::sendCommandWithFeedback(const char *pCommand, int pErrorCode, int pTimeoutCode) {
    return sendRawCommand(pCommand, pErrorCode, pTimeoutCode);
}

int SmtpClient::getServerReply() {
    return getRawCommandReply();
}
