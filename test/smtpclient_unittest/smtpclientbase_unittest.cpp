#include <gtest/gtest.h>
#include <string>
#include <vector>
#include "../../src/messageaddress.h"
#include "../../src/smtpclientbase.h"
#include "../../src/cpp/forcedsecuresmtpclient.hpp"
#include "../../src/cpp/opportunisticsecuresmtpclient.hpp"
#include "../../src/cpp/smtpclient.hpp"
#include "../../src/smtpclienterrors.h"
#include "../../src/socketerrors.h"

using namespace jed_utils;

class FakeSMTPClientBase : public SMTPClientBase {
 public:
    FakeSMTPClientBase(const char *pServerName, unsigned int pPort)
        : SMTPClientBase(pServerName, pPort) {
    }

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

    int getServerReply() override {
        return 0;
    }

    static const char *getNullChar() { return nullptr; }

    static int extractReturnCode(const char *pOutput) {
        return SMTPClientBase::extractReturnCode(pOutput);
    }

    static ServerAuthOptions *extractAuthenticationOptions(const char *pEhloOutput) {
        return SMTPClientBase::extractAuthenticationOptions(pEhloOutput);
    }

    static std::string generateHeaderAddressValues(const std::vector<MessageAddress *> &pList) {
        return SMTPClientBase::generateHeaderAddressValues(pList);
    }
};

template<typename T>
class FakeCPPSMTPClientBase : public T {
 public:
    FakeCPPSMTPClientBase(const char *pServerName, unsigned int pPort)
        : T(pServerName == nullptr ? nullChar : std::string(pServerName), pPort) {
    }

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

    int getServerReply() override {
        return 0;
    }

    static const char *getNullChar() { return nullChar.c_str(); }

    static int extractReturnCode(const char *pOutput) {
        return T::extractReturnCode(pOutput == nullptr ? getNullChar() : pOutput);
    }

    static ServerAuthOptions *extractAuthenticationOptions(const char *pEhloOutput) {
        return T::extractAuthenticationOptions(pEhloOutput == nullptr ? getNullChar() : pEhloOutput);
    }

 private:
    static const std::string nullChar;
};

template<typename T>
const std::string FakeCPPSMTPClientBase<T>::nullChar = "";

template <typename T>
class MultiSmtpClientBaseFixture : public ::testing::Test {
 public:
    MultiSmtpClientBaseFixture<T>()
        : client("127.0.0.1", 587) {
    }
    T client;
};

using MyTypes = ::testing::Types<FakeSMTPClientBase,
                                 FakeCPPSMTPClientBase<jed_utils::cpp::SmtpClient>,
                                 FakeCPPSMTPClientBase<jed_utils::cpp::OpportunisticSecureSMTPClient>,
                                 FakeCPPSMTPClientBase<jed_utils::cpp::ForcedSecureSMTPClient>>;
TYPED_TEST_SUITE(MultiSmtpClientBaseFixture, MyTypes);

TYPED_TEST(MultiSmtpClientBaseFixture, Constructor_NullServerName_ThrowInvalidArgument) {
    try {
        TypeParam client1(TypeParam::getNullChar(), 587);
        FAIL();
    }
    catch(std::invalid_argument &err) {
        ASSERT_STREQ("Server name cannot be null or empty", err.what());
    }
}

TYPED_TEST(MultiSmtpClientBaseFixture, Constructor_EmptyServerName_ThrowInvalidArgument) {
    try {
        TypeParam client1("", 587);
        FAIL();
    }
    catch(std::invalid_argument &err) {
        ASSERT_STREQ("Server name cannot be null or empty", err.what());
    }
}

TYPED_TEST(MultiSmtpClientBaseFixture, Constructor_WhiteSpacesServerName_ThrowInvalidArgument) {
    try {
        TypeParam client1("   ", 587);
        FAIL();
    }
    catch(std::invalid_argument &err) {
        ASSERT_STREQ("Server name cannot be null or empty", err.what());
    }
}

TYPED_TEST(MultiSmtpClientBaseFixture, Constructor_WithValidArgs_ReturnSuccess) {
    TypeParam client1("test", 587);
    ASSERT_EQ("test", std::string(client1.getServerName()));
    ASSERT_EQ(587, client1.getServerPort());
    ASSERT_FALSE(client1.getBatchMode());
}

