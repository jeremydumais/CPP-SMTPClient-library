#include <gtest/gtest.h>
#include "../../Include/PlainTextMessage.h"
#include <stdexcept>

using namespace jed_utils;
using namespace std;

class SimpleMessage : public ::testing::Test
{
public:
    SimpleMessage()
    {
        msg = new PlaintextMessage(MessageAddress("myfromaddress@test.com", "Test Address Display"),
        MessageAddress("youraddress@domain.com"),
        "This is a test (Subject)",
        "Hello\nHow are you?");
    }

    ~SimpleMessage()
    {
        if (msg)
            delete msg;
    }

    PlaintextMessage *msg;
};

TEST(plainTextMessage_SimpleConstructor, validParams)
{
    PlaintextMessage msg(MessageAddress("myfromaddress@test.com", "Test Address Display"),
        MessageAddress("youraddress@domain.com"),
        "This is a test (Subject)",
        "Hello\nHow are you?");
}

TEST(plainTextMessage_ExtendedConstructor, validParams)
{
    MessageAddress addr_to[1] = { MessageAddress("youraddress@domain.com") };
    PlaintextMessage msg(MessageAddress("myfromaddress@test.com", "Test Address Display"),
        addr_to, 1,
        "This is a test (Subject)",
        "Hello\nHow are you?");
}

//Simple Message fixture tests

TEST_F(SimpleMessage, getFromReturnValid)
{
    ASSERT_EQ(msg->getFrom(), MessageAddress("myfromaddress@test.com", "Test Address Display"));
}

TEST_F(SimpleMessage, getToCountReturnValid)
{
    ASSERT_EQ(msg->getToCount(), 1);
}

TEST_F(SimpleMessage, getToReturnValid)
{
    ASSERT_EQ(msg->getToCount(), 1);
    ASSERT_EQ(msg->getToPtr()[0], MessageAddress("youraddress@domain.com"));
}

TEST_F(SimpleMessage, getSubjectReturnValid)
{
    ASSERT_EQ(_stricmp(msg->getSubject(), "This is a test (Subject)"), 0);
}

TEST_F(SimpleMessage, getBodyReturnValid)
{
    ASSERT_EQ(_stricmp(msg->getBody(), "Hello\nHow are you?"), 0);
}

TEST_F(SimpleMessage, getCcCountReturnValid)
{
    ASSERT_EQ(msg->getCcCount(), 0);
}

TEST_F(SimpleMessage, getCcReturnNull)
{
    ASSERT_EQ(msg->getCcPtr(), nullptr);
}

TEST_F(SimpleMessage, getAttachmentsCountReturn0)
{
    ASSERT_EQ(msg->getAttachmentsCount(), 0);
}

TEST_F(SimpleMessage, getAttachmentsPtrReturnNull)
{
    ASSERT_EQ(msg->getAttachmentsPtr(), nullptr);
}

TEST_F(SimpleMessage, getMimeTypeReturnValidPlainText)
{
    ASSERT_EQ(_stricmp(msg->getMimeType(), "text/plain"), 0);
}

//End Simple Message fixture tests