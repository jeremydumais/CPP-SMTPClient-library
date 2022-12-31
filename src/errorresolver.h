#ifndef ERRORRESOLVER_H
#define ERRORRESOLVER_H

#ifdef _WIN32
    #ifdef SMTPCLIENT_EXPORTS
        #define ERRORRESOLVER_API __declspec(dllexport)
    #else
        #define ERRORRESOLVER_API __declspec(dllimport)
    #endif
#else
    #define ERRORRESOLVER_API
#endif

namespace jed_utils {
/** @brief The ErrorResolver class is used to translate an error code
 * return be the sendMail method of the differents SMTP client classes
 * to a string representation of the error message.
 */
class ERRORRESOLVER_API ErrorResolver {
 public:
    /**
     *  @brief  Construct a new ErrorResolver.
     *  @param pErrorCode The error code returned by the sendMail method
     *  of the different smtp client classes.
     */
    explicit ErrorResolver(int pErrorCode);

    /** The destructor of ErrorResolver */
    virtual ~ErrorResolver();

    /** ErrorResolver copy constructor */
    ErrorResolver(const ErrorResolver& other);

    /** ErrorResolver copy assignment operator */
    ErrorResolver& operator=(const ErrorResolver& other);

    /** ErrorResolver move constructor */
    ErrorResolver(ErrorResolver&& other) noexcept;

    /** ErrorResolver move assignment operator */
    ErrorResolver& operator=(ErrorResolver&& other) noexcept;

    /** Return the error code configured. */
    int getErrorCode() const;

    /** Return the error message corresponding of the currently set
     *  error code.
     */
    const char *getErrorMessage() const;

 private:
    int mErrorCode;
    char *mErrorMessage = nullptr;
};
}  // namespace jed_utils

#endif
