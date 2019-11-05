#include "../../src/sslsmtpclient.h"
#include <gtest/gtest.h>

using namespace jed_utils;
using namespace std;

class FakeSSLSMTPClient : public ::testing::Test, public SSLSmtpClient
{
public:
    FakeSSLSMTPClient()
        : SSLSmtpClient("127.0.0.1", 587)
    {
    }

    ~FakeSSLSMTPClient()
    {
    }

    int __extractReturnCode(const char *output) const
    {
        return extractReturnCode(output);
    }

	ServerAuthOptions *__extractAuthenticationOptions(const char *pEhloOutput) const
	{
		return SSLSmtpClient::extractAuthenticationOptions(pEhloOutput);
	}
};

TEST(SSLSmtpClient_Constructor, NullServerName_ThrowInvalidArgument)
{
	try
	{
		SSLSmtpClient client(nullptr, 587);
		FAIL();
	}
	catch(invalid_argument &err) 
	{
        ASSERT_STREQ("Server name cannot be null or empty", err.what());
	}
}

TEST(SSLSmtpClient_Constructor, EmptyServerName_ThrowInvalidArgument)
{
	try
	{
		SSLSmtpClient client("", 587);
		FAIL();
	}
	catch(invalid_argument &err) 
	{
        ASSERT_STREQ("Server name cannot be null or empty", err.what());
	}
}

TEST(SSLSmtpClient_Constructor, OnlySpacesServerName_ThrowInvalidArgument)
{
	try
	{
		SSLSmtpClient client("   ", 587);
		FAIL();
	}
	catch(invalid_argument &err) 
	{
        ASSERT_STREQ("Server name cannot be null or empty", err.what());
	}
}

TEST(SSLSmtpClient_Constructor, ValidArguments_ReturnSuccess)
{
	SSLSmtpClient client("test", 587);	
    ASSERT_STREQ("test", client.getServerName());
    ASSERT_EQ(587, client.getServerPort());
}

TEST(SSLSmtpClient_CopyConstructor, SSLSmtpClientCopyConstructorValid)
{
	SSLSmtpClient* client1 = new SSLSmtpClient("server1", 123);
    client1->setCredentials(Credential("user1", "pass1"));
    client1->setCommandTimeout(8);
	SSLSmtpClient client2(*client1);
	delete client1;
	ASSERT_STREQ("server1", client2.getServerName());
	ASSERT_EQ(123, client2.getServerPort());
	ASSERT_EQ(8, client2.getCommandTimeout());
	ASSERT_STREQ("user1", client2.getCredentials()->getUsername());
	ASSERT_STREQ("pass1", client2.getCredentials()->getPassword());
}

TEST(SSLSmtpClient_CopyAssignment, SSLSmtpClientCopyAssignmentValid)
{
	SSLSmtpClient* client1 = new SSLSmtpClient("test", 123);
    client1->setCredentials(Credential("user1", "pass1"));
    client1->setCommandTimeout(8);
	SSLSmtpClient client2("aaa", 456);
	client2 = *client1;
	delete client1;
	ASSERT_STREQ("test", client2.getServerName());
	ASSERT_EQ(123, client2.getServerPort());
    ASSERT_EQ(8, client2.getCommandTimeout());
	ASSERT_STREQ("user1", client2.getCredentials()->getUsername());
	ASSERT_STREQ("pass1", client2.getCredentials()->getPassword());
}

TEST(SSLSmtpClient_MoveConstructor, SSLSmtpClientMoveConstructorValid)
{
	SSLSmtpClient client1("test", 123);
    client1.setCredentials(Credential("user1", "pass1"));
    client1.setCommandTimeout(8);
	SSLSmtpClient client2(move(client1));
	ASSERT_STREQ("test", client2.getServerName());
	ASSERT_EQ(123, client2.getServerPort());
    ASSERT_EQ(8, client2.getCommandTimeout());
	ASSERT_STREQ("user1", client2.getCredentials()->getUsername());
	ASSERT_STREQ("pass1", client2.getCredentials()->getPassword());

    ASSERT_EQ(nullptr, client1.getServerName());
	ASSERT_EQ(0, client1.getServerPort());
    ASSERT_EQ(0, client1.getCommandTimeout());
	ASSERT_EQ(nullptr, client1.getCredentials());
}

