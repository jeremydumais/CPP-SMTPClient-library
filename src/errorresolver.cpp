#include "errorresolver.h"
#include "smtpclienterrors.h"
#include "socketerrors.h"
#include "sslerrors.h"
#include <cstring>

using namespace jed_utils;
using namespace std::literals::string_literals;

ErrorResolver::ErrorResolver(int pErrorCode)
    : mErrorCode(pErrorCode)
{
    std::string errorMessage = "";
    switch (mErrorCode) {
        case SOCKET_INIT_SESSION_CREATION_ERROR:
            errorMessage = "Unable to create the socket"s;
        break;
        case SOCKET_INIT_SESSION_CONNECT_ERROR:
            errorMessage = "Unable to connect to the socket"s;
        break;
        case SOCKET_INIT_SESSION_CONNECT_TIMEOUT:
            errorMessage = "The connection attempt has timed out"s;
        break;
        case SOCKET_INIT_SESSION_WINSOCKET_STARTUP_ERROR:
            errorMessage = "Unable to start WSA (Winsock)"s;
        break;
        case SOCKET_INIT_SESSION_WINSOCKET_GETADDRINFO_ERROR:
            errorMessage = "Unable to get address info (Winsock)"s;
        break;
        case SOCKET_INIT_SESSION_GETHOSTBYNAME_ERROR:
            errorMessage = "Unable to get host by name"s;
        break;
        case SOCKET_INIT_CLIENT_SEND_EHLO_ERROR:
            errorMessage = "Unable to send the EHLO command"s;
        break;
        case SOCKET_INIT_CLIENT_SEND_EHLO_TIMEOUT:
            errorMessage = "The EHLO command has timed out"s;
        break;
        case SOCKET_INIT_CLIENT_SEND_STARTTLS_ERROR:
            errorMessage = "Unable to send the STARTTLS command"s;
        break;
        case SOCKET_INIT_CLIENT_SEND_STARTTLS_TIMEOUT:
            errorMessage = "The STARTTLS command has timed out"s;
        break;
        case SSL_CLIENT_STARTTLS_INITSSLCTX_ERROR:
            errorMessage = "Unable to initialize the SSL Context"s;
        break;
        case SSL_CLIENT_STARTTLS_BIONEWSSLCONNECT_ERROR:
            errorMessage = "Unable to create the SSL BIO"s;
        break;
        case SSL_CLIENT_STARTTLS_WIN_CERTOPENSYSTEMSTORE_ERROR:
            errorMessage = "Unable to open the Windows Certificate System Store"s;
        break;
        case SSL_CLIENT_STARTTLS_CTX_SET_DEFAULT_VERIFY_PATHS_ERROR:
            errorMessage = "Unable to open the specifies that the default locations from which CA certificates are loaded"s;
        break;
        case SSL_CLIENT_STARTTLS_BIO_CONNECT_ERROR:
            errorMessage = "Unable to connect SSL BIO"s;
        break;
        case SSL_CLIENT_STARTTLS_BIO_HANDSHAKE_ERROR:
            errorMessage = "Unable to handshake with SSL BIO"s;
        break;
        case SSL_CLIENT_STARTTLS_GET_CERTIFICATE_ERROR:
            errorMessage = "Unable to get peer certificate"s;
        break;
        case SSL_CLIENT_STARTTLS_VERIFY_RESULT_ERROR:
            errorMessage = "Unable to verify the result of chain verification"s;
        break;
        case SSL_CLIENT_INITSECURECLIENT_ERROR:
            errorMessage = "Unable to EHLO the server via the secure channel"s;
        break;
        case SSL_CLIENT_INITSECURECLIENT_TIMEOUT:
            errorMessage = "The EHLO command via the secure channel timed out"s;
        break;
        case CLIENT_AUTHENTICATE_ERROR:
            errorMessage = "Unable to authenticate with the credentials provided"s;
        break;
        case CLIENT_AUTHENTICATE_TIMEOUT:
            errorMessage = "The authentication to the server has timed out"s;
        break;
        case CLIENT_AUTHENTICATE_NONEED:
            errorMessage = "The authentication is not needed on the server"s;
        break;
        case CLIENT_AUTHENTICATION_METHOD_NOTSUPPORTED:
            errorMessage = "The authentication method selected is not supported by the server"s;
        break;
        case CLIENT_SENDMAIL_MAILFROM_ERROR:
            errorMessage = "The MAIL FROM command return an error"s;
        break;
        case CLIENT_SENDMAIL_MAILFROM_TIMEOUT:
            errorMessage = "The MAIL FROM command timed out"s;
        break;
        case CLIENT_SENDMAIL_RCPTTO_ERROR:
            errorMessage = "The RCPT TO command return an error"s;
        break;
        case CLIENT_SENDMAIL_RCPTTO_TIMEOUT:
            errorMessage = "The RCPT TO command timed out"s;
        break;
        case CLIENT_SENDMAIL_DATA_ERROR:
            errorMessage = "The DATA command return an error"s;
        break;
        case CLIENT_SENDMAIL_DATA_TIMEOUT:
            errorMessage = "The DATA command timed out"s;
        break;
        case CLIENT_SENDMAIL_HEADERFROM_ERROR:
            errorMessage = "The From header command return an error"s;
        break;
        case CLIENT_SENDMAIL_HEADERTOANDCC_ERROR:
            errorMessage = "The To and CC header command return an error"s;
        break;
        case CLIENT_SENDMAIL_HEADERSUBJECT_ERROR:
            errorMessage = "The Subject header command return an error"s;
        break;
        case CLIENT_SENDMAIL_HEADERCONTENTTYPE_ERROR:
            errorMessage = "The Content type header command return an error"s;
        break;
        case CLIENT_SENDMAIL_BODYPART_ERROR:
            errorMessage = "The Body part return an error"s;
        break;
        case CLIENT_SENDMAIL_BODY_ERROR:
            errorMessage = "The Body command return an error"s;
        break;
        case CLIENT_SENDMAIL_END_DATA_ERROR:
            errorMessage = "The End data command return an error"s;
        break;
        case CLIENT_SENDMAIL_END_DATA_TIMEOUT:
            errorMessage = "The End data command timed out"s;
        break;
        case CLIENT_SENDMAIL_QUIT_ERROR:
            errorMessage = "The QUIT command return an error"s;
        break;
        case SMTPSERVER_AUTHENTICATIONREQUIRED_ERROR:
            errorMessage = "Authentication required"s;
        break;
        case SMTPSERVER_AUTHENTICATIONTOOWEAK_ERROR:
            errorMessage = "Authentication mechanism is too weak"s;
        break;
        case SMTPSERVER_CREDENTIALSINVALID_ERROR:
            errorMessage = "Authentication credentials invalid"s;
        break;
        case SMTPSERVER_ENCRYPTIONREQUIREDFORAUTH_ERROR:
            errorMessage = "Encryption required for requested authentication mechanism"s;
        break;
        default:
            errorMessage = "No message correspond to this error code"s;
    }

	mErrorMessage = new char[errorMessage.length() + 1];
	strcpy(mErrorMessage, errorMessage.c_str());
}

