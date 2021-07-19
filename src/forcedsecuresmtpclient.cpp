#include "smtpclienterrors.h"
#include "socketerrors.h"
#include "sslerrors.h"
#include "forcedsecuresmtpclient.h"
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

ForcedSecureSMTPClient::ForcedSecureSMTPClient(const char *pServerName, unsigned int pPort)
    : SecureSmtpClientBase(pServerName, pPort)
{
}

ForcedSecureSMTPClient::~ForcedSecureSMTPClient()
{    
}

//Copy constructor
ForcedSecureSMTPClient::ForcedSecureSMTPClient(const ForcedSecureSMTPClient& other)
	: SecureSmtpClientBase(other)
{    
}

//Assignment operator
ForcedSecureSMTPClient& ForcedSecureSMTPClient::operator=(const ForcedSecureSMTPClient& other)
{
	if (this != &other) {
        SecureSmtpClientBase::operator=(other);
	}
	return *this;
}

//Move constructor
ForcedSecureSMTPClient::ForcedSecureSMTPClient(ForcedSecureSMTPClient&& other) noexcept
	: SecureSmtpClientBase(move(other))
{
}

//Move assignement operator
ForcedSecureSMTPClient& ForcedSecureSMTPClient::operator=(ForcedSecureSMTPClient&& other) noexcept
{
	if (this != &other) {
        SecureSmtpClientBase::operator=(move(other));
	}
	return *this;
}

int ForcedSecureSMTPClient::establishConnectionWithServer()
{
    int session_init_return_code = initializeSession();
    if (session_init_return_code != 0) {
        return session_init_return_code;
    }
    
    int tls_start_return_code = startTLSNegotiation();
    if (tls_start_return_code != 0) {
        return tls_start_return_code;
    }

    int server_greetings_return_code = checkServerGreetings();
    if (server_greetings_return_code != 220) {
        return server_greetings_return_code;
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

int ForcedSecureSMTPClient::checkServerGreetings() 
{
    char outbuf[1024];
    unsigned int waitTime = 0;
    ssize_t bytes_received = 0;
    while ((bytes_received = BIO_read(mBIO, outbuf, 1024)) <= 0 && waitTime < mCommandTimeOut)
    {
        sleep(1);
        waitTime += 1;
    }
    if (waitTime < mCommandTimeOut) {
        outbuf[bytes_received-1] = '\0';
        addCommunicationLogItem(outbuf, "s");
        int status_code = extractReturnCode(outbuf);
        if (status_code == 220) {
            addCommunicationLogItem("Connected!");
        }
        return status_code;
    }
    return SOCKET_INIT_SESSION_CONNECT_TIMEOUT;
}