TYPED_TEST(MultiSmtpClientBaseFixture, CopyConstructorValid) {
    TypeParam client1("test", 587);
    TypeParam client2(client1);
    ASSERT_EQ("test", std::string(client2.getServerName()));
    ASSERT_EQ(587, client2.getServerPort());
}

TYPED_TEST(MultiSmtpClientBaseFixture, CopyAssignmentValid) {
    TypeParam client1("test", 587);
    TypeParam client2("another_test", 25);
    client2 = client1;
    ASSERT_EQ("test", std::string(client2.getServerName()));
    ASSERT_EQ(587, client2.getServerPort());
}

TYPED_TEST(MultiSmtpClientBaseFixture, MoveConstructorValid) {
    TypeParam client1("test", 587);
    TypeParam client2(std::move(client1));
    ASSERT_EQ("test", std::string(client2.getServerName()));
    ASSERT_EQ(587, client2.getServerPort());
}

TYPED_TEST(MultiSmtpClientBaseFixture, MoveAssignmentValid) {
    TypeParam client1("test", 587);
    TypeParam client2("another_test", 25);
    client2 = std::move(client1);
    ASSERT_EQ("test", std::string(client2.getServerName()));
    ASSERT_EQ(587, client2.getServerPort());
}

TYPED_TEST(MultiSmtpClientBaseFixture, setServerName_ValidName_ReturnSuccess) {
    TypeParam client1("test", 587);
    client1.setServerName("myServer");
    ASSERT_EQ("myServer", std::string(client1.getServerName()));
}

TYPED_TEST(MultiSmtpClientBaseFixture, setServerName_NullServerName_ThrowInvalidArgument) {
    TypeParam client1("test", 587);
    try {
        client1.setServerName(client1.getNullChar());
        FAIL();
    }
    catch(std::invalid_argument &err) {
        ASSERT_STREQ("Server name cannot be null or empty", err.what());
    }
}

TYPED_TEST(MultiSmtpClientBaseFixture, setServerName_EmptyServerName_ThrowInvalidArgument) {
    TypeParam client1("test", 587);
    try {
        client1.setServerName("");
        FAIL();
    }
    catch(std::invalid_argument &err) {
        ASSERT_STREQ("Server name cannot be null or empty", err.what());
    }
}

TYPED_TEST(MultiSmtpClientBaseFixture, setServerName_OnlySpacesServerName_ThrowInvalidArgument) {
    TypeParam client1("test", 587);
    try {
        client1.setServerName("    ");
        FAIL();
    }
    catch(std::invalid_argument &err) {
        ASSERT_STREQ("Server name cannot be null or empty", err.what());
    }
}

TYPED_TEST(MultiSmtpClientBaseFixture, getServerName_ReturnValidServerName) {
    ASSERT_EQ("127.0.0.1", std::string(this->client.getServerName()));
}

TYPED_TEST(MultiSmtpClientBaseFixture, setServerPort_WithPort465ReturnSuccess) {
    this->client.setServerPort(465);
    ASSERT_EQ(465, this->client.getServerPort());
}

TYPED_TEST(MultiSmtpClientBaseFixture, getServerPort_ReturnValidServerPort) {
    ASSERT_EQ(587, this->client.getServerPort());
}

TYPED_TEST(MultiSmtpClientBaseFixture, setBatchMode_WithTrueReturnSuccess) {
    this->client.setBatchMode(true);
    ASSERT_TRUE(this->client.getBatchMode());
}

TYPED_TEST(MultiSmtpClientBaseFixture, getBatchMode_WithNewClient_ReturnFalse) {
    ASSERT_FALSE(this->client.getBatchMode());
}

TYPED_TEST(MultiSmtpClientBaseFixture, getCommunicationLog_WithNewClient_ReturnEmpty) {
    ASSERT_EQ("", std::string(this->client.getCommunicationLog()));
}

TYPED_TEST(MultiSmtpClientBaseFixture, getCredentials_WithNewClient_ReturnNullPtr) {
    ASSERT_EQ(nullptr, this->client.getCredentials());
}

