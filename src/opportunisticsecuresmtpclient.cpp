#include "smtpclienterrors.h"
#include "socketerrors.h"
#include "sslerrors.h"
#include "opportunisticsecuresmtpclient.h"
#include <openssl/err.h>

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
    #include <unistd.h>
    #include <netinet/in.h>
    #include <openssl/bio.h> /* BasicInput/Output streams */
#endif

using namespace std;
using namespace jed_utils;

OpportunisticSecureSMTPClient::OpportunisticSecureSMTPClient(const char *pServerName, unsigned int pPort)
    : SecureSmtpClientBase(pServerName, pPort)
{
}

OpportunisticSecureSMTPClient::~OpportunisticSecureSMTPClient()
{    
}

//Copy constructor
OpportunisticSecureSMTPClient::OpportunisticSecureSMTPClient(const OpportunisticSecureSMTPClient& other)
	: SecureSmtpClientBase(other)
{    
}

//Assignment operator
OpportunisticSecureSMTPClient& OpportunisticSecureSMTPClient::operator=(const OpportunisticSecureSMTPClient& other)
{
	if (this != &other) {
        SecureSmtpClientBase::operator=(other);
	}
	return *this;
}

//Move constructor
OpportunisticSecureSMTPClient::OpportunisticSecureSMTPClient(OpportunisticSecureSMTPClient&& other) noexcept
	: SecureSmtpClientBase(move(other))
{
}

//Move assignement operator
OpportunisticSecureSMTPClient& OpportunisticSecureSMTPClient::operator=(OpportunisticSecureSMTPClient&& other) noexcept
{
	if (this != &other) {
        SecureSmtpClientBase::operator=(move(other));
	}
	return *this;
}

int OpportunisticSecureSMTPClient::establishConnectionWithServer()
{
    int session_init_return_code = initializeSession();
    if (session_init_return_code != 0) {
        return session_init_return_code;
    }

    int server_greetings_return_code = checkServerGreetings();
    if (server_greetings_return_code != 220) {
        return server_greetings_return_code;
    }

    int client_init_return_code = sendServerIdentification();
    if (client_init_return_code != 250) {
        return client_init_return_code;
    }

    int tls_init_return_code = upgradeToSecureConnection();
    if (tls_init_return_code != 220) {
        return tls_init_return_code;
    }

    int tls_start_return_code = startTLSNegotiation();
    if (tls_start_return_code != 0) {
        return tls_start_return_code;
    }

    int client_initSecure_return_code = getServerSecureIdentification();
    if (client_initSecure_return_code != 250) {
        return client_initSecure_return_code;
    }

    if (getCredentials() != nullptr) {
        int client_auth_return_code = authenticateClient();
        if (client_auth_return_code != 235) {
            return client_auth_return_code;
        }
    }
    return 0;
}

int OpportunisticSecureSMTPClient::upgradeToSecureConnection()
{
    string start_tls_cmd { "STARTTLS\r\n" };
    addCommunicationLogItem(start_tls_cmd.c_str());
    return sendRawCommand(start_tls_cmd.c_str(), 
        SOCKET_INIT_CLIENT_SEND_STARTTLS_ERROR, 
        SOCKET_INIT_CLIENT_SEND_STARTTLS_TIMEOUT);
}