TEST(SSLSmtpClient_MoveAssignment, SSLSmtpClientMoveAssignmentValid)
{
	SSLSmtpClient client1("test", 123);
    client1.setCredentials(Credential("user1", "pass1"));
    client1.setCommandTimeout(8);
	SSLSmtpClient client2("aaa", 456);
	client2 = move(client1);
	ASSERT_STREQ("test", client2.getServerName());
	ASSERT_EQ(123, client2.getServerPort());
    ASSERT_EQ(8, client2.getCommandTimeout());
	ASSERT_STREQ("user1", client2.getCredentials()->getUsername());
	ASSERT_STREQ("pass1", client2.getCredentials()->getPassword());

    ASSERT_EQ(nullptr, client1.getServerName());
	ASSERT_EQ(0, client1.getServerPort());
    ASSERT_EQ(0, client1.getCommandTimeout());
	ASSERT_EQ(nullptr, client1.getCredentials());
}

TEST(SSLSmtpClient_setServerName, ValidName_ReturnSuccess)
{
	SSLSmtpClient client("test", 587);
    client.setServerName("myServer");
    ASSERT_STREQ("myServer", client.getServerName());
}

TEST(SSLSmtpClient_setServerName, NullServerName_ThrowInvalidArgument)
{
	SSLSmtpClient client("test", 587);
	try
	{
        client.setServerName(nullptr);
		FAIL();
	}
	catch(invalid_argument &err) 
	{
        ASSERT_STREQ("Server name cannot be null or empty", err.what());
	}
}

TEST(SSLSmtpClient_setServerName, EmptyServerName_ThrowInvalidArgument)
{
	SSLSmtpClient client("test", 587);
	try
	{
        client.setServerName("");
		FAIL();
	}
	catch(invalid_argument &err) 
	{
        ASSERT_STREQ("Server name cannot be null or empty", err.what());
	}
}

TEST(SSLSmtpClient_setServerName, OnlySpacesServerName_ThrowInvalidArgument)
{
	SSLSmtpClient client("test", 587);
	try
	{
        client.setServerName("    ");
		FAIL();
	}
	catch(invalid_argument &err) 
	{
        ASSERT_STREQ("Server name cannot be null or empty", err.what());
	}
}

TEST(SSLSmtpClient_getServerName, ReturnValidServerName)
{
	SSLSmtpClient client("test", 587);
    ASSERT_STREQ("test", client.getServerName());
}

TEST(SSLSmtpClient_setServerPort, WithPort465ReturnSuccess)
{
	SSLSmtpClient client("test", 587);
    client.setServerPort(465);
    ASSERT_EQ(465, client.getServerPort());
}

TEST(SSLSmtpClient_getServerPort, ReturnValidServerPort)
{
	SSLSmtpClient client("test", 587);
    ASSERT_EQ(587, client.getServerPort());
}

TEST_F(FakeSSLSMTPClient, ValidWelcomeCode220_Return220)
{
    ASSERT_EQ(220, __extractReturnCode("220 smtp.gmail.com ESMTP z13sm224346qkj.34 - gsmtp"));
}

TEST_F(FakeSSLSMTPClient, ValidClientCode250_Return250)
{
    ASSERT_EQ(250, __extractReturnCode("250-smtp.gmail.com at your service, [24.48.180.30]"));
}

TEST_F(FakeSSLSMTPClient, ValidClientCode250WithoutDash_Return250)
{
    ASSERT_EQ(250, __extractReturnCode("250 smtp.gmail.com at your service, [24.48.180.30]"));
}

TEST_F(FakeSSLSMTPClient, ValidClientCode250NoSpace_Return250)
{
    ASSERT_EQ(250, __extractReturnCode("250smtp.gmail.com at your service, [24.48.180.30]"));
}

TEST_F(FakeSSLSMTPClient, EmptyOutput_ReturnMinus1)
{
    ASSERT_EQ(-1, __extractReturnCode(""));
}

