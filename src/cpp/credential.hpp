#ifndef CPPCREDENTIAL_H
#define CPPCREDENTIAL_H

#ifdef _WIN32
    #ifdef SMTPCLIENT_EXPORTS
        #define CPP_CREDENTIAL_API __declspec(dllexport)
    #else
        #define CPP_CREDENTIAL_API __declspec(dllimport)
    #endif
#else
    #define CPP_CREDENTIAL_API
#endif

#include <string>
#include "../credential.h"

namespace jed_utils {
namespace cpp {
/** @brief The Credential class is used to authenticate with the
 *  SMTP server.
 */
class CPP_CREDENTIAL_API Credential : private jed_utils::Credential {
 public:
    /**
     *  @brief  Construct a new Credential.
     *  @param pUsername The user name.
     *  @param pPassword The password.
     */
    Credential(const std::string &pUsername, const std::string &pPassword);

    /**
     *  @brief  Construct a new Credential.
     *  @param pUsername The user name.
     *  @param pPassword The password.
     */
    Credential(const std::string &pUsername, const std::string &pPassword,
      RecommendedAuthenticationMethod authOption);

    /** The destructor og Credential */
    ~Credential() override = default;

    /** Credential copy constructor */
    Credential(const Credential& other) = default;

    /** Credential copy assignment operator */
    Credential& operator=(const Credential& other) = default;

    /** Credential move constructor */
    Credential(Credential&& other) noexcept = default;

    /** Credential move assignment operator */
    Credential& operator=(Credential&& other) noexcept = default;

    /** Return the username. */
    std::string getUsername() const;

    /** Return the password. */
    std::string getPassword() const;

    /** Returns the recommended authentication option
     * currently set for the credentials. */
    RecommendedAuthenticationMethod getRecommendedAuthOption() const;

    /**
     *  @brief  Set the user name.
     *  @param pUsername A char array pointer of the user name.
     */
    void setUsername(const std::string &pUsername);

    /**
     *  @brief  Set the password.
     *  @param pPassword A char array pointer of the password.
     */
    void setPassword(const std::string &pPassword);

    /**
     * @brief Changes the recommended authentication method for this set
     *  of credentials.
     * @param authOption The recommended authentication option that we should use
     *  while authenticating the client using the current set of credentials.
     */
    void setRecommendedAuthOption(RecommendedAuthenticationMethod authOption);
};
}  // namespace cpp
}  // namespace jed_utils

#endif
