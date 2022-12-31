#include "../../src/opportunisticsecuresmtpclient.h"
#include "../../src/cpp/opportunisticsecuresmtpclient.hpp"
#include <gtest/gtest.h>

using namespace jed_utils;

class FakeOpportunisticSecureSMTPClient : public ::testing::Test, public OpportunisticSecureSMTPClient {
 public:
    FakeOpportunisticSecureSMTPClient()
        : OpportunisticSecureSMTPClient("127.0.0.1", 587) {
    }
};

template <typename T>
class MultiOppSmtpClientFixture : public ::testing::Test {
 public:
    MultiOppSmtpClientFixture<T>()
        : client("test", 587) {
    }
    T client;
};

using MyTypes = ::testing::Types<OpportunisticSecureSMTPClient, cpp::OpportunisticSecureSMTPClient>;
TYPED_TEST_SUITE(MultiOppSmtpClientFixture, MyTypes);

TEST(OpportunisticSecureSMTPClient_Constructor, NullServerName_ThrowInvalidArgument) {
    try {
        OpportunisticSecureSMTPClient client(nullptr, 587);
        FAIL();
    }
    catch(std::invalid_argument &err) {
        ASSERT_STREQ("Server name cannot be null or empty", err.what());
    }
}

TEST(OpportunisticSecureSMTPClient_Constructor, EmptyServerName_ThrowInvalidArgument) {
    try {
        OpportunisticSecureSMTPClient client("", 587);
        FAIL();
    }
    catch(std::invalid_argument &err) {
        ASSERT_STREQ("Server name cannot be null or empty", err.what());
    }
}

TEST(OpportunisticSecureSMTPClient_Constructor, OnlySpacesServerName_ThrowInvalidArgument) {
    try {
        OpportunisticSecureSMTPClient client("   ", 587);
        FAIL();
    }
    catch(std::invalid_argument &err) {
        ASSERT_STREQ("Server name cannot be null or empty", err.what());
    }
}

TEST(OpportunisticSecureSMTPClient_Constructor, ValidArguments_ReturnSuccess) {
    OpportunisticSecureSMTPClient client("test", 587);
    ASSERT_STREQ("test", client.getServerName());
    ASSERT_EQ(587, client.getServerPort());
}

TEST(OpportunisticSecureSMTPClient_CopyConstructor, OpportunisticSecureSMTPClientCopyConstructorValid) {
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

TEST(OpportunisticSecureSMTPClient_CopyAssignment, OpportunisticSecureSMTPClientCopyAssignmentValid) {
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

TEST(OpportunisticSecureSMTPClient_MoveConstructor, OpportunisticSecureSMTPClientMoveConstructorValid) {
    OpportunisticSecureSMTPClient client1("test", 123);
    client1.setCredentials(Credential("user1", "pass1"));
    client1.setCommandTimeout(8);
    OpportunisticSecureSMTPClient client2(std::move(client1));
    ASSERT_STREQ("test", client2.getServerName());
    ASSERT_EQ(123, client2.getServerPort());
    ASSERT_EQ(8, client2.getCommandTimeout());
    ASSERT_STREQ("user1", client2.getCredentials()->getUsername());
    ASSERT_STREQ("pass1", client2.getCredentials()->getPassword());
}

TEST(OpportunisticSecureSMTPClient_MoveAssignment, OpportunisticSecureSMTPClientMoveAssignmentValid) {
    OpportunisticSecureSMTPClient client1("test", 123);
    client1.setCredentials(Credential("user1", "pass1"));
    client1.setCommandTimeout(8);
    OpportunisticSecureSMTPClient client2("aaa", 456);
    client2 = std::move(client1);
    ASSERT_STREQ("test", client2.getServerName());
    ASSERT_EQ(123, client2.getServerPort());
    ASSERT_EQ(8, client2.getCommandTimeout());
    ASSERT_STREQ("user1", client2.getCredentials()->getUsername());
    ASSERT_STREQ("pass1", client2.getCredentials()->getPassword());
}

TEST_F(FakeOpportunisticSecureSMTPClient, isStartTLSSupported_WithNullServerReponse_ReturnFalse) {
    ASSERT_FALSE(isStartTLSSupported(nullptr));
}

TEST_F(FakeOpportunisticSecureSMTPClient, isStartTLSSupported_WithEmptyServerReponse_ReturnFalse) {
    ASSERT_FALSE(isStartTLSSupported(""));
}

TEST_F(FakeOpportunisticSecureSMTPClient, isStartTLSSupported_WithWhiteSpacesServerReponse_ReturnFalse) {
    ASSERT_FALSE(isStartTLSSupported("   "));
}

TEST_F(FakeOpportunisticSecureSMTPClient, isStartTLSSupported_WithServerReponseContainingSTARTTLS_ReturnTrue) {
    ASSERT_TRUE(isStartTLSSupported("250-SIZE 35882577\r\n"
                "250-8BITMIME\r\n"
                "250-STARTTLS\r\n"
                "250-ENHANCEDSTATUSCODES\r\n"
                "250-PIPELINING\r\n"
                "250-CHUNKING\r\n"
                "250 SMTPUTF8"));
}

TEST_F(FakeOpportunisticSecureSMTPClient, isStartTLSSupported_WithoutServerReponseContainingSTARTTLS_ReturnFalse) {
    ASSERT_FALSE(isStartTLSSupported("250-SIZE 35882577\r\n"
                "250-8BITMIME\r\n"
                "250-ENHANCEDSTATUSCODES\r\n"
                "250-PIPELINING\r\n"
                "250-CHUNKING\r\n"
                "250 SMTPUTF8"));
}
