#include "errorresolver.h"

#include "base64.h"

#include "smtpclienterrors.h"
#include "socketerrors.h"
#include "sslerrors.h"
#include <cstddef>
#include <cstring>
#include <string>

using namespace jed_utils;

ErrorResolver::ErrorResolver(int pErrorCode)
    : mErrorCode(pErrorCode) {
    std::string errorMessage = "";
    switch (mErrorCode) {
        case SOCKET_INIT_SESSION_CREATION_ERROR:
            errorMessage = "Unable to create the socket";
            break;
        case SOCKET_INIT_SESSION_CONNECT_ERROR:
            errorMessage = "Unable to connect to the socket";
            break;
        case SOCKET_INIT_SESSION_CONNECT_TIMEOUT:
            errorMessage = "The connection attempt has timed out";
            break;
        case SOCKET_INIT_SESSION_WINSOCKET_STARTUP_ERROR:
            errorMessage = "Unable to start WSA (Winsock)";
            break;
        case SOCKET_INIT_SESSION_WINSOCKET_GETADDRINFO_ERROR:
            errorMessage = "Unable to get address info (Winsock)";
            break;
        case SOCKET_INIT_SESSION_GETHOSTBYNAME_ERROR:
            errorMessage = "Unable to get host by name";
            break;
        case SOCKET_INIT_SESSION_FCNTL_GET_ERROR:
            errorMessage = "Unable to get socket file descriptor status flags";
            break;
        case SOCKET_INIT_SESSION_FCNTL_SET_ERROR:
            errorMessage = "Unable to set socket file descriptor status flags";
            break;
        case SOCKET_INIT_SESSION_GET_SOCKET_OPTIONS_ERROR:
            errorMessage = "Unable to get socket options";
            break;
        case SOCKET_INIT_SESSION_DELAYED_CONNECTION_ERROR:
            errorMessage = "Error in delayed connection";
            break;
        case SOCKET_INIT_CLIENT_SEND_EHLO_ERROR:
            errorMessage = "Unable to send the EHLO command";
            break;
        case SOCKET_INIT_CLIENT_SEND_EHLO_TIMEOUT:
            errorMessage = "The EHLO command has timed out";
            break;
        case SOCKET_INIT_CLIENT_SEND_STARTTLS_ERROR:
            errorMessage = "Unable to send the STARTTLS command";
            break;
        case SOCKET_INIT_CLIENT_SEND_STARTTLS_TIMEOUT:
            errorMessage = "The STARTTLS command has timed out";
            break;
        case SSL_CLIENT_STARTTLS_INITSSLCTX_ERROR:
            errorMessage = "Unable to initialize the SSL Context";
            break;
        case SSL_CLIENT_STARTTLS_BIONEWSSLCONNECT_ERROR:
            errorMessage = "Unable to create the SSL BIO";
            break;
        case SSL_CLIENT_STARTTLS_WIN_CERTOPENSYSTEMSTORE_ERROR:
            errorMessage = "Unable to open the Windows Certificate System Store";
            break;
        case SSL_CLIENT_STARTTLS_CTX_SET_DEFAULT_VERIFY_PATHS_ERROR:
            errorMessage = "Unable to open the specifies that the default locations from which CA certificates are loaded";
            break;
        case SSL_CLIENT_STARTTLS_BIO_CONNECT_ERROR:
            errorMessage = "Unable to connect SSL BIO";
            break;
        case SSL_CLIENT_STARTTLS_BIO_HANDSHAKE_ERROR:
            errorMessage = "Unable to handshake with SSL BIO";
            break;
        case SSL_CLIENT_STARTTLS_GET_CERTIFICATE_ERROR:
            errorMessage = "Unable to get peer certificate";
            break;
        case SSL_CLIENT_STARTTLS_VERIFY_RESULT_ERROR:
            errorMessage = "Unable to verify the result of chain verification";
            break;
        case SSL_CLIENT_INITSECURECLIENT_ERROR:
            errorMessage = "Unable to EHLO the server via the secure channel";
            break;
        case SSL_CLIENT_INITSECURECLIENT_TIMEOUT:
            errorMessage = "The EHLO command via the secure channel timed out";
            break;
        case CLIENT_AUTHENTICATE_ERROR:
            errorMessage = "Unable to authenticate with the credentials provided";
            break;
        case CLIENT_AUTHENTICATE_TIMEOUT:
            errorMessage = "The authentication to the server has timed out";
            break;
        case CLIENT_AUTHENTICATE_NONEED:
            errorMessage = "The authentication is not needed on the server";
            break;
        case CLIENT_AUTHENTICATION_METHOD_NOTSUPPORTED:
            errorMessage = "The authentication method selected is not supported by the server";
            break;
        case CLIENT_SENDMAIL_MAILFROM_ERROR:
            errorMessage = "The MAIL FROM command return an error";
            break;
        case CLIENT_SENDMAIL_MAILFROM_TIMEOUT:
            errorMessage = "The MAIL FROM command timed out";
            break;
        case CLIENT_SENDMAIL_RCPTTO_ERROR:
            errorMessage = "The RCPT TO command return an error";
            break;
        case CLIENT_SENDMAIL_RCPTTO_TIMEOUT:
            errorMessage = "The RCPT TO command timed out";
            break;
        case CLIENT_SENDMAIL_DATA_ERROR:
            errorMessage = "The DATA command return an error";
            break;
        case CLIENT_SENDMAIL_DATA_TIMEOUT:
            errorMessage = "The DATA command timed out";
            break;
        case CLIENT_SENDMAIL_HEADERFROM_ERROR:
            errorMessage = "The From header command return an error";
            break;
        case CLIENT_SENDMAIL_HEADERTOANDCC_ERROR:
            errorMessage = "The To and CC header command return an error";
            break;
        case CLIENT_SENDMAIL_HEADERSUBJECT_ERROR:
            errorMessage = "The Subject header command return an error";
            break;
        case CLIENT_SENDMAIL_HEADERCONTENTTYPE_ERROR:
            errorMessage = "The Content type header command return an error";
            break;
        case CLIENT_SENDMAIL_BODYPART_ERROR:
            errorMessage = "The Body part return an error";
            break;
        case CLIENT_SENDMAIL_BODY_ERROR:
            errorMessage = "The Body command return an error";
            break;
        case CLIENT_SENDMAIL_END_DATA_ERROR:
            errorMessage = "The End data command return an error";
            break;
        case CLIENT_SENDMAIL_END_DATA_TIMEOUT:
            errorMessage = "The End data command timed out";
            break;
        case CLIENT_SENDMAIL_QUIT_ERROR:
            errorMessage = "The QUIT command return an error";
            break;
        case SMTPSERVER_AUTHENTICATIONREQUIRED_ERROR:
            errorMessage = "Authentication required";
            break;
        case SMTPSERVER_AUTHENTICATIONTOOWEAK_ERROR:
            errorMessage = "Authentication mechanism is too weak";
            break;
        case SMTPSERVER_CREDENTIALSINVALID_ERROR:
            errorMessage = "Authentication credentials invalid";
            break;
        case SMTPSERVER_ENCRYPTIONREQUIREDFORAUTH_ERROR:
            errorMessage = "Encryption required for requested authentication mechanism";
            break;
        case SMTPSERVER_AUTHENTICATION_UNSUCCESSFUL_GMAIL_ERROR:
            errorMessage = "Token based authentication failed. See https://support.google.com/mail/thread/204884242/334-authentication-unsuccessful?hl=en";
            break;
        default:
            errorMessage = "No message correspond to this error code";
    }

    size_t errorMessageLength = errorMessage.length();
    mErrorMessage = new char[errorMessageLength + 1];
    std::strncpy(mErrorMessage, errorMessage.c_str(), errorMessageLength);
    mErrorMessage[errorMessageLength] = '\0';
}

