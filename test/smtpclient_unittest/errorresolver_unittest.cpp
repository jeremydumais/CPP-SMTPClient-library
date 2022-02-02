#include <gtest/gtest.h>
#include "../../src/errorresolver.h"
#include "../../src/smtpclienterrors.h"
#include "../../src/socketerrors.h"
#include "../../src/sslerrors.h"

using namespace jed_utils;
using namespace std::literals::string_literals;

TEST(ErrorResolver_Constructor, NegativeErrorCode_ReturnValid)
{
    ErrorResolver errorResolver(-1);
}

TEST(ErrorResolver_Constructor, PositiveErrorCode_ReturnValid)
{
    ErrorResolver errorResolver(1);
}

TEST(ErrorResolver_getErrorCode, WithOneOnConstruction_ReturnOne)
{
    ErrorResolver errorResolver(1);
    ASSERT_EQ(1, errorResolver.getErrorCode());
}

TEST(ErrorResolver_getErrorMessage, WithNonExistantCode_ReturnNoMessage)
{
    ErrorResolver errorResolver(0);
    ASSERT_EQ("No message correspond to this error code"s, errorResolver.getErrorMessage());
}

TEST(ErrorResolver_getErrorMessage, WithSOCKET_INIT_SESSION_CREATION_ERROR_ReturnValidMessage)
{
    ErrorResolver errorResolver(SOCKET_INIT_SESSION_CREATION_ERROR);
    ASSERT_EQ("Unable to create the socket"s, errorResolver.getErrorMessage());
}

TEST(ErrorResolver_getErrorMessage, WithSOCKET_INIT_SESSION_CONNECT_ERROR_ReturnValidMessage)
{
    ErrorResolver errorResolver(SOCKET_INIT_SESSION_CONNECT_ERROR);
    ASSERT_EQ("Unable to connect to the socket"s, errorResolver.getErrorMessage());
}

TEST(ErrorResolver_getErrorMessage, WithSOCKET_INIT_SESSION_CONNECT_TIMEOUT_ReturnValidMessage)
{
    ErrorResolver errorResolver(SOCKET_INIT_SESSION_CONNECT_TIMEOUT);
    ASSERT_EQ("The connection attempt has timed out"s, errorResolver.getErrorMessage());
}

TEST(ErrorResolver_getErrorMessage, WithSOCKET_INIT_SESSION_WINSOCKET_STARTUP_ERROR_ReturnValidMessage)
{
    ErrorResolver errorResolver(SOCKET_INIT_SESSION_WINSOCKET_STARTUP_ERROR);
    ASSERT_EQ("Unable to start WSA (Winsock)"s, errorResolver.getErrorMessage());
}

TEST(ErrorResolver_getErrorMessage, WithSOCKET_INIT_SESSION_WINSOCKET_GETADDRINFO_ERROR_ReturnValidMessage)
{
    ErrorResolver errorResolver(SOCKET_INIT_SESSION_WINSOCKET_GETADDRINFO_ERROR);
    ASSERT_EQ("Unable to get address info (Winsock)"s, errorResolver.getErrorMessage());
}

TEST(ErrorResolver_getErrorMessage, WithSOCKET_INIT_SESSION_GETHOSTBYNAME_ERROR_ReturnValidMessage)
{
    ErrorResolver errorResolver(SOCKET_INIT_SESSION_GETHOSTBYNAME_ERROR);
    ASSERT_EQ("Unable to get host by name"s, errorResolver.getErrorMessage());
}

TEST(ErrorResolver_getErrorMessage, WithSOCKET_INIT_CLIENT_SEND_EHLO_ERROR_ReturnValidMessage)
{
    ErrorResolver errorResolver(SOCKET_INIT_CLIENT_SEND_EHLO_ERROR);
    ASSERT_EQ("Unable to send the EHLO command"s, errorResolver.getErrorMessage());
}

TEST(ErrorResolver_getErrorMessage, WithSOCKET_INIT_CLIENT_SEND_EHLO_TIMEOUT_ReturnValidMessage)
{
    ErrorResolver errorResolver(SOCKET_INIT_CLIENT_SEND_EHLO_TIMEOUT);
    ASSERT_EQ("The EHLO command has timed out"s, errorResolver.getErrorMessage());
}

