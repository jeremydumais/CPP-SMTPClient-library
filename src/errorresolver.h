#ifndef ERRORRESOLVER_H
#define ERRORRESOLVER_H

#include <string>

namespace jed_utils
{
    /** @brief The ErrorResolver class is used to translate an error code
     * return be the sendMail method of the differents SMTP client classes 
     * to a string representation of the error message.
     */
    class ErrorResolver
    {
    public:
        /**
		 *  @brief  Construct a new ErrorResolver. 
		 *  @param pErrorCode The error code returned by the sendMail method
         *  of the different smtp client classes.
		 */
        ErrorResolver(int pErrorCode);

		/** Return the error code configured. */
        int getErrorCode() const;

		/** Return the error message corresponding of the currently set
         *  error code. 
         */
        const std::string &getErrorMessage() const;
    private:
        int mErrorCode;
        std::string mErrorMessage;
    };
}

#endif