ErrorResolver::~ErrorResolver() {
    delete[] mErrorMessage;
    mErrorMessage = nullptr;
}

// Copy constructor
ErrorResolver::ErrorResolver(const ErrorResolver& other)
    : mErrorCode(other.mErrorCode),
      mErrorMessage(new char[std::strlen(other.mErrorMessage) + 1]) {
    size_t errorMessageLength = std::strlen(other.mErrorMessage);
    std::strncpy(mErrorMessage, other.mErrorMessage, errorMessageLength);
    mErrorMessage[errorMessageLength] = '\0';
}

// Assignment operator
ErrorResolver& ErrorResolver::operator=(const ErrorResolver& other) {
    if (this != &other) {
        mErrorCode = other.mErrorCode;
        delete[] mErrorMessage;
        size_t errorMessageLength = std::strlen(other.mErrorMessage);
        mErrorMessage = new char[errorMessageLength + 1];
        std::strncpy(mErrorMessage, other.mErrorMessage, errorMessageLength);
        mErrorMessage[errorMessageLength] = '\0';
    }
    return *this;
}

// Move constructor
ErrorResolver::ErrorResolver(ErrorResolver&& other) noexcept
    : mErrorCode(other.mErrorCode),
      mErrorMessage(other.mErrorMessage) {
    other.mErrorCode = 0;
    // Release the data pointer from the source object so that the destructor
    // does not free the memory multiple times.
    other.mErrorMessage = nullptr;
}

// Move assignement operator
ErrorResolver& ErrorResolver::operator=(ErrorResolver&& other) noexcept {
    if (this != &other) {
        mErrorCode = other.mErrorCode;
        delete[] mErrorMessage;
        // Copy the data pointer and its length from the source object.
        mErrorMessage = other.mErrorMessage;
        // Release the data pointer from the source object so that
        // the destructor does not free the memory multiple times.
        other.mErrorCode = 0;
        other.mErrorMessage = nullptr;
    }
    return *this;
}

int ErrorResolver::getErrorCode() const {
    return mErrorCode;
}

const char *ErrorResolver::getErrorMessage() const {
    return mErrorMessage;
}
