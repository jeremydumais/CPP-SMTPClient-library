#ifndef IMPLICITSSLSMTPCLIENT_H
#define IMPLICITSSLSMTPCLIENT_H

#include "securesmtpclientbase.h"

#ifdef _WIN32
	#ifdef SMTPCLIENT_EXPORTS  
		#define FORCEDSECURESMTPCLIENT_API __declspec(dllexport)   
	#else  
		#define FORCEDSECURESMTPCLIENT_API __declspec(dllimport)   
	#endif  
#else
	#define FORCEDSECURESMTPCLIENT_API
#endif

namespace jed_utils
{
	class FORCEDSECURESMTPCLIENT_API ForcedSecureSMTPClient : public SecureSMTPClientBase
	{
	public:
		ForcedSecureSMTPClient(const char *pServerName, unsigned int pPort);
		~ForcedSecureSMTPClient() = default;
		ForcedSecureSMTPClient(const ForcedSecureSMTPClient& other) = default; //Copy constructor
        ForcedSecureSMTPClient& operator=(const ForcedSecureSMTPClient& other); //Copy assignment
		ForcedSecureSMTPClient(ForcedSecureSMTPClient&& other) noexcept; //Move constructor
		ForcedSecureSMTPClient& operator=(ForcedSecureSMTPClient&& other) noexcept; //Move assignement
	protected:
		int establishConnectionWithServer() override;
		int checkServerGreetings() override;
	};
} // namespace jed_utils

#endif
