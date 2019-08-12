#include <gtest/gtest.h>
#include "../../src/stringutils.h"

using namespace std;
using namespace jed_utils;

TEST(TrimLeft, TrimOneSpace)
{
    string s = " ";
    ASSERT_EQ("", StringUtils::trimLeft(s));
}

TEST(TrimLeft, TrimTwoSpaces)
{
    string s = "  ";
    ASSERT_EQ("", StringUtils::trimLeft(s));
}

TEST(TrimLeft, TrimWordOneSpaceLeft)
{
    string s = " Test  ";
    ASSERT_EQ("Test  ", StringUtils::trimLeft(s));
}

TEST(TrimLeft, TrimWordTwoSpacesLeft)
{
    string s = "  Test  ";
    ASSERT_EQ("Test  ", StringUtils::trimLeft(s));
}

TEST(TrimLeft, TrimTwoWordsTwoSpacesLeft)
{
    string s = "  Test 123 ";
    ASSERT_EQ("Test 123 ", StringUtils::trimLeft(s));
}

TEST(TrimRight, TrimOneSpace)
{
    string s = " ";
    ASSERT_EQ("", StringUtils::trimRight(s));
}

TEST(TrimRight, TrimTwoSpaces)
{
    string s = "  ";
    ASSERT_EQ("", StringUtils::trimRight(s));
}

TEST(TrimRight, TrimWordOneSpaceRight)
{
    string s = " Test ";
    ASSERT_EQ(" Test", StringUtils::trimRight(s));
}

TEST(TrimRight, TrimWordTwoSpacesRight)
{
    string s = "  Test  ";
    ASSERT_EQ("  Test", StringUtils::trimRight(s));
}

TEST(TrimRight, TrimTwoWordsTwoSpacesRight)
{
    string s = "  Test 123  ";
    ASSERT_EQ("  Test 123", StringUtils::trimRight(s));
}

TEST(TrimBoth, TrimOneSpace)
{
    string s = " ";
    ASSERT_EQ("", StringUtils::trim(s));
}

TEST(TrimBoth, TrimTwoSpaces)
{
    string s = "  ";
    ASSERT_EQ("", StringUtils::trim(s));
}

TEST(TrimBoth, TrimOneWordTwoSpacesLeftAndRight)
{
    string s = "  Test  ";
    ASSERT_EQ("Test", StringUtils::trim(s));
}

TEST(TrimBoth, TrimTwoWordsOneSpaceLeftAndRight)
{
    string s = " Test 123 ";
    ASSERT_EQ("Test 123", StringUtils::trim(s));
}

TEST(TrimBoth, TrimTwoWordsTwoSpacesLeftAndRight)
{
    string s = "  Test 123  ";
    ASSERT_EQ("Test 123", StringUtils::trim(s));
}
