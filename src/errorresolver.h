#ifndef ERRORRESOLVER_H
#define ERRORRESOLVER_H

#include <string>

namespace jed_utils
{
    class ErrorResolver
    {
    public:
        ErrorResolver(int pErrorCode);
        int getErrorCode() const;
        const std::string &getErrorMessage() const;
    private:
        int mErrorCode;
        std::string mErrorMessage;
    };
}

#endif