TEST(ErrorResolver_getErrorMessage, WithSOCKET_INIT_CLIENT_SEND_STARTTLS_ERROR_ReturnValidMessage)
{
    ErrorResolver errorResolver(SOCKET_INIT_CLIENT_SEND_STARTTLS_ERROR);
    ASSERT_EQ("Unable to send the STARTTLS command"s, errorResolver.getErrorMessage());
}

TEST(ErrorResolver_getErrorMessage, WithSOCKET_INIT_CLIENT_SEND_STARTTLS_TIMEOUT_ReturnValidMessage)
{
    ErrorResolver errorResolver(SOCKET_INIT_CLIENT_SEND_STARTTLS_TIMEOUT);
    ASSERT_EQ("The STARTTLS command has timed out"s, errorResolver.getErrorMessage());
}

TEST(ErrorResolver_getErrorMessage, WithSSL_CLIENT_STARTTLS_INITSSLCTX_ERROR_ReturnValidMessage)
{
    ErrorResolver errorResolver(SSL_CLIENT_STARTTLS_INITSSLCTX_ERROR);
    ASSERT_EQ("Unable to initialize the SSL Context"s, errorResolver.getErrorMessage());
}

TEST(ErrorResolver_getErrorMessage, WithSSL_CLIENT_STARTTLS_BIONEWSSLCONNECT_ERROR_ReturnValidMessage)
{
    ErrorResolver errorResolver(SSL_CLIENT_STARTTLS_BIONEWSSLCONNECT_ERROR);
    ASSERT_EQ("Unable to create the SSL BIO"s, errorResolver.getErrorMessage());
}

TEST(ErrorResolver_getErrorMessage, WithSSL_CLIENT_STARTTLS_WIN_CERTOPENSYSTEMSTORE_ERROR_ReturnValidMessage)
{
    ErrorResolver errorResolver(SSL_CLIENT_STARTTLS_WIN_CERTOPENSYSTEMSTORE_ERROR);
    ASSERT_EQ("Unable to open the Windows Certificate System Store"s, errorResolver.getErrorMessage());
}

TEST(ErrorResolver_getErrorMessage, WithSSL_CLIENT_STARTTLS_CTX_SET_DEFAULT_VERIFY_PATHS_ERROR_ReturnValidMessage)
{
    ErrorResolver errorResolver(SSL_CLIENT_STARTTLS_CTX_SET_DEFAULT_VERIFY_PATHS_ERROR);
    ASSERT_EQ("Unable to open the specifies that the default locations from which CA certificates are loaded"s, errorResolver.getErrorMessage());
}

TEST(ErrorResolver_getErrorMessage, WithSSL_CLIENT_STARTTLS_BIO_CONNECT_ERROR_ReturnValidMessage)
{
    ErrorResolver errorResolver(SSL_CLIENT_STARTTLS_BIO_CONNECT_ERROR);
    ASSERT_EQ("Unable to connect SSL BIO"s, errorResolver.getErrorMessage());
}

TEST(ErrorResolver_getErrorMessage, WithSSL_CLIENT_STARTTLS_BIO_HANDSHAKE_ERROR_ReturnValidMessage)
{
    ErrorResolver errorResolver(SSL_CLIENT_STARTTLS_BIO_HANDSHAKE_ERROR);
    ASSERT_EQ("Unable to handshake with SSL BIO"s, errorResolver.getErrorMessage());
}

TEST(ErrorResolver_getErrorMessage, WithSSL_CLIENT_STARTTLS_GET_CERTIFICATE_ERROR_ReturnValidMessage)
{
    ErrorResolver errorResolver(SSL_CLIENT_STARTTLS_GET_CERTIFICATE_ERROR);
    ASSERT_EQ("Unable to get peer certificate"s, errorResolver.getErrorMessage());
}

TEST(ErrorResolver_getErrorMessage, WithSSL_CLIENT_STARTTLS_VERIFY_RESULT_ERROR_ReturnValidMessage)
{
    ErrorResolver errorResolver(SSL_CLIENT_STARTTLS_VERIFY_RESULT_ERROR);
    ASSERT_EQ("Unable to verify the result of chain verification"s, errorResolver.getErrorMessage());
}

TEST(ErrorResolver_getErrorMessage, WithSSL_CLIENT_INITSECURECLIENT_ERROR_ReturnValidMessage)
{
    ErrorResolver errorResolver(SSL_CLIENT_INITSECURECLIENT_ERROR);
    ASSERT_EQ("Unable to EHLO the server via the secure channel"s, errorResolver.getErrorMessage());
}

