#include <gtest/gtest.h>
#include <cstdint>
#include <regex>
#include <string>
#include <unordered_set>
#include "../../src/messageidutils.h"

#if defined(_WIN32)
    #include <windows.h>
#else
    #include <unistd.h>
#endif

using namespace jed_utils;

// ---------- small helpers ----------
static std::string toBase36(uint64_t v) {
    static const char* digits = "0123456789abcdefghijklmnopqrstuvwxyz";
    if (v == 0) return "0";
    std::string out;
    while (v) {
        out.push_back(digits[v % 36]); v /= 36;
    }
    std::reverse(out.begin(), out.end());
    return out;
}

static uint32_t getPidPortable() {
#if defined(_WIN32)
    return static_cast<uint32_t>(::GetCurrentProcessId());
#else
    return static_cast<uint32_t>(::getpid());
#endif
}


// LHS regex: four dot-separated base36 segments
static const std::regex kLhsRegex() {
   return std::regex("^([a-z0-9]+\\.){3}[a-z0-9]+$");
}

// Full Message-ID regex with brackets and RHS hotmail.com
static const std::regex kFullHotmailRegex() {
    return std::regex("^<([a-z0-9]+\\.){3}[a-z0-9]+@hotmail\\.com>$");
}

// Full Message-ID regex without brackets (hotmail.com)
static const std::regex kNoBracketsHotmailRegex() {
    return std::regex("^([a-z0-9]+\\.){3}[a-z0-9]+@hotmail\\.com$");
}

TEST(MessageIDUtils_Generate, WithHotmailAndBrackets_StrictOK_FormatMatches) {
    const std::string id = MessageIDUtils::generate("hotmail.com", /*includeAngleBrackets=*/true, /*strictRhsCheck=*/true);
    ASSERT_TRUE(std::regex_match(id, kFullHotmailRegex())) << id;
}

TEST(MessageIDUtils_Generate, WithHotmail_NoBrackets_StrictOK_FormatMatches) {
    const std::string id = MessageIDUtils::generate("hotmail.com", /*includeAngleBrackets=*/false, /*strictRhsCheck=*/true);
    ASSERT_TRUE(std::regex_match(id, kNoBracketsHotmailRegex())) << id;
    ASSERT_EQ(id.find('<'), std::string::npos);
    ASSERT_EQ(id.find('>'), std::string::npos);
}

TEST(MessageIDUtils_Generate, StrictRhsCheck_RejectsInvalidRhs) {
    // space makes RHS invalid for strict check
    EXPECT_THROW({
        (void)MessageIDUtils::generate("bad host", true, /*strictRhsCheck=*/true);
    }, std::invalid_argument);
}

TEST(MessageIDUtils_Generate, AcceptsDomainLiteralIPv6_WhenStrict) {
    const std::string rhs = "[IPv6:2001:db8::1]";
    const std::string id = MessageIDUtils::generate(rhs, /*includeAngleBrackets=*/true, /*strictRhsCheck=*/true);
    // basic containment checks
    ASSERT_FALSE(id.empty());
    ASSERT_NE(id.find(rhs), std::string::npos) << id;
    ASSERT_EQ(id.front(), '<');
    ASSERT_EQ(id.back(), '>');
    // ensure exactly one '@'
    ASSERT_EQ(std::count(id.begin(), id.end(), '@'), 1);
}

TEST(MessageIDUtils_Generate, EmptyRhs_NonStrict_GeneratesButEndsWithAt) {
    const std::string id = MessageIDUtils::generate("", /*includeAngleBrackets=*/false, /*strictRhsCheck=*/false);
    ASSERT_FALSE(id.empty());
    // LHS present and then '@' as last char
    ASSERT_EQ(id.back(), '@') << id;
}

TEST(MessageIDUtils_Generate, ManySequential_AreUnique) {
    std::unordered_set<std::string> seen;
    seen.reserve(2000);
    for (int i = 0; i < 2000; ++i) {
        seen.insert(MessageIDUtils::generate("hotmail.com", false, false));
    }
    ASSERT_EQ(seen.size(), 2000u);
}

TEST(MessageIDUtils_GenerateLhs, Shape_IsFourBase36Segments) {
    const std::string lhs = MessageIDUtils::generateLhs();
    ASSERT_TRUE(std::regex_match(lhs, kLhsRegex())) << lhs;

    // Split and inspect the second segment equals PID in base36
    size_t p1 = lhs.find('.');
    ASSERT_NE(p1, std::string::npos);
    size_t p2 = lhs.find('.', p1 + 1);
    ASSERT_NE(p2, std::string::npos);
    const std::string seg_pid = lhs.substr(p1 + 1, p2 - (p1 + 1));

    const auto pid36 = toBase36(static_cast<uint64_t>(getPidPortable()));
    ASSERT_EQ(seg_pid, pid36) << "Expected PID segment " << pid36 << " but got " << seg_pid << " in LHS: " << lhs;
}

TEST(MessageIDUtils_GenerateLhs, SuccessiveCalls_Differ) {
    const std::string a = MessageIDUtils::generateLhs();
    const std::string b = MessageIDUtils::generateLhs();
    ASSERT_NE(a, b);
}
