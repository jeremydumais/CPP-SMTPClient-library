#ifndef CREDENTIAL_H
#define CREDENTIAL_H

#ifdef _WIN32
    #ifdef SMTPCLIENT_EXPORTS
        #define CREDENTIAL_API __declspec(dllexport)
    #else
        #define CREDENTIAL_API __declspec(dllimport)
    #endif
#else
    #define CREDENTIAL_API
#endif

namespace jed_utils {
/**
 * @brief The RecommendedAuthenticationMethod contains all possible
 * authentication options that developers can indicate for a set
 * of credentials.
 */
enum RecommendedAuthenticationMethod {
  kImplicit = 0,
  kPlain,
  kLogin,
  kXOauth2,
  kPlainClientToken,
  kOAuthBearer,
  kXOAuth
};


/** @brief The Credential class is used to authenticate with the
 *  SMTP server.
 */
class CREDENTIAL_API Credential {
 public:
    /**
     *  @brief  Construct a new Credential.
     *  @param pUsername The user name.
     *  @param pPassword The password.
     */
    Credential(const char *pUsername, const char *pPassword);

   /**
    *  @brief  Construct a new Credential.
    *  @param pUsername The user name.
    *  @param pPassword The password.
    */
    Credential(const char *pUsername,
            const char *pPassword,
            RecommendedAuthenticationMethod authOption);

    /** The destructor og Credential */
    virtual ~Credential();

    /** Credential copy constructor */
    Credential(const Credential& other);

    /** Credential copy assignment operator */
    Credential& operator=(const Credential& other);

    /** Credential move constructor */
    Credential(Credential&& other) noexcept;

    /** Credential move assignment operator */
    Credential& operator=(Credential&& other) noexcept;

    /** Return the username. */
    const char *getUsername() const;

    /** Return the password. */
    const char *getPassword() const;

    /** Returns the recommended authentication option
     * currently set for the credentials. */
    RecommendedAuthenticationMethod getRecommendedAuthOption() const;

    /**
     *  @brief  Set the user name.
     *  @param pUsername A char array pointer of the user name.
     */
    void setUsername(const char *pUsername);

    /**
     *  @brief  Set the password.
     *  @param pPassword A char array pointer of the password.
     */
    void setPassword(const char *pPassword);

    /**
     * @brief Changes the recommended authentication method for this set
     *  of credentials.
     * @param authOption The recommended authentication option that we should
     * use while authenticating the client using the current set of credentials.
     */
    void setRecommendedAuthOption(RecommendedAuthenticationMethod authOption);

 private:
    char *mUsername;
    char *mPassword;
    RecommendedAuthenticationMethod mRecommendedAuthMethod;
};
}  // namespace jed_utils

#endif  // CREDENTIAL_H
