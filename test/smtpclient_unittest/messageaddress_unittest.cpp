#include "../../src/messageaddress.h"
#include "../../src/cpp/messageaddress.hpp"
#include <gtest/gtest.h>
#include <stdexcept>

using namespace jed_utils;

template <typename T>
class MultiMessageAddressFixture : public ::testing::Test {
 public:
    MultiMessageAddressFixture<T>()
        : msg_add("test@domain", "Test Address") {
    }
    T msg_add;
};

using MyTypes = ::testing::Types<MessageAddress, cpp::MessageAddress>;
TYPED_TEST_SUITE(MultiMessageAddressFixture, MyTypes);

TYPED_TEST(MultiMessageAddressFixture, constructor_EmptyEmailAddrInvalidArgument) {
    // Test with empty filename
    try {
        TypeParam msg_add("", "");
        FAIL();
    }
    catch (std::invalid_argument) {
    }
}

TYPED_TEST(MultiMessageAddressFixture, constructor_EmptyEmailAddressValidDNThrowInvalidArgument) {
    try {
        TypeParam msg_add("", "Test Address");
        FAIL();
    }
    catch(std::invalid_argument) {
    }
}

TYPED_TEST(MultiMessageAddressFixture, constructor_WhiteSpacesEmailAddrInvalidArgument) {
    // Test with empty filename
    try {
        TypeParam msg_add(" ", "");
        FAIL();
    }
    catch (std::invalid_argument) {
    }
}

TYPED_TEST(MultiMessageAddressFixture, constructor_OnlyPrefixEmailAddrInvalidArgument) {
    // Test with empty filename
    try {
        TypeParam msg_add("test", "");
        FAIL();
    }
    catch (std::invalid_argument) {
    }
}

TYPED_TEST(MultiMessageAddressFixture, constructor_OnlyAtSignEmailAddrInvalidArgument) {
    // Test with empty filename
    try {
        TypeParam msg_add("@", "");
        FAIL();
    }
    catch (std::invalid_argument) {
    }
}

TYPED_TEST(MultiMessageAddressFixture, constructor_NoSuffixEmailAddrInvalidArgument) {
    // Test with empty filename
    try {
        TypeParam msg_add("test@", "");
        FAIL();
    }
    catch (std::invalid_argument) {
    }
}

TYPED_TEST(MultiMessageAddressFixture, constructor_NoExtensionEmailAddrValidParam) {
    TypeParam msg_add("test@domain", "Test Address");
    ASSERT_EQ("test@domain", std::string(msg_add.getEmailAddress()));
    ASSERT_EQ("Test Address", std::string(msg_add.getDisplayName()));
}

TYPED_TEST(MultiMessageAddressFixture, constructor_ValidParam) {
    TypeParam msg_add("test@domain.com", "Test Address");
    ASSERT_EQ("test@domain.com", std::string(msg_add.getEmailAddress()));
    ASSERT_EQ("Test Address", std::string(msg_add.getDisplayName()));
}

TYPED_TEST(MultiMessageAddressFixture, constructor_ValidParamWithUpperCaseCharEmailAddress) {
    TypeParam msg_add("myaddress@gmail.com", "Test Address");
    ASSERT_EQ("myaddress@gmail.com", std::string(msg_add.getEmailAddress()));
    ASSERT_EQ("Test Address", std::string(msg_add.getDisplayName()));
}

TYPED_TEST(MultiMessageAddressFixture, CopyConstructor_MessageAddressCopyConstructorValid) {
    TypeParam msg_add1("myaddress@gmail.com", "Test Address");
    TypeParam msg_add2(msg_add1);
    ASSERT_EQ("myaddress@gmail.com", std::string(msg_add1.getEmailAddress()));
    ASSERT_EQ("Test Address", std::string(msg_add1.getDisplayName()));
    ASSERT_EQ("myaddress@gmail.com", std::string(msg_add2.getEmailAddress()));
    ASSERT_EQ("Test Address", std::string(msg_add2.getDisplayName()));
}

TYPED_TEST(MultiMessageAddressFixture, CopyAssignment_MessageAddressCopyAssignmentValid) {
    TypeParam msg_add1("test@ccc.com", "123");
    TypeParam msg_add2("aaa@test.com", "bbb");
    msg_add2 = msg_add1;
    ASSERT_EQ("test@ccc.com", std::string(msg_add1.getEmailAddress()));
    ASSERT_EQ("123", std::string(msg_add1.getDisplayName()));
    ASSERT_EQ("test@ccc.com", std::string(msg_add2.getEmailAddress()));
    ASSERT_EQ("123", std::string(msg_add2.getDisplayName()));
}

TYPED_TEST(MultiMessageAddressFixture, MoveConstructor_MessageAddressMoveConstructorValid) {
    TypeParam msg_add1("test@aaa.com", "123");
    TypeParam msg_add2(std::move(msg_add1));
    ASSERT_EQ("test@aaa.com", std::string(msg_add2.getEmailAddress()));
    ASSERT_EQ("123", std::string(msg_add2.getDisplayName()));
}

TYPED_TEST(MultiMessageAddressFixture, MoveAssignment_MessageAddressMoveAssignmentValid) {
    TypeParam msg_add1("test@aaa.com", "123");
    TypeParam msg_add2("aaa@bbb.com", "bbb");
    msg_add2 = std::move(msg_add1);
    ASSERT_EQ("test@aaa.com", std::string(msg_add2.getEmailAddress()));
    ASSERT_EQ("123", std::string(msg_add2.getDisplayName()));
}

TYPED_TEST(MultiMessageAddressFixture, get_email_address_validDomain) {
    TypeParam msg_add("test@domain.com", "Test Address");
    ASSERT_EQ("test@domain.com", std::string(msg_add.getEmailAddress()));
}

TYPED_TEST(MultiMessageAddressFixture, get_display_name_validDN) {
    TypeParam msg_add("test@domain.com", "Test Address");
    ASSERT_EQ("Test Address", std::string(msg_add.getDisplayName()));
}

