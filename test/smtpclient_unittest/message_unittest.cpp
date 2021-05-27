#include "../../src/message.h"
#include <gtest/gtest.h>

using namespace jed_utils;
using namespace std;

class FakeMessage : public Message
{
public:
    FakeMessage(const MessageAddress &pFrom,
			const MessageAddress &pTo,
			const char *pSubject,
			const char *pBody)
        : Message(pFrom, pTo, pSubject, pBody) 
    {
    }

    const char *getMimeType() const override { return nullptr; }
};

void validateMinimumDataMessage(const Message &msg)
{
    ASSERT_STREQ("test@test.com", msg.getFrom().getEmailAddress());
    ASSERT_EQ(1, msg.getToCount());
    ASSERT_STREQ("test2@test.com", msg.getTo()[0]->getEmailAddress());
    ASSERT_STREQ("", msg.getSubject());
    ASSERT_STREQ("", msg.getBody());
    ASSERT_EQ(0, msg.getCcCount());
    ASSERT_EQ(nullptr, msg.getCc());
    ASSERT_EQ(0, msg.getBccCount());
    ASSERT_EQ(nullptr, msg.getBcc());
    ASSERT_EQ(0, msg.getAttachmentsCount());
    ASSERT_EQ(nullptr, msg.getAttachments());
}

TEST(Message_constructor, WithSingleToRecipientAndMinimumData_Success)
{
    FakeMessage msg(MessageAddress("test@test.com"),
                    MessageAddress("test2@test.com"),
                    "",
                    "");
    validateMinimumDataMessage(msg);
}

TEST(Message_constructor, WithSingleToRecipientAndNullSubject_Success)
{
    FakeMessage msg(MessageAddress("test@test.com"),
                    MessageAddress("test2@test.com"),
                    nullptr,
                    "");
    validateMinimumDataMessage(msg);
}

TEST(Message_constructor, WithSingleToRecipientAndNullBody_Success)
{
    FakeMessage msg(MessageAddress("test@test.com"),
                    MessageAddress("test2@test.com"),
                    "",
                    nullptr);
    validateMinimumDataMessage(msg);
}