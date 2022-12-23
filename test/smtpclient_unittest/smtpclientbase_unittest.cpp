#include "../../src/smtpclientbase.h"
#include <gtest/gtest.h>
#include "../../src/socketerrors.h"

using namespace jed_utils;

class FakeSMTPClientBase : public ::testing::Test, public SMTPClientBase {
 public:
    FakeSMTPClientBase()
        : SMTPClientBase("127.0.0.1", 587) {
    }

    FakeSMTPClientBase(const char *pServerName, unsigned int pPort)
        : SMTPClientBase(pServerName, pPort) {
    }
    void TestBody() override {}

    void cleanup() override {}

    int establishConnectionWithServer() override {
        return 0;
    }

    int sendCommand(const char *pCommand, int pErrorCode) override {
        return 0;
    }

    int sendCommandWithFeedback(const char *pCommand, int pErrorCode, int pTimeoutCode) override {
        return 0;
    }
};

TEST(SMTPClientBase_Constructor, NullServerName_ThrowInvalidArgument) {
    try {
        FakeSMTPClientBase client(nullptr, 587);
        FAIL();
    }
    catch(std::invalid_argument &err) {
        ASSERT_STREQ("Server name cannot be null or empty", err.what());
    }
}

TEST(SMTPClientBase_Constructor, EmptyServerName_ThrowInvalidArgument) {
    try {
        FakeSMTPClientBase client("", 587);
        FAIL();
    }
    catch(std::invalid_argument &err) {
        ASSERT_STREQ("Server name cannot be null or empty", err.what());
    }
}

TEST(SMTPClientBase_Constructor, WhiteSpacesServerName_ThrowInvalidArgument) {
    try {
        FakeSMTPClientBase client("   ", 587);
        FAIL();
    }
    catch(std::invalid_argument &err) {
        ASSERT_STREQ("Server name cannot be null or empty", err.what());
    }
}

TEST(SMTPClientBase_Constructor, WithValidArgs_ReturnSuccess) {
    FakeSMTPClientBase client("test", 587);
    ASSERT_STREQ("test", client.getServerName());
    ASSERT_EQ(587, client.getServerPort());
}

TEST(SmtpClientBase_setServerName, ValidName_ReturnSuccess) {
    FakeSMTPClientBase client("test", 587);
    client.setServerName("myServer");
    ASSERT_STREQ("myServer", client.getServerName());
}

TEST(SmtpClientBase_setServerName, NullServerName_ThrowInvalidArgument) {
    FakeSMTPClientBase client("test", 587);
    try {
        client.setServerName(nullptr);
        FAIL();
    }
    catch(std::invalid_argument &err) {
        ASSERT_STREQ("Server name cannot be null or empty", err.what());
    }
}

TEST(SmtpClientBase_setServerName, EmptyServerName_ThrowInvalidArgument) {
    FakeSMTPClientBase client("test", 587);
    try {
        client.setServerName("");
        FAIL();
    }
    catch(std::invalid_argument &err) {
        ASSERT_STREQ("Server name cannot be null or empty", err.what());
    }
}

TEST(SmtpClientBase_setServerName, OnlySpacesServerName_ThrowInvalidArgument) {
    FakeSMTPClientBase client("test", 587);
    try {
        client.setServerName("    ");
        FAIL();
    }
    catch(std::invalid_argument &err) {
        ASSERT_STREQ("Server name cannot be null or empty", err.what());
    }
}

TEST(SmtpClientBase_getServerName, ReturnValidServerName) {
    FakeSMTPClientBase client("test", 587);
    ASSERT_STREQ("test", client.getServerName());
}

TEST(SmtpClientBase_setServerPort, WithPort465ReturnSuccess) {
    FakeSMTPClientBase client("test", 587);
    client.setServerPort(465);
    ASSERT_EQ(465, client.getServerPort());
}

TEST(SmtpClientBase_getServerPort, ReturnValidServerPort) {
    FakeSMTPClientBase client("test", 587);
    ASSERT_EQ(587, client.getServerPort());
}

TEST_F(FakeSMTPClientBase, extractReturnCode_ValidWelcomeCode220_Return220) {
    ASSERT_EQ(220, extractReturnCode("220 smtp.gmail.com ESMTP z13sm224346qkj.34 - gsmtp"));
}

TEST_F(FakeSMTPClientBase, extractReturnCode_ValidClientCode250_Return250) {
    ASSERT_EQ(250, extractReturnCode("250-smtp.gmail.com at your service, [24.48.180.30]"));
}

TEST_F(FakeSMTPClientBase, extractReturnCode_ValidClientCode250WithoutDash_Return250) {
    ASSERT_EQ(250, extractReturnCode("250 smtp.gmail.com at your service, [24.48.180.30]"));
}

TEST_F(FakeSMTPClientBase, extractReturnCode_ValidClientCode250NoSpace_Return250) {
    ASSERT_EQ(250, extractReturnCode("250smtp.gmail.com at your service, [24.48.180.30]"));
}

TEST_F(FakeSMTPClientBase, extractReturnCode_EmptyOutput_ReturnMinus1) {
    ASSERT_EQ(-1, extractReturnCode(""));
}

TEST_F(FakeSMTPClientBase, extractReturnCode_TwoSpaces_ReturnMinus1) {
    ASSERT_EQ(-1, extractReturnCode("  "));
}

