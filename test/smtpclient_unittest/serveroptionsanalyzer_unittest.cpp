#include <gtest/gtest.h>
#include "../../src/serveroptionsanalyzer.h"

using namespace jed_utils;

TEST(ServerOptionsAnalyzer_ContainsAllOptions, WithEmpty_ReturnFalse) {
    ASSERT_FALSE(ServerOptionsAnalyzer::containsAllOptions(""));
}

TEST(ServerOptionsAnalyzer_ContainsAllOptions, With250HypenSTARTTLS_ReturnFALSE) {
    ASSERT_FALSE(ServerOptionsAnalyzer::containsAllOptions("250-STARTTLS"));
}

TEST(ServerOptionsAnalyzer_ContainsAllOptions, With250SpaceSTARTTLS_ReturnTrue) {
    ASSERT_TRUE(ServerOptionsAnalyzer::containsAllOptions("250 STARTTLS"));
}

TEST(ServerOptionsAnalyzer_ContainsAllOptions, With250HypenSTARTTLSrn250SpaceSize_ReturnTrue) {
    ASSERT_TRUE(ServerOptionsAnalyzer::containsAllOptions("250-STARTTLS\r\n250 SIZE 53477376"));
}

TEST(ServerOptionsAnalyzer_ContainsAllOptions, With250HypenSTARTTLSrn250HypenSize_ReturnFalse) {
    ASSERT_FALSE(ServerOptionsAnalyzer::containsAllOptions("250-STARTTLS\r\n250-SIZE 53477376"));
}

TEST(ServerOptionsAnalyzer_ContainsAllOptions, With250HypenSTARTTLSrn250HypenSizern_ReturnTrue) {
    ASSERT_TRUE(ServerOptionsAnalyzer::containsAllOptions("250-STARTTLS\r\n250 SIZE 53477376\r\n"));
}
