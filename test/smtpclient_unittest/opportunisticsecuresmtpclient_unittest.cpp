#include "../../src/sslsmtpclient.h"
#include <gtest/gtest.h>

using namespace jed_utils;
using namespace std;

class FakeSSLSMTPClient : public ::testing::Test, public OpportunisticSecureSMTPClient
{
public:
    FakeSSLSMTPClient()
        : OpportunisticSecureSMTPClient("127.0.0.1", 587)
    {
    }
};

TEST(SSLSmtpClient_Constructor, NullServerName_ThrowInvalidArgument)
{
	try
	{
		OpportunisticSecureSMTPClient client(nullptr, 587);
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
		OpportunisticSecureSMTPClient client("", 587);
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
		OpportunisticSecureSMTPClient client("   ", 587);
		FAIL();
	}
	catch(invalid_argument &err) 
	{
        ASSERT_STREQ("Server name cannot be null or empty", err.what());
	}
}

TEST(SSLSmtpClient_Constructor, ValidArguments_ReturnSuccess)
{
	OpportunisticSecureSMTPClient client("test", 587);	
    ASSERT_STREQ("test", client.getServerName());
    ASSERT_EQ(587, client.getServerPort());
}

TEST(SSLSmtpClient_CopyConstructor, SSLSmtpClientCopyConstructorValid)
{
	OpportunisticSecureSMTPClient* client1 = new OpportunisticSecureSMTPClient("server1", 123);
    client1->setCredentials(Credential("user1", "pass1"));
    client1->setCommandTimeout(8);
	OpportunisticSecureSMTPClient client2(*client1);
	delete client1;
	ASSERT_STREQ("server1", client2.getServerName());
	ASSERT_EQ(123, client2.getServerPort());
	ASSERT_EQ(8, client2.getCommandTimeout());
	ASSERT_STREQ("user1", client2.getCredentials()->getUsername());
	ASSERT_STREQ("pass1", client2.getCredentials()->getPassword());
}

TEST(SSLSmtpClient_CopyAssignment, SSLSmtpClientCopyAssignmentValid)
{
	OpportunisticSecureSMTPClient* client1 = new OpportunisticSecureSMTPClient("test", 123);
    client1->setCredentials(Credential("user1", "pass1"));
    client1->setCommandTimeout(8);
	OpportunisticSecureSMTPClient client2("aaa", 456);
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
	OpportunisticSecureSMTPClient client1("test", 123);
    client1.setCredentials(Credential("user1", "pass1"));
    client1.setCommandTimeout(8);
	OpportunisticSecureSMTPClient client2(move(client1));
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
	OpportunisticSecureSMTPClient client1("test", 123);
    client1.setCredentials(Credential("user1", "pass1"));
    client1.setCommandTimeout(8);
	OpportunisticSecureSMTPClient client2("aaa", 456);
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
