#include <gtest/gtest.h>
#include "../../src/errorresolver.h"

using namespace jed_utils;
using namespace std::literals::string_literals;

TEST(ErrorResolver_Constructor, NegativeErrorCode_ReturnValid)
{
    ErrorResolver errorResolver(-1);
}

TEST(ErrorResolver_Constructor, PositiveErrorCode_ReturnValid)
{
    ErrorResolver errorResolver(1);
}

TEST(ErrorResolver_getErrorCode, WithOneOnConstruction_ReturnOne)
{
    ErrorResolver errorResolver(1);
    ASSERT_EQ(1, errorResolver.getErrorCode());
}

TEST(ErrorResolver_getErrorMessage, WithNonExistantCode_ReturnNoMessage)
{
    ErrorResolver errorResolver(0);
    ASSERT_EQ("No message correspond to this error code"s, errorResolver.getErrorMessage());
}

TEST(ErrorResolver_getErrorMessage, WithCodeMinusOne_ReturnValidMessage)
{
    ErrorResolver errorResolver(-1);
    ASSERT_EQ("Unable to create the socket"s, errorResolver.getErrorMessage());
}

TEST(ErrorResolver_getErrorMessage, WithCodeMinusTwo_ReturnValidMessage)
{
    ErrorResolver errorResolver(-2);
    ASSERT_EQ("Unable to connect to the socket"s, errorResolver.getErrorMessage());
}

TEST(ErrorResolver_getErrorMessage, WithCodeMinusThree_ReturnValidMessage)
{
    ErrorResolver errorResolver(-3);
    ASSERT_EQ("The connection attempt has timed out"s, errorResolver.getErrorMessage());
}

TEST(ErrorResolver_getErrorMessage, WithCodeMinusFour_ReturnValidMessage)
{
    ErrorResolver errorResolver(-4);
    ASSERT_EQ("Unable to start WSA (Winsock)"s, errorResolver.getErrorMessage());
}

TEST(ErrorResolver_getErrorMessage, WithCodeMinusFive_ReturnValidMessage)
{
    ErrorResolver errorResolver(-5);
    ASSERT_EQ("Unable to get address info (Winsock)"s, errorResolver.getErrorMessage());
}

TEST(ErrorResolver_getErrorMessage, WithCodeMinusSix_ReturnValidMessage)
{
    ErrorResolver errorResolver(-6);
    ASSERT_EQ("Unable to get host by name"s, errorResolver.getErrorMessage());
}