TEST_F(FakeSMTPClientBase, extractReturnCode_ThreeSpaces_ReturnMinus1) {
    ASSERT_EQ(-1, extractReturnCode("   "));
}

TEST_F(FakeSMTPClientBase, extractReturnCode_NotNumeric_ReturnMinus1) {
    ASSERT_EQ(-1, extractReturnCode("ABC"));
}

TEST_F(FakeSMTPClientBase, extractReturnCode_NullPtr_ReturnMinus1) {
    ASSERT_EQ(-1, extractReturnCode(nullptr));
}

TEST(SmtpClientBase_getCommandTimeout, DefaultTimeOut_Return3) {
    FakeSMTPClientBase client("fdfdsfs", 587);
    ASSERT_EQ(3, client.getCommandTimeout());
}

TEST(SmtpClientBase_getCommandTimeout, SetTimeOutWith2_Return2) {
    FakeSMTPClientBase client("fdfdsfs", 587);
    client.setCommandTimeout(2);
    ASSERT_EQ(2, client.getCommandTimeout());
}

TEST_F(FakeSMTPClientBase, extractAuthenticationOptions_WithNullEhlo_ReturnNullptr) {
    ASSERT_EQ(nullptr, extractAuthenticationOptions(nullptr));
}

TEST_F(FakeSMTPClientBase, extractAuthenticationOptions_WithEmptyEhlo_ReturnNullptr) {
    ASSERT_EQ(nullptr, extractAuthenticationOptions(""));
}

TEST_F(FakeSMTPClientBase, extractAuthenticationOptions_WithOnlySpacesEhlo_ReturnNullptr) {
    ASSERT_EQ(nullptr, extractAuthenticationOptions("    "));
}

TEST_F(FakeSMTPClientBase, extractAuthenticationOptions_WithNoAuthOptionsEhlo_ReturnNullptr) {
    ASSERT_EQ(nullptr, extractAuthenticationOptions("250-SIZE 35882577\r\n250-8BITMIME\r\n"));
}

TEST_F(FakeSMTPClientBase, extractAuthenticationOptions_WithAuthOnlyPlainEhlo_ReturnNullptr) {
    ServerAuthOptions *options = extractAuthenticationOptions("250-AUTH PLAIN\r\n");
    ASSERT_NE(nullptr, options);
    ASSERT_TRUE(options->Plain);
    ASSERT_FALSE(options->Login);
    ASSERT_FALSE(options->XOAuth2);
    ASSERT_FALSE(options->Plain_ClientToken);
    ASSERT_FALSE(options->OAuthBearer);
    ASSERT_FALSE(options->XOAuth);
}

TEST_F(FakeSMTPClientBase, extractAuthenticationOptions_WithAuthPlainLoginEhlo_ReturnNullptr) {
    ServerAuthOptions *options = extractAuthenticationOptions("250-AUTH LOGIN PLAIN\r\n");
    ASSERT_NE(nullptr, options);
    ASSERT_TRUE(options->Plain);
    ASSERT_TRUE(options->Login);
    ASSERT_FALSE(options->XOAuth2);
    ASSERT_FALSE(options->Plain_ClientToken);
    ASSERT_FALSE(options->OAuthBearer);
    ASSERT_FALSE(options->XOAuth);
}

TEST_F(FakeSMTPClientBase, extractAuthenticationOptions_WithAuthMultipleEhlo_ReturnNullptr) {
    ServerAuthOptions *options = extractAuthenticationOptions("250-AUTH LOGIN PLAIN XOAUTH2 PLAIN-CLIENTTOKEN OAUTHBEARER XOAUTH\r\n");
    ASSERT_NE(nullptr, options);
    ASSERT_TRUE(options->Plain);
    ASSERT_TRUE(options->Login);
    ASSERT_TRUE(options->XOAuth2);
    ASSERT_TRUE(options->Plain_ClientToken);
    ASSERT_TRUE(options->OAuthBearer);
    ASSERT_TRUE(options->XOAuth);
}

TEST_F(FakeSMTPClientBase, getErrorMessage_r_WithNullPtr_ReturnMinus1) {
    ASSERT_EQ(-1, getErrorMessage_r(-1, nullptr, 0));
}

TEST_F(FakeSMTPClientBase, getErrorMessage_r_WithZeroLength_ReturnMinus1) {
    const size_t length = 6;
    char *buffer = new char[length];
    ASSERT_EQ(-1, getErrorMessage_r(-1, buffer, 0));
    delete[] buffer;
}

TEST_F(FakeSMTPClientBase, getErrorMessage_r_WithCharPtrOfFive_Return6) {
    const size_t length = 6;
    char *buffer = new char[length];
    ASSERT_EQ(5, getErrorMessage_r(SOCKET_INIT_SESSION_CREATION_ERROR, buffer, length));
    ASSERT_STREQ("Unabl", buffer);
    delete[] buffer;
}

TEST_F(FakeSMTPClientBase, getErrorMessage_r_WithCharPtrOf50_Return0) {
    const size_t length = 50;
    char *buffer = new char[length];
    ASSERT_EQ(0, getErrorMessage_r(SOCKET_INIT_SESSION_CREATION_ERROR, buffer, length));
    ASSERT_STREQ("Unable to create the socket", buffer);
    delete[] buffer;
}