TEST(ErrorResolver_getErrorMessage, WithSSL_CLIENT_INITSECURECLIENT_TIMEOUT_ReturnValidMessage)
{
    ErrorResolver errorResolver(SSL_CLIENT_INITSECURECLIENT_TIMEOUT);
    ASSERT_EQ("The EHLO command via the secure channel timed out"s, errorResolver.getErrorMessage());
}

TEST(ErrorResolver_getErrorMessage, WithCLIENT_AUTHENTICATE_ERROR_ReturnValidMessage)
{
    ErrorResolver errorResolver(CLIENT_AUTHENTICATE_ERROR);
    ASSERT_EQ("Unable to authenticate with the credentials provided"s, errorResolver.getErrorMessage());
}

TEST(ErrorResolver_getErrorMessage, WithCLIENT_AUTHENTICATE_TIMEOUT_ReturnValidMessage)
{
    ErrorResolver errorResolver(CLIENT_AUTHENTICATE_TIMEOUT);
    ASSERT_EQ("The authentication to the server has timed out"s, errorResolver.getErrorMessage());
}

TEST(ErrorResolver_getErrorMessage, WithCLIENT_AUTHENTICATE_NONEED_ReturnValidMessage)
{
    ErrorResolver errorResolver(CLIENT_AUTHENTICATE_NONEED);
    ASSERT_EQ("The authentication is not needed on the server"s, errorResolver.getErrorMessage());
}

TEST(ErrorResolver_getErrorMessage, WithCLIENT_AUTHENTICATION_METHOD_NOTSUPPORTED_ReturnValidMessage)
{
    ErrorResolver errorResolver(CLIENT_AUTHENTICATION_METHOD_NOTSUPPORTED);
    ASSERT_EQ("The authentication method selected is not supported by the server"s, errorResolver.getErrorMessage());
}

TEST(ErrorResolver_getErrorMessage, WithCLIENT_SENDMAIL_MAILFROM_ERROR_ReturnValidMessage)
{
    ErrorResolver errorResolver(CLIENT_SENDMAIL_MAILFROM_ERROR);
    ASSERT_EQ("The MAIL FROM command return an error"s, errorResolver.getErrorMessage());
}

TEST(ErrorResolver_getErrorMessage, WithCLIENT_SENDMAIL_MAILFROM_TIMEOUT_ReturnValidMessage)
{
    ErrorResolver errorResolver(CLIENT_SENDMAIL_MAILFROM_TIMEOUT);
    ASSERT_EQ("The MAIL FROM command timed out"s, errorResolver.getErrorMessage());
}

TEST(ErrorResolver_getErrorMessage, WithCLIENT_SENDMAIL_RCPTTO_ERROR_ReturnValidMessage)
{
    ErrorResolver errorResolver(CLIENT_SENDMAIL_RCPTTO_ERROR);
    ASSERT_EQ("The RCPT TO command return an error"s, errorResolver.getErrorMessage());
}

TEST(ErrorResolver_getErrorMessage, WithCLIENT_SENDMAIL_RCPTTO_TIMEOUT_ReturnValidMessage)
{
    ErrorResolver errorResolver(CLIENT_SENDMAIL_RCPTTO_TIMEOUT);
    ASSERT_EQ("The RCPT TO command timed out"s, errorResolver.getErrorMessage());
}

TEST(ErrorResolver_getErrorMessage, WithCLIENT_SENDMAIL_DATA_ERROR_ReturnValidMessage)
{
    ErrorResolver errorResolver(CLIENT_SENDMAIL_DATA_ERROR);
    ASSERT_EQ("The DATA command return an error"s, errorResolver.getErrorMessage());
}

TEST(ErrorResolver_getErrorMessage, WithCLIENT_SENDMAIL_DATA_TIMEOUT_ReturnValidMessage)
{
    ErrorResolver errorResolver(CLIENT_SENDMAIL_DATA_TIMEOUT);
    ASSERT_EQ("The DATA command timed out"s, errorResolver.getErrorMessage());
}

TEST(ErrorResolver_getErrorMessage, WithCLIENT_SENDMAIL_HEADERFROM_ERROR_ReturnValidMessage)
{
    ErrorResolver errorResolver(CLIENT_SENDMAIL_HEADERFROM_ERROR);
    ASSERT_EQ("The From header command return an error"s, errorResolver.getErrorMessage());
}