TEST(Credential, setCredentials_WithABCAnd123_ReturnSuccess) {
    FakeSMTPClientBase client("test", 587);
    ASSERT_EQ(nullptr, client.getCredentials());
    client.setCredentials(Credential("ABC", "123"));
    const auto *credentials = client.getCredentials();
    ASSERT_NE(nullptr, credentials);
    ASSERT_EQ("ABC", std::string(credentials->getUsername()));
    ASSERT_EQ("123", std::string(credentials->getPassword()));
}

TEST(CPP_Credential, setCredentials_WithABCAnd123_ReturnSuccess) {
    FakeCPPSMTPClientBase<::jed_utils::cpp::SmtpClient> client("test", 587);
    ASSERT_EQ(nullptr, client.getCredentials());
    client.setCredentials(jed_utils::cpp::Credential("ABC", "123"));
    const auto *credentials = client.getCredentials();
    ASSERT_NE(nullptr, credentials);
    ASSERT_EQ("ABC", std::string(credentials->getUsername()));
    ASSERT_EQ("123", std::string(credentials->getPassword()));
}

TYPED_TEST(MultiSmtpClientBaseFixture, extractReturnCode_ValidWelcomeCode220_Return220) {
    ASSERT_EQ(220, TypeParam::extractReturnCode("220 smtp.gmail.com ESMTP z13sm224346qkj.34 - gsmtp"));
}

TYPED_TEST(MultiSmtpClientBaseFixture, extractReturnCode_ValidClientCode250_Return250) {
    ASSERT_EQ(250, TypeParam::extractReturnCode("250-smtp.gmail.com at your service, [24.48.180.30]"));
}

TYPED_TEST(MultiSmtpClientBaseFixture, extractReturnCode_ValidClientCode250WithoutDash_Return250) {
    ASSERT_EQ(250, TypeParam::extractReturnCode("250 smtp.gmail.com at your service, [24.48.180.30]"));
}

TYPED_TEST(MultiSmtpClientBaseFixture, extractReturnCode_ValidClientCode250NoSpace_Return250) {
    ASSERT_EQ(250, TypeParam::extractReturnCode("250smtp.gmail.com at your service, [24.48.180.30]"));
}

TYPED_TEST(MultiSmtpClientBaseFixture, extractReturnCode_EmptyOutput_ReturnMinus1) {
    ASSERT_EQ(-1, TypeParam::extractReturnCode(""));
}

TYPED_TEST(MultiSmtpClientBaseFixture, extractReturnCode_TwoSpaces_ReturnMinus1) {
    ASSERT_EQ(-1, TypeParam::extractReturnCode("  "));
}

TYPED_TEST(MultiSmtpClientBaseFixture, extractReturnCode_ThreeSpaces_ReturnMinus1) {
    ASSERT_EQ(-1, TypeParam::extractReturnCode("   "));
}

TYPED_TEST(MultiSmtpClientBaseFixture, extractReturnCode_NotNumeric_ReturnMinus1) {
    ASSERT_EQ(-1, TypeParam::extractReturnCode("ABC"));
}

TYPED_TEST(MultiSmtpClientBaseFixture, extractReturnCode_NullPtr_ReturnMinus1) {
    ASSERT_EQ(-1, TypeParam::extractReturnCode(TypeParam::getNullChar()));
}

TYPED_TEST(MultiSmtpClientBaseFixture, getCommandTimeout_DefaultTimeOut_Return5) {
    TypeParam client1("fdfdsfs", 587);
    ASSERT_EQ(5, client1.getCommandTimeout());
}

TYPED_TEST(MultiSmtpClientBaseFixture, setCommandTimeout_With2_Return2) {
    TypeParam client1("fdfdsfs", 587);
    client1.setCommandTimeout(2);
    ASSERT_EQ(2, client1.getCommandTimeout());
}

TYPED_TEST(MultiSmtpClientBaseFixture, extractAuthenticationOptions_WithNullEhlo_ReturnNullptr) {
    ASSERT_EQ(nullptr, TypeParam::extractAuthenticationOptions(nullptr));
}

TYPED_TEST(MultiSmtpClientBaseFixture, extractAuthenticationOptions_WithEmptyEhlo_ReturnNullptr) {
    ASSERT_EQ(nullptr, TypeParam::extractAuthenticationOptions(""));
}

