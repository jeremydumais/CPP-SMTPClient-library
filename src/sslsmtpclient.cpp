#include "sslsmtpclient.h"
#include "socketerrors.h"
#include "sslerrors.h"
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#ifdef _WIN32
	#include <WinSock2.h>
    #include <ws2tcpip.h>
#else
    #include <fcntl.h>
    #include <openssl/bio.h> /* BasicInput/Output streams */
    #include <openssl/err.h>
    #include <netdb.h>
    #include <netinet/in.h>
    #include <sys/socket.h>	
    #include <unistd.h>
#endif
#include <vector>

using namespace std;
using namespace jed_utils;

SSLSmtpClient::SSLSmtpClient(const char *pServerName, unsigned int pPort)
    : mServerName(nullptr),
      mPort(pPort),
      mCommunicationLog(nullptr),
      mCommandTimeOut(3),
      mLastSocketErrNo(0),
      mBIO(nullptr),
      mCTX(nullptr),
      mSSL(nullptr)
{
    size_t server_name_len = strlen(pServerName);
	mServerName = new char[server_name_len + 1];
	strncpy(mServerName, pServerName, server_name_len);
    mServerName[server_name_len] = '\0';
}

SSLSmtpClient::~SSLSmtpClient()
{    
    delete[] mServerName;
    mServerName = nullptr;
    delete[] mCommunicationLog;
    mCommunicationLog = nullptr;
}

void SSLSmtpClient::cleanup()
{
    SSL_CTX_free(mCTX);
    mCTX = nullptr;
    BIO_free_all(mBIO);
    mBIO = nullptr;
}

