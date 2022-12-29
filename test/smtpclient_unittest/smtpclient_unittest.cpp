#include "../../src/smtpclient.h"
#include "../../src/cpp/smtpclient.hpp"
#include <gtest/gtest.h>

using namespace jed_utils;

class FakeSMTPClient : public ::testing::Test, public SmtpClient {
 public:
    FakeSMTPClient()
        : SmtpClient("127.0.0.1", 587) {
    }
};

TEST(SmtpClient_Constructor, NullServerName_ThrowInvalidArgument) {
    try {
        SmtpClient client(nullptr, 587);
        FAIL();
    }
    catch(std::invalid_argument &err) {
        ASSERT_STREQ("Server name cannot be null or empty", err.what());
    }
}

TEST(SmtpClient_Constructor, EmptyServerName_ThrowInvalidArgument) {
    try {
        SmtpClient client("", 587);
        FAIL();
    }
    catch(std::invalid_argument &err) {
        ASSERT_STREQ("Server name cannot be null or empty", err.what());
    }
}

TEST(SmtpClient_Constructor, OnlySpacesServerName_ThrowInvalidArgument) {
    try {
        SmtpClient client("   ", 587);
        FAIL();
    }
    catch(std::invalid_argument &err) {
        ASSERT_STREQ("Server name cannot be null or empty", err.what());
    }
}

TEST(SmtpClient_Constructor, ValidArguments_ReturnSuccess) {
    SmtpClient client("test", 587);
    ASSERT_STREQ("test", client.getServerName());
    ASSERT_EQ(587, client.getServerPort());
}

TEST(SmtpClient_CopyConstructor, SmtpClientCopyConstructorValid) {
    SmtpClient* client1 = new SmtpClient("server1", 123);
    client1->setCredentials(Credential("user1", "pass1"));
    client1->setCommandTimeout(8);
    SmtpClient client2(*client1);
    delete client1;
    ASSERT_STREQ("server1", client2.getServerName());
    ASSERT_EQ(123, client2.getServerPort());
    ASSERT_EQ(8, client2.getCommandTimeout());
    ASSERT_STREQ("user1", client2.getCredentials()->getUsername());
    ASSERT_STREQ("pass1", client2.getCredentials()->getPassword());
}

TEST(SmtpClient_CopyAssignment, SmtpClientCopyAssignmentValid) {
    SmtpClient* client1 = new SmtpClient("test", 123);
    client1->setCredentials(Credential("user1", "pass1"));
    client1->setCommandTimeout(8);
    SmtpClient client2("aaa", 456);
    client2 = *client1;
    delete client1;
    ASSERT_STREQ("test", client2.getServerName());
    ASSERT_EQ(123, client2.getServerPort());
    ASSERT_EQ(8, client2.getCommandTimeout());
    ASSERT_STREQ("user1", client2.getCredentials()->getUsername());
    ASSERT_STREQ("pass1", client2.getCredentials()->getPassword());
}

TEST(SmtpClient_MoveConstructor, SmtpClientMoveConstructorValid) {
    SmtpClient client1("test", 123);
    client1.setCredentials(Credential("user1", "pass1"));
    client1.setCommandTimeout(8);
    SmtpClient client2(std::move(client1));
    ASSERT_STREQ("test", client2.getServerName());
    ASSERT_EQ(123, client2.getServerPort());
    ASSERT_EQ(8, client2.getCommandTimeout());
    ASSERT_STREQ("user1", client2.getCredentials()->getUsername());
    ASSERT_STREQ("pass1", client2.getCredentials()->getPassword());
}

TEST(SmtpClient_MoveAssignment, SmtpClientMoveAssignmentValid) {
    SmtpClient client1("test", 123);
    client1.setCredentials(Credential("user1", "pass1"));
    client1.setCommandTimeout(8);
    SmtpClient client2("aaa", 456);
    client2 = std::move(client1);
    ASSERT_STREQ("test", client2.getServerName());
    ASSERT_EQ(123, client2.getServerPort());
    ASSERT_EQ(8, client2.getCommandTimeout());
    ASSERT_STREQ("user1", client2.getCredentials()->getUsername());
    ASSERT_STREQ("pass1", client2.getCredentials()->getPassword());
}