TYPED_TEST(MultiSmtpClientBaseFixture, extractAuthenticationOptions_WithOnlySpacesEhlo_ReturnNullptr) {
    ASSERT_EQ(nullptr, TypeParam::extractAuthenticationOptions("    "));
}

TYPED_TEST(MultiSmtpClientBaseFixture, extractAuthenticationOptions_WithNoAuthOptionsEhlo_ReturnNullptr) {
    ASSERT_EQ(nullptr, TypeParam::extractAuthenticationOptions("250-SIZE 35882577\r\n250-8BITMIME\r\n"));
}

TYPED_TEST(MultiSmtpClientBaseFixture, extractAuthenticationOptions_WithAuthOnlyPlainEhlo_ReturnOptions) {
    ServerAuthOptions *options = TypeParam::extractAuthenticationOptions("250-AUTH PLAIN\r\n");
    ASSERT_NE(nullptr, options);
    ASSERT_TRUE(options->Plain);
    ASSERT_FALSE(options->Login);
    ASSERT_FALSE(options->XOAuth2);
    ASSERT_FALSE(options->Plain_ClientToken);
    ASSERT_FALSE(options->OAuthBearer);
    ASSERT_FALSE(options->XOAuth);
}

TYPED_TEST(MultiSmtpClientBaseFixture, extractAuthenticationOptions_WithAuthPlainLoginEhlo_ReturnOptions) {
    ServerAuthOptions *options = TypeParam::extractAuthenticationOptions("250-AUTH LOGIN PLAIN\r\n");
    ASSERT_NE(nullptr, options);
    ASSERT_TRUE(options->Plain);
    ASSERT_TRUE(options->Login);
    ASSERT_FALSE(options->XOAuth2);
    ASSERT_FALSE(options->Plain_ClientToken);
    ASSERT_FALSE(options->OAuthBearer);
    ASSERT_FALSE(options->XOAuth);
}

TYPED_TEST(MultiSmtpClientBaseFixture, extractAuthenticationOptions_WithAuthPlainLoginEhloWithoutDash_ReturnOptions) {
    ServerAuthOptions *options = TypeParam::extractAuthenticationOptions("250-jedubuntuserver Hello [192.168.1.144]Haraka is at your service.\r\n"
"250-PIPELINING\r\n"
"250-8BITMIME\r\n"
"250-SMTPUTF8\r\n"
"250-SIZE 0\r\n"
"250 AUTH PLAIN LOGIN");
    ASSERT_NE(nullptr, options);
    ASSERT_TRUE(options->Plain);
    ASSERT_TRUE(options->Login);
    ASSERT_FALSE(options->XOAuth2);
    ASSERT_FALSE(options->Plain_ClientToken);
    ASSERT_FALSE(options->OAuthBearer);
    ASSERT_FALSE(options->XOAuth);
}

TYPED_TEST(MultiSmtpClientBaseFixture, extractAuthenticationOptions_WithAuthMultipleEhlo_ReturnOptions) {
    ServerAuthOptions *options = TypeParam::extractAuthenticationOptions("250-AUTH LOGIN PLAIN XOAUTH2 PLAIN-CLIENTTOKEN OAUTHBEARER XOAUTH\r\n");
    ASSERT_NE(nullptr, options);
    ASSERT_TRUE(options->Plain);
    ASSERT_TRUE(options->Login);
    ASSERT_TRUE(options->XOAuth2);
    ASSERT_TRUE(options->Plain_ClientToken);
    ASSERT_TRUE(options->OAuthBearer);
    ASSERT_TRUE(options->XOAuth);
}

TYPED_TEST(MultiSmtpClientBaseFixture, getErrorMessage_WithZero_ReturnNoMessage) {
    ASSERT_EQ("No message correspond to this error code",
              std::string(TypeParam::getErrorMessage(0)));
}

TYPED_TEST(MultiSmtpClientBaseFixture, getErrorMessage_WithMinusOne_ReturnErrorMessage) {
    ASSERT_EQ("Unable to create the socket", std::string(TypeParam::getErrorMessage(-1)));
}

