#include "../../src/message.h"
#include <gtest/gtest.h>

using namespace jed_utils;

class FakeMessage : public Message {
 public:
    FakeMessage(const MessageAddress &pFrom,
            const MessageAddress &pTo,
            const char *pSubject,
            const char *pBody,
            const MessageAddress *pCc = nullptr,
            const MessageAddress *pBcc = nullptr,
            const Attachment pAttachments[] = nullptr,
            size_t pAttachmentsSize = 0)
        : Message(pFrom, pTo, pSubject, pBody, pCc, pBcc, pAttachments, pAttachmentsSize) {
    }

    FakeMessage(const MessageAddress &pFrom,
            const MessageAddress pTo[],
            size_t pToCount,
            const char *pSubject,
            const char *pBody,
            const MessageAddress pCc[] = nullptr,
            size_t pCcCount = 0,
            const MessageAddress pBcc[] = nullptr,
            size_t pBccCount = 0,
            const Attachment pAttachments[] = nullptr,
            size_t pAttachmentsSize = 0)
        : Message(pFrom, pTo, pToCount, pSubject, pBody, pCc, pCcCount,
                  pBcc, pBccCount, pAttachments, pAttachmentsSize) {
    }

    const char *getMimeType() const override { return nullptr; }
};

void validateMinimumDataMessage(const Message &msg) {
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

FakeMessage getFakeMessageSample1() {
    MessageAddress *cc = new MessageAddress("cc@cc.com");
    MessageAddress *bcc = new MessageAddress("bcc@bcc.com");
    Attachment att[] { Attachment("file1.png"), Attachment("file2.png") };
    return FakeMessage(MessageAddress("from@from.com"),
            MessageAddress("to@to.com"),
            "Subject",
            "Body",
            cc,
            bcc,
            att, 2);
}

FakeMessage getFakeMessageSample2() {
    MessageAddress to[2] { MessageAddress("to1@to.com"), MessageAddress("to2@to.com") };
    MessageAddress cc[2] = { MessageAddress("cc1@cc.com"), MessageAddress("cc2@cc.com") };
    MessageAddress bcc[2] = { MessageAddress("bcc1@bcc.com"), MessageAddress("bcc2@bcc.com") };
    Attachment att[] { Attachment("file1.png"), Attachment("file2.png") };
    return FakeMessage(MessageAddress("from@from.com"),
            to, 2,
            "Subject",
            "Body",
            cc, 2,
            bcc, 2,
            att, 2);
}

void validateFakeMessageSample1(const FakeMessage &msg) {
    ASSERT_STREQ("from@from.com", msg.getFrom().getEmailAddress());
    ASSERT_STREQ("to@to.com", msg.getTo()[0]->getEmailAddress());
    ASSERT_STREQ("Subject", msg.getSubject());
    ASSERT_STREQ("Body", msg.getBody());
    ASSERT_STREQ("cc@cc.com", msg.getCc()[0]->getEmailAddress());
    ASSERT_STREQ("bcc@bcc.com", msg.getBcc()[0]->getEmailAddress());
    ASSERT_STREQ("file1.png", msg.getAttachments()[0]->getFilename());
    ASSERT_STREQ("file2.png", msg.getAttachments()[1]->getFilename());
    ASSERT_EQ(2, msg.getAttachmentsCount());
}

void validateFakeMessageSample2(const FakeMessage &msg) {
    ASSERT_STREQ("from@from.com", msg.getFrom().getEmailAddress());
    ASSERT_STREQ("to1@to.com", msg.getTo()[0]->getEmailAddress());
    ASSERT_STREQ("to2@to.com", msg.getTo()[1]->getEmailAddress());
    ASSERT_STREQ("Subject", msg.getSubject());
    ASSERT_STREQ("Body", msg.getBody());
    ASSERT_STREQ("cc1@cc.com", msg.getCc()[0]->getEmailAddress());
    ASSERT_STREQ("cc2@cc.com", msg.getCc()[1]->getEmailAddress());
    ASSERT_STREQ("bcc1@bcc.com", msg.getBcc()[0]->getEmailAddress());
    ASSERT_STREQ("bcc2@bcc.com", msg.getBcc()[1]->getEmailAddress());
    ASSERT_STREQ("file1.png", msg.getAttachments()[0]->getFilename());
    ASSERT_STREQ("file2.png", msg.getAttachments()[1]->getFilename());
    ASSERT_EQ(2, msg.getAttachmentsCount());
}

TEST(Message_constructor, WithSingleToRecipientAndMinimumData_Success) {
    FakeMessage msg(MessageAddress("test@test.com"),
            MessageAddress("test2@test.com"),
            "",
            "");
    validateMinimumDataMessage(msg);
}

TEST(Message_constructor, WithSingleToRecipientAndNullSubject_Success) {
    FakeMessage msg(MessageAddress("test@test.com"),
            MessageAddress("test2@test.com"),
            nullptr,
            "");
    validateMinimumDataMessage(msg);
}

TEST(Message_constructor, WithSingleToRecipientAndNullBody_Success) {
    FakeMessage msg(MessageAddress("test@test.com"),
            MessageAddress("test2@test.com"),
            "",
            nullptr);
    validateMinimumDataMessage(msg);
}

TEST(Message_constructor, WithCompleteInfos_Success) {
    auto msg = getFakeMessageSample1();
    validateFakeMessageSample1(msg);
}

TEST(Message_constructor, WithExtendedInfos_Success) {
    auto msg = getFakeMessageSample2();
    validateFakeMessageSample2(msg);
}

TEST(Message_CopyConstructor, MessageCopyConstructorValid) {
    auto msg1 = getFakeMessageSample2();
    FakeMessage msg2(msg1);
    validateFakeMessageSample2(msg2);
}

TEST(Message_CopyAssignment, MessageCopyAssignmentValid) {
    auto msg1 = getFakeMessageSample2();
    auto msg2 = getFakeMessageSample1();
    msg2 = msg1;
    validateFakeMessageSample2(msg2);
}

TEST(Message_MoveConstructor, MessageMoveConstructorValid) {
    auto msg1 = getFakeMessageSample2();
    FakeMessage msg2(std::move(msg1));
    validateFakeMessageSample2(msg2);
}

TEST(Message_MoveAssignment, MessageMoveAssignmentValid) {
    auto msg1 = getFakeMessageSample2();
    FakeMessage msg2 = getFakeMessageSample1();
    msg2 = std::move(msg1);
    validateFakeMessageSample2(msg2);
}
