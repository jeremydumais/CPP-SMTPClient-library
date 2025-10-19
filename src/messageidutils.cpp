#include <algorithm>
#include <atomic>
#include <chrono>
#include <cstdint>
#include <random>
#include <stdexcept>
#include <string>
#include "messageidutils.h"

#if defined(_WIN32)
    #include <windows.h>
#else
    #include <unistd.h>
    #include <sys/types.h>
#endif

namespace jed_utils {

std::string MessageIDUtils::generate(const std::string& rhs,
                                bool includeAngleBrackets,
                                bool strictRhsCheck) {
    if (strictRhsCheck && !rhsLooksOk(rhs))
        throw std::invalid_argument("MessageIDUtils::generate: RHS contains invalid characters");

    std::string lhs = generateLhs();
    std::string core = lhs + "@" + rhs;
    return includeAngleBrackets ? ("<" + core + ">") : core;
}

std::string MessageIDUtils::generateLhs() {
    const auto micros = std::chrono::duration_cast<std::chrono::microseconds>(
            std::chrono::system_clock::now().time_since_epoch()).count();
    const uint32_t pid = getPid();
    const uint64_t ctr = counter().fetch_add(1, std::memory_order_relaxed);
    const std::string rnd = random128Base36();

    std::string lhs;
    lhs.reserve(64);
    lhs.append(toBase36(static_cast<uint64_t>(micros)));
    lhs.push_back('.');
    lhs.append(toBase36(static_cast<uint64_t>(pid)));
    lhs.push_back('.');
    lhs.append(toBase36(ctr));
    lhs.push_back('.');
    lhs.append(rnd);
    return lhs;
}

uint32_t MessageIDUtils::getPid() {
    #if defined(_WIN32)
        return static_cast<uint32_t>(GetCurrentProcessId());
    #else
        return static_cast<uint32_t>(getpid());
    #endif
}

std::atomic<uint64_t>& MessageIDUtils::counter() {
    static std::atomic<uint64_t> c {
        static_cast<uint64_t>(std::random_device {}()) ^
            static_cast<uint64_t>(
                    std::chrono::high_resolution_clock::now().time_since_epoch().count())
    };
    return c;
}

std::string MessageIDUtils::toBase36(uint64_t v) {
    static const char* digits = "0123456789abcdefghijklmnopqrstuvwxyz";
    if (v == 0) return "0";
    std::string out;
    while (v) {
        out.push_back(digits[v % 36]);
        v /= 36;
    }
    std::reverse(out.begin(), out.end());
    return out;
}

uint64_t MessageIDUtils::rand64() {
    static thread_local std::mt19937_64 rng([] {
        uint64_t seed = (static_cast<uint64_t>(std::random_device{}()) << 1) ^
            static_cast<uint64_t>(
                std::chrono::high_resolution_clock::now().time_since_epoch().count());
        seed ^= reinterpret_cast<uintptr_t>(&seed);
        return std::mt19937_64(seed);
        }());
    return rng();
}

std::string MessageIDUtils::random128Base36() {
    const uint64_t a = rand64();
    const uint64_t b = rand64();
    return toBase36(a) + toBase36(b);
}

bool MessageIDUtils::rhsLooksOk(const std::string& rhs) {
    if (rhs.empty()) return false;
    return std::all_of(rhs.begin(), rhs.end(), [](unsigned char c) {
        return std::isalnum(c) || c == '.' || c == '-' || c == '[' || c == ']' || c == ':';
    });
}

}  // namespace jed_utils