TYPED_TEST(MultiSmtpClientBaseFixture, getErrorMessage_With538_ReturnErrorMessage) {
    ASSERT_EQ("Encryption required for requested authentication mechanism",
              std::string(TypeParam::getErrorMessage(SMTPSERVER_ENCRYPTIONREQUIREDFORAUTH_ERROR)));
}

TEST(SMTPClientBase, getErrorMessage_r_WithNullPtr_ReturnMinus1) {
    ASSERT_EQ(-1, FakeSMTPClientBase::getErrorMessage_r(-1, nullptr, 0));
}

TEST(SMTPClientBase, getErrorMessage_r_WithZeroLength_ReturnMinus1) {
    const size_t length = 6;
    char *buffer = new char[length];
    ASSERT_EQ(-1, FakeSMTPClientBase::getErrorMessage_r(-1, buffer, 0));
    delete[] buffer;
}

TEST(CPP_SmtpClient, getErrorMessage_r_WithZero_ReturnMinus1) {
    std::string msg = "";
    ASSERT_EQ(0, FakeCPPSMTPClientBase<jed_utils::cpp::SmtpClient>::getErrorMessage_r(0, msg));
    ASSERT_EQ("No message correspond to this error code", msg);
}

TEST(SMTPClientBase, getErrorMessage_r_WithCharPtrOfFive_Return6) {
    const size_t length = 6;
    char *buffer = new char[length];
    ASSERT_EQ(5, FakeSMTPClientBase::getErrorMessage_r(SOCKET_INIT_SESSION_CREATION_ERROR,
                                                       buffer,
                                                       length));
    ASSERT_STREQ("Unabl", buffer);
    delete[] buffer;
}

TEST(CPP_SmtpClient, getErrorMessage_r_WithMinus1_Return0) {
    std::string buffer = "";
    ASSERT_EQ(0, FakeCPPSMTPClientBase<jed_utils::cpp::SmtpClient>::getErrorMessage_r(SOCKET_INIT_SESSION_CREATION_ERROR,
                                                          buffer));
    ASSERT_EQ("Unable to create the socket", buffer);
}

TEST(SMTPClientBase, getErrorMessage_r_WithCharPtrOf50_Return0) {
    const size_t length = 50;
    char *buffer = new char[length];
    ASSERT_EQ(0, FakeSMTPClientBase::getErrorMessage_r(SOCKET_INIT_SESSION_CREATION_ERROR,
                                                       buffer,
                                                       length));
    ASSERT_STREQ("Unable to create the socket", buffer);
    delete[] buffer;
}

TEST(SMTPClientBase, generateHeaderAddressValues_WithToAndEmptyAddress_ReturnEmptyTo) {
    ASSERT_EQ("", FakeSMTPClientBase::generateHeaderAddressValues({}));
}

TEST(SMTPClientBase, generateHeaderAddressValues_WithToAndOneAddress_ReturnValidHeader) {
    MessageAddress addr1("test@test.com", "test");
    ASSERT_EQ("test <test@test.com>",
            FakeSMTPClientBase::generateHeaderAddressValues({ &addr1 }));
}

TEST(SMTPClientBase, generateHeaderAddressValues_WithToAndOneAddressWithoutDisplay_ReturnValidHeader) {
    MessageAddress addr1("test@test.com");
    ASSERT_EQ("test@test.com",
            FakeSMTPClientBase::generateHeaderAddressValues({ &addr1 }));
}

TEST(SMTPClientBase, generateHeaderAddressValues_WithToAndTwoAddresses_ReturnValidHeader) {
    MessageAddress addr1("test@test.com", "test");
    MessageAddress addr2("test2@test.com", "test2");
    ASSERT_EQ("test <test@test.com>, test2 <test2@test.com>", FakeSMTPClientBase::generateHeaderAddressValues({
                &addr1, &addr2 }));
}

TEST(SMTPClientBase, generateHeaderAddressValues_WithToAndTwoAddressesWithoutDisplay_ReturnValidHeader) {
    MessageAddress addr1("test@test.com");
    MessageAddress addr2("test2@test.com", "test2");
    ASSERT_EQ("test@test.com, test2 <test2@test.com>", FakeSMTPClientBase::generateHeaderAddressValues({
                &addr1, &addr2 }));
}

