// SMTPClient_Test.cpp : Defines the entry point for the console application.
#include <gtest/gtest.h>
#include <iostream>
#include <stdexcept>
#include "../../src/smtpclient.h"

using namespace jed_utils;

int main(int argc, char**argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
