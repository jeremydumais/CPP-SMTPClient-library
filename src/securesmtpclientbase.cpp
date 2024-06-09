#include "securesmtpclientbase.h"
#include <openssl/err.h>
#include <openssl/x509_vfy.h>
#include <string>
#include <utility>
#include "serveroptionsanalyzer.h"
#include "smtpclienterrors.h"
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

using namespace std::literals::string_literals;
using namespace jed_utils;

SecureSMTPClientBase::SecureSMTPClientBase(const char *pServerName, unsigned int pPort)
    : SMTPClientBase(pServerName, pPort),
    mBIO(nullptr),
    mCTX(nullptr),
    mSSL(nullptr),
    mAcceptSelfSignedCert(false) {
}

SecureSMTPClientBase::~SecureSMTPClientBase() {
    SecureSMTPClientBase::cleanup();
}

// Copy constructor
SecureSMTPClientBase::SecureSMTPClientBase(const SecureSMTPClientBase& other)
    : SMTPClientBase(other),
    mBIO(nullptr),
    mCTX(nullptr),
    mSSL(nullptr),
    mAcceptSelfSignedCert(other.mAcceptSelfSignedCert) {
}

// Assignment operator
SecureSMTPClientBase& SecureSMTPClientBase::operator=(const SecureSMTPClientBase& other) {
    if (this != &other) {
        SMTPClientBase::operator=(other);
        mBIO = nullptr;
        mCTX = nullptr;
        mSSL = nullptr;
        mAcceptSelfSignedCert = other.mAcceptSelfSignedCert;
    }
    return *this;
}

// Move constructor
SecureSMTPClientBase::SecureSMTPClientBase(SecureSMTPClientBase&& other) noexcept
: SMTPClientBase(std::move(other)),
    mBIO(other.mBIO),
    mCTX(other.mCTX),
    mSSL(other.mSSL),
    mAcceptSelfSignedCert(other.mAcceptSelfSignedCert) {
    // Release the data pointer from the source object so that the destructor
    // does not free the memory multiple times.
    other.mBIO = nullptr;
    other.mCTX = nullptr;
    other.mSSL = nullptr;
    other.mAcceptSelfSignedCert = false;
}

// Move assignement operator
SecureSMTPClientBase& SecureSMTPClientBase::operator=(SecureSMTPClientBase&& other) noexcept {
    if (this != &other) {
        // Copy the data pointer and its length from the source object.
        mBIO = other.mBIO;
        mCTX = other.mCTX;
        mSSL = other.mSSL;
        mAcceptSelfSignedCert = other.mAcceptSelfSignedCert;
        // Release the data pointer from the source object so that
        // the destructor does not free the memory multiple times.
        other.mBIO = nullptr;
        other.mCTX = nullptr;
        other.mSSL = nullptr;
        other.mAcceptSelfSignedCert = false;
        SMTPClientBase::operator=(std::move(other));
    }
    return *this;
}

bool SecureSMTPClientBase::getAcceptSelfSignedCert() const {
    return mAcceptSelfSignedCert;
}

void SecureSMTPClientBase::setAcceptSelfSignedCert(bool pValue) {
    mAcceptSelfSignedCert = pValue;
}

