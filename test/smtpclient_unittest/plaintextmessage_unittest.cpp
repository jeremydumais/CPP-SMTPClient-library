#include <gtest/gtest.h>
#include <stdexcept>
#include <vector>
#include "../../src/plaintextmessage.h"

using namespace jed_utils;

class SimpleMessage : public ::testing::Test {
 public:
    SimpleMessage() {
        msg = new PlaintextMessage(MessageAddress("myfromaddress@test.com", "Test Address Display"),
        MessageAddress("youraddress@domain.com"),
        "This is a test (Subject)",
        "Hello\nHow are you?");
    }

    ~SimpleMessage() {
        if (msg) {
            delete msg;
        }
    }

    PlaintextMessage *msg;
};

class CompleteMessageWithSimpleConstructor : public ::testing::Test {
 public:
    CompleteMessageWithSimpleConstructor() {
        Attachment att[2] { Attachment("C:\\Temp\\test.png", "test image.png"), Attachment("C:\\Temp\\test2.png", "test image2.png") };
        MessageAddress cc[1] { MessageAddress("myccaddress@domain.com", "myCCName") };
        MessageAddress bcc[1] { MessageAddress("mybccaddress@domain.com", "myBCCName") };
        msg = new PlaintextMessage(MessageAddress("myfromaddress@test.com", "Test Address Display"),
        MessageAddress("youraddress@domain.com", "DisplayNameTo"),
        "This is a test (Subject)",
        "Hello\nHow are you?",
        cc,
        bcc,
        att);
    }

    ~CompleteMessageWithSimpleConstructor() {
        if (msg) {
            delete msg;
        }
    }

    PlaintextMessage *msg;
};

TEST(plainTextMessage_SimpleConstructor, validParams) {
    PlaintextMessage(MessageAddress("myfromaddress@test.com", "Test Address Display"),
        MessageAddress("youraddress@domain.com"),
        "This is a test (Subject)",
        "Hello\nHow are you?");
}

TEST(plainTextMessage_ExtendedConstructor, validParams) {
    MessageAddress addr_to[1] { MessageAddress("youraddress@domain.com") };
    PlaintextMessage(MessageAddress("myfromaddress@test.com", "Test Address Display"),
        *addr_to,
        "This is a test (Subject)",
        "Hello\nHow are you?");
}

// Simple Message fixture tests
TEST_F(SimpleMessage, getFromReturnValid) {
    ASSERT_EQ(msg->getFrom(), MessageAddress("myfromaddress@test.com", "Test Address Display"));
}

TEST_F(SimpleMessage, getToCountReturnValid) {
    ASSERT_EQ(msg->getToCount(), 1);
}

TEST_F(SimpleMessage, getToReturnValid) {
    ASSERT_EQ(msg->getToCount(), 1);
    ASSERT_EQ(*msg->getTo()[0], MessageAddress("youraddress@domain.com"));
}

TEST_F(SimpleMessage, getSubjectReturnValid) {
    ASSERT_STREQ("This is a test (Subject)", msg->getSubject());
}

TEST_F(SimpleMessage, getBodyReturnValid) {
    ASSERT_STREQ("Hello\nHow are you?", msg->getBody());
}

TEST_F(SimpleMessage, getCcCountReturnValid) {
    ASSERT_EQ(msg->getCcCount(), 0);
}

TEST_F(SimpleMessage, getCcReturnNull) {
    ASSERT_EQ(nullptr, msg->getCc());
}

TEST_F(SimpleMessage, getAttachmentsCountReturn0) {
    ASSERT_EQ(msg->getAttachmentsCount(), 0);
}

TEST_F(SimpleMessage, getAttachmentsPtrReturnNull) {
    ASSERT_EQ(nullptr, msg->getAttachments());
}

TEST_F(SimpleMessage, getMimeTypeReturnValidPlainText) {
    ASSERT_STREQ("text/plain", msg->getMimeType());
}

// End Simple Message fixture tests
