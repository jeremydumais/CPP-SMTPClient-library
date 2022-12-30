#include "../../src/cpp/plaintextmessage.hpp"
#include <gtest/gtest.h>

using namespace jed_utils::cpp;

namespace jed_utils_unittest {
namespace cpp_plaintextmessage {

TEST(PlaintextMessage_Constructor, WithValidArgs_ReturnSuccess) {
    PlaintextMessage msg(MessageAddress("from@from.com"),
                   { MessageAddress("to1@to.com"), MessageAddress("to2@to.com") },
                   "Subject",
                   "Body",
                   { MessageAddress("cc1@cc.com"), MessageAddress("cc2@cc.com") },
                   { MessageAddress("bcc1@bcc.com"), MessageAddress("bcc2@bcc.com") },
                   { Attachment("file1.png"), Attachment("file2.png") });
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

TEST(PlaintextMessage_GetMimeType, ReturnTextPlaintext) {
    PlaintextMessage msg(MessageAddress("from@from.com"),
                    { MessageAddress("to@to.com") },
                    "Subject",
                    "Body");
    ASSERT_EQ("text/plain", msg.getMimeType());
}

}  // namespace cpp_plainmessage
}  // namespace jed_utils_unittest