void SecureSMTPClientBase::cleanup() {
    if (getBatchMode() && mIsConnected) {
        sendQuitCommand();
    }
    mIsConnected = false;
    if (mCTX != nullptr) {
        SSL_CTX_free(mCTX);
    }
    mCTX = nullptr;
    if (mBIO != nullptr) {
        BIO_free_all(mBIO);
    }
    mBIO = nullptr;
    int socketFileDescriptor {getSocketFileDescriptor() };
    if (socketFileDescriptor != 0) {
#ifdef _WIN32
        shutdown(socketFileDescriptor, SD_BOTH);
        closesocket(socketFileDescriptor);
#else
        close(socketFileDescriptor);
#endif
    }
    clearSocketFileDescriptor();
    mSSL = nullptr;
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

BIO* SecureSMTPClientBase::getBIO() const {
    return mBIO;
}

void SecureSMTPClientBase::initializeSSLContext() {
    SSL_library_init();

    OpenSSL_add_all_algorithms();
    SSL_load_error_strings();
    const SSL_METHOD *method = TLS_client_method();
    mCTX = SSL_CTX_new(method);

    if (mCTX == nullptr) {
        setLastSocketErrNo(static_cast<int>(ERR_get_error()));
    }
}

int SecureSMTPClientBase::startTLSNegotiation() {
    addCommunicationLogItem("<Start TLS negotiation>");
    initializeSSLContext();
    if (mCTX == nullptr) {
        return SSL_CLIENT_STARTTLS_INITSSLCTX_ERROR;
    }

    mBIO = BIO_new_ssl_connect(mCTX);
    if (mBIO == nullptr) {
        return SSL_CLIENT_STARTTLS_BIONEWSSLCONNECT_ERROR;
    }

    /* Link bio channel, SSL session, and server endpoint */
    const int SERVERNAMEANDPORT_LENGTH = 1024;
    char name[SERVERNAMEANDPORT_LENGTH];
    sprintf(name, "%s:%u", getServerName(), getServerPort());
    BIO_get_ssl(mBIO, &mSSL); /* session */
    SSL_set_fd(mSSL, getSocketFileDescriptor());
    SSL_set_mode(mSSL, SSL_MODE_AUTO_RETRY); /* robustness */
    BIO_set_conn_hostname(mBIO, name); /* prepare to connect */

#ifdef _WIN32
    /* On Windows, we need to import all the ROOT certificates to
       the OpenSSL Store */
    PCCERT_CONTEXT pContext = nullptr;
    X509_STORE *store = SSL_CTX_get_cert_store(mCTX);
    HCERTSTORE hStore = CertOpenSystemStore(NULL, "ROOT");

    if (!hStore) {
        setLastSocketErrNo(static_cast<int>(GetLastError()));
        return SSL_CLIENT_STARTTLS_WIN_CERTOPENSYSTEMSTORE_ERROR;
    }

    pContext = CertEnumCertificatesInStore(hStore, pContext);
    while (pContext) {
        X509 *x509 = nullptr;
        x509 = d2i_X509(nullptr, (const unsigned char **)&pContext->pbCertEncoded, pContext->cbCertEncoded);
        if (x509) {
            X509_STORE_add_cert(store, x509);
            X509_free(x509);
        }
        pContext = CertEnumCertificatesInStore(hStore, pContext);
    }
#else
    if (SSL_CTX_set_default_verify_paths(mCTX) == 0) {
        return SSL_CLIENT_STARTTLS_CTX_SET_DEFAULT_VERIFY_PATHS_ERROR;
    }
#endif
    long verify_flag = SSL_get_verify_result(mSSL);
    if (verify_flag != X509_V_OK) {
        fprintf(stderr,
                "##### Certificate verification error (%i) but continuing...\n",
                static_cast<int>(verify_flag));
    }

    /* Try to connect */
    if (BIO_do_connect(mBIO) <= 0) {
        cleanup();
        setLastSocketErrNo(static_cast<int>(ERR_get_error()));
        return SSL_CLIENT_STARTTLS_BIO_CONNECT_ERROR;
    }

    /* Try to do the handshake */
    addCommunicationLogItem("<Negotiate a TLS session>", "c & s");
    if (BIO_do_handshake(mBIO) <= 0) {
        cleanup();
        setLastSocketErrNo(static_cast<int>(ERR_get_error()));
        return SSL_CLIENT_STARTTLS_BIO_HANDSHAKE_ERROR;
    }

    addCommunicationLogItem("<Check result of negotiation>", "c & s");
    /* Step 1: Verify a server certificate was presented
       during the negotiation */
    X509* cert = SSL_get_peer_certificate(mSSL);
    if (cert != nullptr) {
        X509_free(cert); /* Free immediately */
    }
    if (cert == nullptr) {
        cleanup();
        return SSL_CLIENT_STARTTLS_GET_CERTIFICATE_ERROR;
    }

    /* Step 2: verify the result of chain verification */
    /* Verification performed according to RFC 4158    */
    int res = static_cast<int>(SSL_get_verify_result(mSSL));
    if (res == X509_V_ERR_DEPTH_ZERO_SELF_SIGNED_CERT && getAcceptSelfSignedCert()) {
        addCommunicationLogItem("Warning: Self signed certificate", "s");
    } else {
        if (!(X509_V_OK == res)) {
            addCommunicationLogItem(X509_verify_cert_error_string(res), "s");
            cleanup();
            return SSL_CLIENT_STARTTLS_VERIFY_RESULT_ERROR;
        }
    }

    addCommunicationLogItem("TLS session ready!");

#ifdef _WIN32
    CertFreeCertificateContext(pContext);
    CertCloseStore(hStore, 0);
#endif
    return 0;
}

int SecureSMTPClientBase::getServerSecureIdentification() {
    const int EHLO_SUCCESS_CODE = 250;
    addCommunicationLogItem("Contacting the server again but via the secure channel...");
    std::string ehlo { "ehlo localhost\r\n"s };
    addCommunicationLogItem(ehlo.c_str());
    int tls_command_return_code = sendCommandWithFeedback(ehlo.c_str(),
            SSL_CLIENT_INITSECURECLIENT_ERROR,
            SSL_CLIENT_INITSECURECLIENT_TIMEOUT);
    if (tls_command_return_code != EHLO_SUCCESS_CODE) {
        return tls_command_return_code;
    }
    std::string returnedOptions = getLastServerResponse();
    // Check that the last returned option has no hyphen otherwise options are
    // still missing from the server.
    while (!ServerOptionsAnalyzer::containsAllOptions(returnedOptions)) {
        int replyCode = getServerReply();
        if (replyCode == -1) {
            return SSL_CLIENT_INITSECURECLIENT_TIMEOUT;
        } else if (replyCode != EHLO_SUCCESS_CODE) {
            return replyCode;
        }
        returnedOptions += "\n" + std::string(getLastServerResponse());
    }
    // Inspect the returned values for authentication options
    setAuthenticationOptions(SMTPClientBase::extractAuthenticationOptions(returnedOptions.c_str()));
    return EHLO_SUCCESS_CODE;
}

int SecureSMTPClientBase::sendCommand(const char *pCommand, int pErrorCode) {
    if (BIO_puts(mBIO, pCommand) < 0) {
        setLastSocketErrNo(static_cast<int>(ERR_get_error()));
        cleanup();
        return pErrorCode;
    }
    return 0;
}

int SecureSMTPClientBase::sendCommandWithFeedback(const char *pCommand, int pErrorCode, int pTimeoutCode) {
    // Check if we are in the TLS mode of before it
    if (mBIO == nullptr) {
        return sendRawCommand(pCommand, pErrorCode, pTimeoutCode);
    }
    if (BIO_puts(mBIO, pCommand) < 0) {
        setLastSocketErrNo(static_cast<int>(ERR_get_error()));
        cleanup();
        return pErrorCode;
    }

    int serverReplyCode = getServerReply();
    if (serverReplyCode != -1) {
        return serverReplyCode;
    }

    cleanup();
    return pTimeoutCode;
}

int SecureSMTPClientBase::getServerReply() {
    unsigned int waitTime {0};
    int bytes_received {0};
    char outbuf[SERVERRESPONSE_BUFFER_LENGTH];
    while ((bytes_received = BIO_read(mBIO, outbuf, SERVERRESPONSE_BUFFER_LENGTH)) <= 0 && waitTime < getCommandTimeout()) {
        crossPlatformSleep(1);
        waitTime += 1;
    }
    if (waitTime < getCommandTimeout()) {
        outbuf[bytes_received-1] = '\0';
        setLastServerResponse(outbuf);
        addCommunicationLogItem(outbuf, "s");
        return extractReturnCode(outbuf);
    }
    return -1;
}
