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

TEST(SSLSmtpClient_Constructor, NullServerName)
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

TEST(SSLSmtpClient_Constructor, EmptyServerName)
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
#include "../../src/sslsmtpclient.h"
#include <gtest/gtest.h>

using namespace jed_utils;
using namespace std;
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
