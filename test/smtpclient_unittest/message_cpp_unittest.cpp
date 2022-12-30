#include "../../src/cpp/message.hpp"
#include <gtest/gtest.h>

using namespace jed_utils::cpp;

namespace jed_utils_unittest {
namespace cpp_message {


class FakeMessage : public Message {
 public:
    FakeMessage(const MessageAddress &pFrom,
                const std::vector<MessageAddress> &pTo,
                const std::string &pSubject,
                const std::string &pBody,
                const std::vector<MessageAddress> &pCc = {},
                const std::vector<MessageAddress> &pBcc = {},
                const std::vector<Attachment> &pAttachments = {})
        : Message(pFrom, pTo, pSubject, pBody, pCc, pBcc, pAttachments) {
    }

    std::string getMimeType() const override { return ""; }
};

void validateMinimumDataMessage(const Message &msg) {
    ASSERT_EQ("test@test.com", msg.getFrom().getEmailAddress());
    ASSERT_EQ(1, msg.getToCount());
    ASSERT_EQ("test2@test.com", msg.getTo()[0].getEmailAddress());
    ASSERT_EQ("", msg.getSubject());
    ASSERT_EQ("", msg.getBody());
    ASSERT_EQ(0, msg.getCcCount());
    ASSERT_EQ(0, msg.getBccCount());
    ASSERT_EQ(0, msg.getAttachmentsCount());
}

FakeMessage getFakeMessageSample1() {
    return FakeMessage(MessageAddress("from@from.com"),
            { MessageAddress("to@to.com") },
            "Subject",
            "Body",
            { MessageAddress("cc@cc.com") },
            { MessageAddress("bcc@bcc.com") },
            { Attachment("file1.png"), Attachment("file2.png") });
}

FakeMessage getFakeMessageSample2() {
    return FakeMessage(MessageAddress("from@from.com"),
            { MessageAddress("to1@to.com"), MessageAddress("to2@to.com") },
            "Subject",
            "Body",
            { MessageAddress("cc1@cc.com"), MessageAddress("cc2@cc.com") },
            { MessageAddress("bcc1@bcc.com"), MessageAddress("bcc2@bcc.com") },
            { Attachment("file1.png"), Attachment("file2.png") });
}

void validateFakeMessageSample1(const FakeMessage &msg) {
    ASSERT_EQ("from@from.com", msg.getFrom().getEmailAddress());
    ASSERT_EQ("to@to.com", msg.getTo()[0].getEmailAddress());
    ASSERT_EQ("Subject", msg.getSubject());
    ASSERT_EQ("Body", msg.getBody());
    ASSERT_EQ("cc@cc.com", msg.getCc()[0].getEmailAddress());
    ASSERT_EQ("bcc@bcc.com", msg.getBcc()[0].getEmailAddress());
    ASSERT_EQ("file1.png", msg.getAttachments()[0].getFilename());
    ASSERT_EQ("file2.png", msg.getAttachments()[1].getFilename());
    ASSERT_EQ(2, msg.getAttachmentsCount());
}

void validateFakeMessageSample2(const FakeMessage &msg) {
    ASSERT_EQ("from@from.com", msg.getFrom().getEmailAddress());
    ASSERT_EQ("to1@to.com", msg.getTo()[0].getEmailAddress());
    ASSERT_EQ("to2@to.com", msg.getTo()[1].getEmailAddress());
    ASSERT_EQ("Subject", msg.getSubject());
    ASSERT_EQ("Body", msg.getBody());
    ASSERT_EQ("cc1@cc.com", msg.getCc()[0].getEmailAddress());
    ASSERT_EQ("cc2@cc.com", msg.getCc()[1].getEmailAddress());
    ASSERT_EQ("bcc1@bcc.com", msg.getBcc()[0].getEmailAddress());
    ASSERT_EQ("bcc2@bcc.com", msg.getBcc()[1].getEmailAddress());
    ASSERT_EQ("file1.png", msg.getAttachments()[0].getFilename());
    ASSERT_EQ("file2.png", msg.getAttachments()[1].getFilename());
    ASSERT_EQ(2, msg.getAttachmentsCount());
}

TEST(Message_constructor, WithSingleToRecipientAndMinimumData_Success) {
    FakeMessage msg(MessageAddress("test@test.com"),
            { MessageAddress("test2@test.com") },
            "",
            "");
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

TEST(Message_constructor, WithEmptyToArgs_ThrowInvalidArgumentException) {
    try {
        FakeMessage msg(MessageAddress("from@from.com"),
                        {},
                        "TestSubject",
                        "TestBody");
        FAIL();
    }
    catch(std::invalid_argument &err) {
        ASSERT_STREQ("To cannot be empty", err.what());
    }
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

}  // namespace cpp_message
}  // namespace jed_utils_unittest
