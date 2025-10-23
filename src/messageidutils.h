#ifndef MESSAGEIDUTILS_H
#define MESSAGEIDUTILS_H

#include <atomic>
#include <cstdint>
#include <string>

#ifdef _WIN32
    #ifdef SMTPCLIENT_STATIC
        #define MESSAGEIDUTILS_API
    #elif defined(SMTPCLIENT_EXPORTS)
        #define MESSAGEIDUTILS_API __declspec(dllexport)
    #else
        #define MESSAGEIDUTILS_API __declspec(dllimport)
    #endif
#else
    #define MESSAGEIDUTILS_API
#endif

namespace jed_utils {

class MESSAGEIDUTILS_API MessageIDUtils {
 public:
    // Generate a complete Message-ID string, e.g. "<abc.def.ghi.jkl@domain>"
    static std::string generate(const std::string& rhs,
                                bool includeAngleBrackets = true,
                                bool strictRhsCheck = false);
    // Generate only the LHS portion (dot-atom safe)
    static std::string generateLhs();

 private:
    // --- platform-specific PID ---
    static uint32_t getPid();
    // --- atomic counter (process-wide) ---
    static std::atomic<uint64_t>& counter();
    // --- convert integer to base36 (a-z0-9) ---
    static std::string toBase36(uint64_t v);
    // --- thread-local RNG, seeded once per thread ---
    static uint64_t rand64();
    // --- 128-bit random number encoded in base36 ---
    static std::string random128Base36();
    // --- basic RHS validator (optional strict mode) ---
    static bool rhsLooksOk(const std::string& rhs);
};

}  // namespace jed_utils

#endif  // MESSAGEIDUTILS_H