TEST_F(FakeSSLSMTPClient, TwoSpaces_ReturnMinus1)
{
    ASSERT_EQ(-1, __extractReturnCode("  "));
}

TEST_F(FakeSSLSMTPClient, ThreeSpaces_ReturnMinus1)
{
    ASSERT_EQ(-1, __extractReturnCode("   "));
}

TEST_F(FakeSSLSMTPClient, NotNumeric_ReturnMinus1)
{
    ASSERT_EQ(-1, __extractReturnCode("ABC"));
}

TEST_F(FakeSSLSMTPClient, NullPtr_ReturnMinus1)
{
    ASSERT_EQ(-1, __extractReturnCode(nullptr));
}

TEST(SSLSmtpClient_getCommandTimeout, DefaultTimeOut_Return3)
{
    SSLSmtpClient client("fdfdsfs", 587);
    ASSERT_EQ(3, client.getCommandTimeout());
}

TEST(SSLSmtpClient_getCommandTimeout, SetTimeOutWith2_Return2)
{
    SSLSmtpClient client("fdfdsfs", 587);
    client.setCommandTimeout(2);
    ASSERT_EQ(2, client.getCommandTimeout());
}

TEST_F(FakeSSLSMTPClient, extractAuthenticationOptionsWithNullEhlo_ReturnNullptr)
{
	ASSERT_EQ(nullptr, __extractAuthenticationOptions(nullptr));
}

TEST_F(FakeSSLSMTPClient, extractAuthenticationOptionsWithEmptyEhlo_ReturnNullptr)
{
	ASSERT_EQ(nullptr, __extractAuthenticationOptions(""));
}

TEST_F(FakeSSLSMTPClient, extractAuthenticationOptionsWithOnlySpacesEhlo_ReturnNullptr)
{
	ASSERT_EQ(nullptr, __extractAuthenticationOptions("    "));
}

TEST_F(FakeSSLSMTPClient, extractAuthenticationOptionsWithNoAuthOptionsEhlo_ReturnNullptr)
{
	ASSERT_EQ(nullptr, __extractAuthenticationOptions("250-SIZE 35882577\r\n250-8BITMIME\r\n"));
}

TEST_F(FakeSSLSMTPClient, extractAuthenticationOptionsWithAuthOnlyPlainEhlo_ReturnNullptr)
{
	ServerAuthOptions *options = __extractAuthenticationOptions("250-AUTH PLAIN\r\n");
	ASSERT_NE(nullptr, options);
	ASSERT_TRUE(options->Plain);
	ASSERT_FALSE(options->Login);
	ASSERT_FALSE(options->XOAuth2);
    ASSERT_FALSE(options->Plain_ClientToken);
    ASSERT_FALSE(options->OAuthBearer);
    ASSERT_FALSE(options->XOAuth);
}

TEST_F(FakeSSLSMTPClient, extractAuthenticationOptionsWithAuthPlainLoginEhlo_ReturnNullptr)
{
	ServerAuthOptions *options = __extractAuthenticationOptions("250-AUTH LOGIN PLAIN\r\n");
	ASSERT_NE(nullptr, options);
	ASSERT_TRUE(options->Plain);
	ASSERT_TRUE(options->Login);
	ASSERT_FALSE(options->XOAuth2);
    ASSERT_FALSE(options->Plain_ClientToken);
    ASSERT_FALSE(options->OAuthBearer);
    ASSERT_FALSE(options->XOAuth);
}


TEST_F(FakeSSLSMTPClient, extractAuthenticationOptionsWithAuthMultipleEhlo_ReturnNullptr)
{
	ServerAuthOptions *options = __extractAuthenticationOptions("250-AUTH LOGIN PLAIN XOAUTH2 PLAIN-CLIENTTOKEN OAUTHBEARER XOAUTH\r\n");
	ASSERT_NE(nullptr, options);
	ASSERT_TRUE(options->Plain);
	ASSERT_TRUE(options->Login);
	ASSERT_TRUE(options->XOAuth2);
    ASSERT_TRUE(options->Plain_ClientToken);
    ASSERT_TRUE(options->OAuthBearer);
    ASSERT_TRUE(options->XOAuth);
}