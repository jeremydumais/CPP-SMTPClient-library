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