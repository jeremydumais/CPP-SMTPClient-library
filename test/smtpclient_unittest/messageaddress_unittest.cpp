#include "../../src/messageaddress.h"
#include <gtest/gtest.h>
#include <stdexcept>

using namespace jed_utils;

TEST(MessageAddress_constructor, EmptyEmailAddrInvalidArgument)
{
    //Test with empty filename
    try
    {
        MessageAddress msg_add("", "");
        FAIL();

    }
    catch (std::invalid_argument)
    {
    }
}

TEST(MessageAddress_constructor, EmptyEmailAddressValidDNThrowInvalidArgument)
{
    try
    {
        MessageAddress msg_add("", "Test Address");
        FAIL();
    }
    catch(std::invalid_argument)
    {
    }
}

TEST(MessageAddress_constructor, WhiteSpacesEmailAddrInvalidArgument)
{
    //Test with empty filename
    try
    {
        MessageAddress msg_add(" ", "");
        FAIL();

    }
    catch (std::invalid_argument)
    {
    }
}

TEST(MessageAddress_constructor, OnlyPrefixEmailAddrInvalidArgument)
{
    //Test with empty filename
    try
    {
        MessageAddress msg_add("test", "");
        FAIL();

    }
    catch (std::invalid_argument)
    {
    }
}

TEST(MessageAddress_constructor, OnlyAtSignEmailAddrInvalidArgument)
{
    //Test with empty filename
    try
    {
        MessageAddress msg_add("@", "");
        FAIL();

    }
    catch (std::invalid_argument)
    {
    }
}

TEST(MessageAddress_constructor, NoSuffixEmailAddrInvalidArgument)
{
    //Test with empty filename
    try
    {
        MessageAddress msg_add("test@", "");
        FAIL();

    }
    catch (std::invalid_argument)
    {
    }
}

TEST(MessageAddress_constructor, NoExtensionEmailAddrValidParam)
{
    MessageAddress msg_add("test@domain", "Test Address");
    ASSERT_STREQ("test@domain", msg_add.getEmailAddress());
    ASSERT_STREQ("Test Address", msg_add.getDisplayName());
}

TEST(MessageAddress_constructor, ValidParam)
{
    MessageAddress msg_add("test@domain.com", "Test Address");
    ASSERT_STREQ("test@domain.com", msg_add.getEmailAddress());
    ASSERT_STREQ("Test Address", msg_add.getDisplayName());
}

TEST(MessageAddress_constructor, ValidParamWithUpperCaseCharEmailAddress)
{
    MessageAddress msg_add("myaddress@gmail.com", "Test Address");
    ASSERT_STREQ("myaddress@gmail.com", msg_add.getEmailAddress());
    ASSERT_STREQ("Test Address", msg_add.getDisplayName());
}

TEST(MessageAddress_CopyConstructor, MessageAddressCopyConstructorValid)
{
    MessageAddress msg_add1("myaddress@gmail.com", "Test Address");
    MessageAddress msg_add2(msg_add1);
    ASSERT_STREQ("myaddress@gmail.com", msg_add1.getEmailAddress());
    ASSERT_STREQ("Test Address", msg_add1.getDisplayName());
    ASSERT_STREQ("myaddress@gmail.com", msg_add2.getEmailAddress());
    ASSERT_STREQ("Test Address", msg_add2.getDisplayName());
}

TEST(MessageAddress_CopyAssignment, MessageAddressCopyAssignmentValid)
{
    MessageAddress msg_add1("test@ccc.com", "123");
    MessageAddress msg_add2("aaa@test.com", "bbb");
    msg_add2 = msg_add1;
    ASSERT_STREQ("test@ccc.com", msg_add1.getEmailAddress());
    ASSERT_STREQ("123", msg_add1.getDisplayName());
    ASSERT_STREQ("test@ccc.com", msg_add2.getEmailAddress());
    ASSERT_STREQ("123", msg_add2.getDisplayName());
}

TEST(MessageAddress_MoveConstructor, MessageAddressMoveConstructorValid)
{
    MessageAddress msg_add1("test@aaa.com", "123");
    MessageAddress msg_add2(std::move(msg_add1));
    ASSERT_STREQ("test@aaa.com", msg_add2.getEmailAddress());
    ASSERT_STREQ("123", msg_add2.getDisplayName());
}

TEST(MessageAddress_MoveAssignment, MessageAddressMoveAssignmentValid)
{
    MessageAddress msg_add1("test@aaa.com", "123");
    MessageAddress msg_add2("aaa@bbb.com", "bbb");
    msg_add2 = std::move(msg_add1);
    ASSERT_STREQ("test@aaa.com", msg_add2.getEmailAddress());
    ASSERT_STREQ("123", msg_add2.getDisplayName());
}

TEST(MessageAddress_get_email_address, validDomain)
{
    MessageAddress msg_add("test@domain.com", "Test Address");
    ASSERT_STREQ("test@domain.com", msg_add.getEmailAddress());
}

TEST(MessageAddress_get_display_name, validDN)
{
    MessageAddress msg_add("test@domain.com", "Test Address");
    ASSERT_STREQ("Test Address", msg_add.getDisplayName());
}

