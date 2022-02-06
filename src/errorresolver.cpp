#include "errorresolver.h"
#include "smtpclienterrors.h"
#include "socketerrors.h"
#include "sslerrors.h"

using namespace jed_utils;
using namespace std::literals::string_literals;

ErrorResolver::ErrorResolver(int pErrorCode)
    : mErrorCode(pErrorCode),
      mErrorMessage(""s)
{
    switch (mErrorCode) {
        case SOCKET_INIT_SESSION_CREATION_ERROR:
            mErrorMessage = "Unable to create the socket"s;
        break;
        case SOCKET_INIT_SESSION_CONNECT_ERROR:
            mErrorMessage = "Unable to connect to the socket"s;
        break;
        case SOCKET_INIT_SESSION_CONNECT_TIMEOUT:
            mErrorMessage = "The connection attempt has timed out"s;
        break;
        case SOCKET_INIT_SESSION_WINSOCKET_STARTUP_ERROR:
            mErrorMessage = "Unable to start WSA (Winsock)"s;
        break;
        case SOCKET_INIT_SESSION_WINSOCKET_GETADDRINFO_ERROR:
            mErrorMessage = "Unable to get address info (Winsock)"s;
        break;
        case SOCKET_INIT_SESSION_GETHOSTBYNAME_ERROR:
            mErrorMessage = "Unable to get host by name"s;
        break;
        case SOCKET_INIT_CLIENT_SEND_EHLO_ERROR:
            mErrorMessage = "Unable to send the EHLO command"s;
        break;
        case SOCKET_INIT_CLIENT_SEND_EHLO_TIMEOUT:
            mErrorMessage = "The EHLO command has timed out"s;
        break;
        case SOCKET_INIT_CLIENT_SEND_STARTTLS_ERROR:
            mErrorMessage = "Unable to send the STARTTLS command"s;
        break;
        case SOCKET_INIT_CLIENT_SEND_STARTTLS_TIMEOUT:
            mErrorMessage = "The STARTTLS command has timed out"s;
        break;
        case SSL_CLIENT_STARTTLS_INITSSLCTX_ERROR:
            mErrorMessage = "Unable to initialize the SSL Context"s;
        break;
        case SSL_CLIENT_STARTTLS_BIONEWSSLCONNECT_ERROR:
            mErrorMessage = "Unable to create the SSL BIO"s;
        break;
        case SSL_CLIENT_STARTTLS_WIN_CERTOPENSYSTEMSTORE_ERROR:
            mErrorMessage = "Unable to open the Windows Certificate System Store"s;
        break;
        case SSL_CLIENT_STARTTLS_CTX_SET_DEFAULT_VERIFY_PATHS_ERROR:
            mErrorMessage = "Unable to open the specifies that the default locations from which CA certificates are loaded"s;
        break;
        case SSL_CLIENT_STARTTLS_BIO_CONNECT_ERROR:
            mErrorMessage = "Unable to connect SSL BIO"s;
        break;
        case SSL_CLIENT_STARTTLS_BIO_HANDSHAKE_ERROR:
            mErrorMessage = "Unable to handshake with SSL BIO"s;
        break;
        case SSL_CLIENT_STARTTLS_GET_CERTIFICATE_ERROR:
            mErrorMessage = "Unable to get peer certificate"s;
        break;
        case SSL_CLIENT_STARTTLS_VERIFY_RESULT_ERROR:
            mErrorMessage = "Unable to verify the result of chain verification"s;
        break;
        case SSL_CLIENT_INITSECURECLIENT_ERROR:
            mErrorMessage = "Unable to EHLO the server via the secure channel"s;
        break;
        case SSL_CLIENT_INITSECURECLIENT_TIMEOUT:
            mErrorMessage = "The EHLO command via the secure channel timed out"s;
        break;
        case CLIENT_AUTHENTICATE_ERROR:
            mErrorMessage = "Unable to authenticate with the credentials provided"s;
        break;
        case CLIENT_AUTHENTICATE_TIMEOUT:
            mErrorMessage = "The authentication to the server has timed out"s;
        break;
        case CLIENT_AUTHENTICATE_NONEED:
            mErrorMessage = "The authentication is not needed on the server"s;
        break;
        case CLIENT_AUTHENTICATION_METHOD_NOTSUPPORTED:
            mErrorMessage = "The authentication method selected is not supported by the server"s;
        break;
        case CLIENT_SENDMAIL_MAILFROM_ERROR:
            mErrorMessage = "The MAIL FROM command return an error"s;
        break;
        case CLIENT_SENDMAIL_MAILFROM_TIMEOUT:
            mErrorMessage = "The MAIL FROM command timed out"s;
        break;
        case CLIENT_SENDMAIL_RCPTTO_ERROR:
            mErrorMessage = "The RCPT TO command return an error"s;
        break;
        case CLIENT_SENDMAIL_RCPTTO_TIMEOUT:
            mErrorMessage = "The RCPT TO command timed out"s;
        break;
        case CLIENT_SENDMAIL_DATA_ERROR:
            mErrorMessage = "The DATA command return an error"s;
        break;
        case CLIENT_SENDMAIL_DATA_TIMEOUT:
            mErrorMessage = "The DATA command timed out"s;
        break;
        case CLIENT_SENDMAIL_HEADERFROM_ERROR:
            mErrorMessage = "The From header command return an error"s;
        break;
        case CLIENT_SENDMAIL_HEADERTOANDCC_ERROR:
            mErrorMessage = "The To and CC header command return an error"s;
        break;
        case CLIENT_SENDMAIL_HEADERSUBJECT_ERROR:
            mErrorMessage = "The Subject header command return an error"s;
        break;
        case CLIENT_SENDMAIL_HEADERCONTENTTYPE_ERROR:
            mErrorMessage = "The Content type header command return an error"s;
        break;
        case CLIENT_SENDMAIL_BODYPART_ERROR:
            mErrorMessage = "The Body part return an error"s;
        break;
        case CLIENT_SENDMAIL_BODY_ERROR:
            mErrorMessage = "The Body command return an error"s;
        break;
        case CLIENT_SENDMAIL_END_DATA_ERROR:
            mErrorMessage = "The End data command return an error"s;
        break;
        case CLIENT_SENDMAIL_END_DATA_TIMEOUT:
            mErrorMessage = "The End data command timed out"s;
        break;
        case CLIENT_SENDMAIL_QUIT_ERROR:
            mErrorMessage = "The QUIT command return an error"s;
        break;
        case SMTPSERVER_AUTHENTICATIONREQUIRED_ERROR:
            mErrorMessage = "Authentication required"s;
        break; 
        case SMTPSERVER_AUTHENTICATIONTOOWEAK_ERROR:
            mErrorMessage = "Authentication mechanism is too weak"s;
        break;
        case SMTPSERVER_CREDENTIALSINVALID_ERROR:
            mErrorMessage = "Authentication credentials invalid"s;
        break; 
        case SMTPSERVER_ENCRYPTIONREQUIREDFORAUTH_ERROR:
            mErrorMessage = "Encryption required for requested authentication mechanism"s;
        break;   
        default:
            mErrorMessage = "No message correspond to this error code"s;
    }
}

int ErrorResolver::getErrorCode() const
{
    return mErrorCode;
}

const std::string &ErrorResolver::getErrorMessage() const
{
    return mErrorMessage;
}
