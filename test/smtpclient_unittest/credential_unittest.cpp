#include "../../src/credential.h"
#include "../../src/cpp/credential.hpp"
#include <gtest/gtest.h>
#include <algorithm>
#include <string>

using namespace jed_utils;

template <typename T>
class MultiCredentialFixture : public ::testing::Test {
 public:
    MultiCredentialFixture<T>()
        : att("test", "123") {
    }
    T att;
};

using MyTypes = ::testing::Types<Credential, cpp::Credential>;
TYPED_TEST_SUITE(MultiCredentialFixture, MyTypes);

TEST(Credential, Constructor_NullUsername) {
    try {
        Credential cred(nullptr, "123");
        FAIL();
    }
    catch(std::invalid_argument &err) {
        ASSERT_STREQ("Username cannot be null or empty", err.what());
    }
}

TYPED_TEST(MultiCredentialFixture, Constructor_EmptyUsername) {
    try {
        TypeParam cred("", "123");
        FAIL();
    }
    catch(std::invalid_argument &err) {
        ASSERT_STREQ("Username cannot be null or empty", err.what());
    }
}

TYPED_TEST(MultiCredentialFixture, Constructor_OnlySpacesUsername) {
    try {
        TypeParam cred("    ", "123");
        FAIL();
    }
    catch(std::invalid_argument &err) {
        ASSERT_STREQ("Username cannot be null or empty", err.what());
    }
}

TEST(Credential, Constructor_NullPassword) {
    try {
        Credential cred("test", nullptr);
        FAIL();
    }
    catch(std::invalid_argument &err) {
        ASSERT_STREQ("Password cannot be null or empty", err.what());
    }
}

TYPED_TEST(MultiCredentialFixture, Constructor_EmptyPassword) {
    try {
        TypeParam cred("test", "");
        FAIL();
    }
    catch(std::invalid_argument &err) {
        ASSERT_STREQ("Password cannot be null or empty", err.what());
    }
}

TYPED_TEST(MultiCredentialFixture, Constructor_ValidOnlySpacesPassword) {
    TypeParam cred("Test3", "   ");
    ASSERT_EQ("Test3", std::string(cred.getUsername()));
    ASSERT_EQ("   ", std::string(cred.getPassword()));
}

TYPED_TEST(MultiCredentialFixture, CopyConstructor_CredentialCopyConstructorValid) {
    TypeParam *cred1 = new TypeParam("test", "123");
    TypeParam cred2(*cred1);
    delete cred1;
    ASSERT_EQ("test", std::string(cred2.getUsername()));
    ASSERT_EQ("123", std::string(cred2.getPassword()));
}

TYPED_TEST(MultiCredentialFixture, CopyAssignment_CredentialCopyAssignmentValid) {
    TypeParam *cred1 = new TypeParam("test", "123");
    TypeParam cred2("aaa", "bbb");
    cred2 = *cred1;
    delete cred1;
    ASSERT_EQ("test", std::string(cred2.getUsername()));
    ASSERT_EQ("123", std::string(cred2.getPassword()));
}

TYPED_TEST(MultiCredentialFixture, MoveConstructor_CredentialMoveConstructorValid) {
    TypeParam cred1("test", "123");
    TypeParam cred2(std::move(cred1));
    ASSERT_EQ("test", std::string(cred2.getUsername()));
    ASSERT_EQ("123", std::string(cred2.getPassword()));
}

TYPED_TEST(MultiCredentialFixture, MoveAssignment_CredentialMoveAssignmentValid) {
    TypeParam cred1("test", "123");
    TypeParam cred2("aaa", "bbb");
    cred2 = std::move(cred1);
    ASSERT_EQ("test", std::string(cred2.getUsername()));
    ASSERT_EQ("123", std::string(cred2.getPassword()));
}

TYPED_TEST(MultiCredentialFixture, getUsername_ValidUsername) {
    TypeParam cred("Test3", "123");
    ASSERT_EQ("Test3", std::string(cred.getUsername()));
}

TYPED_TEST(MultiCredentialFixture, getPassword_ValidPassword) {
    TypeParam cred("Test3", "123");
    ASSERT_EQ("123", std::string(cred.getPassword()));
}

TYPED_TEST(MultiCredentialFixture, setUsername_ValidUsername) {
    TypeParam cred("Test3", "123");
    cred.setUsername("Test4");
    ASSERT_EQ("Test4", std::string(cred.getUsername()));
}