ErrorResolver::~ErrorResolver()
{
    delete []mErrorMessage;
    mErrorMessage = nullptr;
}

//Copy constructor
ErrorResolver::ErrorResolver(const ErrorResolver& other)
	: mErrorCode(other.mErrorCode),
      mErrorMessage(new char[strlen(other.mErrorMessage) + 1])
{
	strcpy(mErrorMessage, other.mErrorMessage);
}

//Assignment operator
ErrorResolver& ErrorResolver::operator=(const ErrorResolver& other)
{
	if (this != &other)
	{
        mErrorCode = other.mErrorCode;
		delete[] mErrorMessage;
		//mErrorMessage
		mErrorMessage = new char[strlen(other.mErrorMessage) + 1];
		strcpy(mErrorMessage, other.mErrorMessage);
	}
	return *this;
}

//Move constructor
ErrorResolver::ErrorResolver(ErrorResolver&& other) noexcept
	: mErrorCode(other.mErrorCode),
      mErrorMessage(other.mErrorMessage)
{
    other.mErrorCode = 0;
	// Release the data pointer from the source object so that the destructor
	// does not free the memory multiple times.
	other.mErrorMessage = nullptr;
}

//Move assignement operator
ErrorResolver& ErrorResolver::operator=(ErrorResolver&& other) noexcept
{
	if (this != &other)
	{
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

int ErrorResolver::getErrorCode() const
{
    return mErrorCode;
}

const char *ErrorResolver::getErrorMessage() const
{
    return mErrorMessage;
}
