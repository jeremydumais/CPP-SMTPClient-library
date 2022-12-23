#include <gtest/gtest.h>
#include "../../src/stringutils.h"

using namespace jed_utils;

TEST(TrimLeft, TrimOneSpace) {
    std::string s = " ";
    ASSERT_EQ("", StringUtils::trimLeft(s));
}

TEST(TrimLeft, TrimTwoSpaces) {
    std::string s = "  ";
    ASSERT_EQ("", StringUtils::trimLeft(s));
}

TEST(TrimLeft, TrimWordOneSpaceLeft) {
    std::string s = " Test  ";
    ASSERT_EQ("Test  ", StringUtils::trimLeft(s));
}

TEST(TrimLeft, TrimWordTwoSpacesLeft) {
    std::string s = "  Test  ";
    ASSERT_EQ("Test  ", StringUtils::trimLeft(s));
}

TEST(TrimLeft, TrimTwoWordsTwoSpacesLeft) {
    std::string s = "  Test 123 ";
    ASSERT_EQ("Test 123 ", StringUtils::trimLeft(s));
}

TEST(TrimRight, TrimOneSpace) {
    std::string s = " ";
    ASSERT_EQ("", StringUtils::trimRight(s));
}

TEST(TrimRight, TrimTwoSpaces) {
    std::string s = "  ";
    ASSERT_EQ("", StringUtils::trimRight(s));
}

TEST(TrimRight, TrimWordOneSpaceRight) {
    std::string s = " Test ";
    ASSERT_EQ(" Test", StringUtils::trimRight(s));
}

TEST(TrimRight, TrimWordTwoSpacesRight) {
    std::string s = "  Test  ";
    ASSERT_EQ("  Test", StringUtils::trimRight(s));
}

TEST(TrimRight, TrimTwoWordsTwoSpacesRight) {
    std::string s = "  Test 123  ";
    ASSERT_EQ("  Test 123", StringUtils::trimRight(s));
}

TEST(TrimBoth, TrimOneSpace) {
    std::string s = " ";
    ASSERT_EQ("", StringUtils::trim(s));
}

TEST(TrimBoth, TrimTwoSpaces) {
    std::string s = "  ";
    ASSERT_EQ("", StringUtils::trim(s));
}

TEST(TrimBoth, TrimOneWordTwoSpacesLeftAndRight) {
    std::string s = "  Test  ";
    ASSERT_EQ("Test", StringUtils::trim(s));
}

TEST(TrimBoth, TrimTwoWordsOneSpaceLeftAndRight) {
    std::string s = " Test 123 ";
    ASSERT_EQ("Test 123", StringUtils::trim(s));
}

TEST(TrimBoth, TrimTwoWordsTwoSpacesLeftAndRight) {
    std::string s = "  Test 123  ";
    ASSERT_EQ("Test 123", StringUtils::trim(s));
}

TEST(ToLower, EmptyString) {
    ASSERT_EQ("", StringUtils::toLower(""));
}

TEST(ToLower, OnlySpaces) {
    ASSERT_EQ("  ", StringUtils::toLower("  "));
}

TEST(ToLower, AllCaps) {
    ASSERT_EQ("test", StringUtils::toLower("TEST"));
}

TEST(ToLower, AllLowerCase) {
    ASSERT_EQ("test", StringUtils::toLower("test"));
}

TEST(ToUpper, EmptyString) {
    ASSERT_EQ("", StringUtils::toUpper(""));
}

TEST(ToUpper, OnlySpaces) {
    ASSERT_EQ("  ", StringUtils::toUpper("  "));
}

TEST(ToUpper, AllCaps) {
    ASSERT_EQ("TEST", StringUtils::toUpper("TEST"));
}

TEST(ToUpper, AllLowerCase) {
    ASSERT_EQ("TEST", StringUtils::toUpper("test"));
}