int SSLSmtpClient::initSession(const unsigned int pSock) 
{
    delete[] mCommunicationLog;
    mCommunicationLog = new char[4096];
    mCommunicationLog[0] = '\0';

    char outbuf[1024];
    struct hostent *host = gethostbyname(mServerName);
    struct sockaddr_in saddr_in {};
    saddr_in.sin_family = AF_INET;
    saddr_in.sin_port = htons(static_cast<u_short>(mPort));
    saddr_in.sin_addr.s_addr = 0;
    memcpy(reinterpret_cast<char*>(&(saddr_in.sin_addr)), host->h_addr, host->h_length);
    stringstream ss;
    ss << "Trying to connect to " << mServerName << " on port " << mPort;
    addCommunicationLogItem(ss.str().c_str());
    if (connect(pSock, reinterpret_cast<struct sockaddr*>(&saddr_in), sizeof(saddr_in)) == -1) {
        mLastSocketErrNo = errno;
        return SOCKET_INIT_SESSION_CONNECT_ERROR;
    } 

    unsigned int waitTime = 0;
    ssize_t bytes_received = 0;
    while ((bytes_received = recv(pSock, outbuf, 1024, 0)) < 0 && waitTime < mCommandTimeOut)
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

int SSLSmtpClient::initClient(const unsigned int pSock) 
{
    char outbuf[1024];

    string ehlo { "ehlo localhost\r\n" };
    addCommunicationLogItem("ehlo localhost\\r\\n");
    if (send(pSock, ehlo.c_str(), ehlo.length(), 0) == -1) {
        mLastSocketErrNo = errno;
        return SOCKET_INIT_CLIENT_SEND_EHLO_ERROR;
    }
    unsigned int waitTime = 0;
    ssize_t bytes_received = 0;
    while ((bytes_received = recv(pSock, outbuf, 1024, 0)) < 0 && waitTime < mCommandTimeOut)
    {
        sleep(1);
        waitTime += 1;
    }
    if (waitTime < mCommandTimeOut) {
        outbuf[bytes_received-1] = '\0';
        addCommunicationLogItem(outbuf, "s");
        return extractReturnCode(outbuf);
    }
    
    return SOCKET_INIT_CLIENT_SEND_EHLO_TIMEOUT;
}

int SSLSmtpClient::initTLS(const unsigned int pSock)
{
    char outbuf[1024];

    string ehlo { "STARTTLS\r\n" };
    addCommunicationLogItem("STARTTLS\\r\\n");
    if (send(pSock, ehlo.c_str(), ehlo.length(), 0) == -1) {
        mLastSocketErrNo = errno;
        return SOCKET_INIT_CLIENT_SEND_STARTTLS_ERROR;
    }
    unsigned int waitTime = 0;
    ssize_t bytes_received = 0;
    while ((bytes_received = recv(pSock, outbuf, 1024, 0)) < 0 && waitTime < mCommandTimeOut)
    {
        sleep(1);
        waitTime += 1;
    }
    if (waitTime < mCommandTimeOut) {
        outbuf[bytes_received-1] = '\0';
        addCommunicationLogItem(outbuf, "s");
        return extractReturnCode(outbuf);
    }
    
    return SOCKET_INIT_CLIENT_SEND_STARTTLS_TIMEOUT;
}

void SSLSmtpClient::InitSSL_CTX()
{
    SSL_library_init();

    OpenSSL_add_all_algorithms();
    SSL_load_error_strings();
    const SSL_METHOD *method = TLSv1_2_client_method();
    mCTX = SSL_CTX_new(method);

    if (mCTX == nullptr) {
        mLastSocketErrNo = ERR_get_error();
    }
}

int SSLSmtpClient::startTLS(const unsigned int pSock)
{
    addCommunicationLogItem("<Start TLS negotiation>");    
    InitSSL_CTX();
    if (mCTX == nullptr) {
        return SSL_CLIENT_STARTTLS_INITSSLCTX_ERROR;
    }

    mBIO = BIO_new_ssl_connect(mCTX);
    if (mBIO == nullptr) {
        return SSL_CLIENT_STARTTLS_BIONEWSSLCONNECT_ERROR;
    }

    /* Link bio channel, SSL session, and server endpoint */
    char name[1024];
    sprintf(name, "%s:%i", mServerName, mPort);
    BIO_get_ssl(mBIO, &mSSL); /* session */
    SSL_set_fd(mSSL, pSock);
    SSL_set_mode(mSSL, SSL_MODE_AUTO_RETRY); /* robustness */
    BIO_set_conn_hostname(mBIO, name); /* prepare to connect */

    /* Specifies the locations for ctx, at which CA certificates 
       for verification purposes are located */
    if (!SSL_CTX_load_verify_locations(mCTX,
            "/etc/ssl/certs/ca-certificates.crt", 
            "/etc/ssl/certs/")) {
        mLastSocketErrNo = ERR_get_error();
        return SSL_CLIENT_STARTTLS_CTX_LOAD_VERIFY_LOCATIONS_ERROR;
    }

    long verify_flag = SSL_get_verify_result(mSSL);
    if (verify_flag != X509_V_OK) {
        fprintf(stderr,
            "##### Certificate verification error (%i) but continuing...\n",
            (int)verify_flag);
    }

    /* Try to connect */
    if (BIO_do_connect(mBIO) <= 0) {
        cleanup();
        mLastSocketErrNo = ERR_get_error();
        return SSL_CLIENT_STARTTLS_BIO_CONNECT_ERROR;
    }

    /* Try to do the handshake */
    addCommunicationLogItem("<Negotiate a TLS session>", "c & s");    
    if (BIO_do_handshake(mBIO) <= 0) {
        cleanup();
        mLastSocketErrNo = ERR_get_error();
        return SSL_CLIENT_STARTTLS_BIO_HANDSHAKE_ERROR;
    }

    addCommunicationLogItem("<Check result of negotiation>", "c & s");    
    /* Step 1: Verify a server certificate was presented 
       during the negotiation */
    X509* cert = SSL_get_peer_certificate(mSSL);
    if(cert != nullptr) { 
        X509_free(cert); /* Free immediately */
    } 
    if(cert == nullptr) {
        cleanup();
        return SSL_CLIENT_STARTTLS_GET_CERTIFICATE_ERROR;
    }

    /* Step 2: verify the result of chain verification */
    /* Verification performed according to RFC 4158    */
    int res = SSL_get_verify_result(mSSL);
    if(!(X509_V_OK == res)) {
        cleanup();
        return SSL_CLIENT_STARTTLS_VERIFY_RESULT_ERROR;
    }

    addCommunicationLogItem("TLS session ready!");    

    return 0;
}

int SSLSmtpClient::initSecureClient()
{
    addCommunicationLogItem("Contacting the server again but via the secure channel...");
    addCommunicationLogItem("ehlo localhost\\r\\n");
    if (const int status = BIO_puts(mBIO, "ehlo localhost\r\n") < 0) {
        mLastSocketErrNo = ERR_get_error();
        cleanup();
        return SSL_CLIENT_INITSECURECLIENT_ERROR;
    }
    unsigned int waitTime {0};
    int bytes_received {0};
    char outbuf[1024];
    
    while ((bytes_received = BIO_read(mBIO, outbuf, 1024)) <= 0 && waitTime < mCommandTimeOut) {
        sleep(1);
        waitTime += 1;
    }
    if (waitTime < mCommandTimeOut) {
        outbuf[bytes_received-1] = '\0';
        addCommunicationLogItem(outbuf, "s");
        cleanup(); //To be removed
        return 0;
    }
    else {
        cleanup();
        return SSL_CLIENT_INITSECURECLIENT_TIMEOUT;
    }
}

int SSLSmtpClient::authenticate(const char* pUsername, const char* pPassword)
{
    string username { pUsername };
    string password { pPassword };
    return 0;
}

const char *SSLSmtpClient::getCommunicationLog() const
{
    return mCommunicationLog;
}

int SSLSmtpClient::extractReturnCode(const char *pOutput) const
{
    if (pOutput != nullptr && strlen(pOutput) >= 3) {
        string code_str { pOutput };
        try {
            return std::stoi(code_str.substr(0, 3));
        } 
        catch (std::exception const &e) {
            return -1;
        }
    }
    return -1;
}

void SSLSmtpClient::addCommunicationLogItem(const char *pItem, const char *pPrefix)
{
    strcat(mCommunicationLog, "\n");
    strcat(mCommunicationLog, pPrefix);
    strcat(mCommunicationLog, ": ");
    strcat(mCommunicationLog, pItem);
}