TEST(Credential, setUsername_NullUsername) {
    Credential cred("Test", "123");
    try {
        cred.setUsername(nullptr);
        FAIL();
    }
    catch(std::invalid_argument &err) {
        ASSERT_STREQ("Username cannot be null or empty", err.what());
    }
}

TYPED_TEST(MultiCredentialFixture, setUsername_EmptyUsername) {
    TypeParam cred("Test", "123");
    try {
        cred.setUsername("");
        FAIL();
    }
    catch(std::invalid_argument &err) {
        ASSERT_STREQ("Username cannot be null or empty", err.what());
    }
}

TYPED_TEST(MultiCredentialFixture, setUsername_OnlySpacesUsername) {
    TypeParam cred("Test", "123");
    try {
        cred.setUsername("    ");
        FAIL();
    }
    catch(std::invalid_argument &err) {
        ASSERT_STREQ("Username cannot be null or empty", err.what());
    }
}

TYPED_TEST(MultiCredentialFixture, setPassword_ValidPassword) {
    TypeParam cred("Test3", "123");
    cred.setPassword("432");
    ASSERT_EQ("432", std::string(cred.getPassword()));
}

TEST(Credential, setPassword_NullPassword) {
    Credential cred("Test", "123");
    try {
        cred.setPassword(nullptr);
        FAIL();
    }
    catch(std::invalid_argument &err) {
        ASSERT_STREQ("Password cannot be null or empty", err.what());
    }
}

TYPED_TEST(MultiCredentialFixture, setPassword_EmptyPassword) {
    TypeParam cred("Test", "123");
    try {
        cred.setPassword("");
        FAIL();
    }
    catch(std::invalid_argument &err) {
        ASSERT_STREQ("Password cannot be null or empty", err.what());
    }
}

TYPED_TEST(MultiCredentialFixture, setPassword_ValidOnlySpacesPassword) {
    TypeParam cred("Test3", "123");
    cred.setPassword("   ");
    ASSERT_EQ("   ", std::string(cred.getPassword()));
}

TYPED_TEST(MultiCredentialFixture, RecommendedAuthenticationModeImplicit) {
    TypeParam cred{"Test", "123"};
    ASSERT_EQ("Test", std::string{cred.getUsername()});
    ASSERT_EQ("123", std::string{cred.getPassword()});
    ASSERT_EQ(RecommendedAuthenticationMethod::kImplicit,
        cred.getRecommendedAuthOption());

    std::vector<RecommendedAuthenticationMethod> methods{
        RecommendedAuthenticationMethod::kPlain,
        RecommendedAuthenticationMethod::kLogin,
        RecommendedAuthenticationMethod::kXOauth2,
        RecommendedAuthenticationMethod::kPlainClientToken,
        RecommendedAuthenticationMethod::kOAuthBearer,
        RecommendedAuthenticationMethod::kXOAuth,
    };

    std::for_each(methods.cbegin(), methods.cend(),
        [cred](auto method) mutable {
            cred.setRecommendedAuthOption(method);
            ASSERT_EQ(method, cred.getRecommendedAuthOption());

            TypeParam newCred{cred};
            ASSERT_EQ(method, newCred.getRecommendedAuthOption());

            TypeParam newCred2 = cred;
            ASSERT_EQ(method, newCred2.getRecommendedAuthOption());

            TypeParam movedCred{std::move(newCred)};
            ASSERT_EQ(method, movedCred.getRecommendedAuthOption());

            TypeParam movedCred2 = std::move(movedCred);
            ASSERT_EQ(method, movedCred.getRecommendedAuthOption());
        });
}

TYPED_TEST(MultiCredentialFixture, RecommendedAuthenticationModeSpecified) {
    std::vector<RecommendedAuthenticationMethod> methods{
        RecommendedAuthenticationMethod::kPlain,
        RecommendedAuthenticationMethod::kLogin,
        RecommendedAuthenticationMethod::kXOauth2,
        RecommendedAuthenticationMethod::kPlainClientToken,
        RecommendedAuthenticationMethod::kOAuthBearer,
        RecommendedAuthenticationMethod::kXOAuth,
    };

    std::for_each(methods.cbegin(), methods.cend(),
        [](auto method) {
            TypeParam cred{"Test", "123", method};
            ASSERT_EQ("Test", std::string{cred.getUsername()});
            ASSERT_EQ("123", std::string{cred.getPassword()});
            ASSERT_EQ(method, cred.getRecommendedAuthOption());
        });
}
