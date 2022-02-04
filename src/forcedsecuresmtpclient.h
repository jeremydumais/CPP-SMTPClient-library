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
	/** @brief The ForcedSecureSMTPClient is useful to communicate with legacy 
	 *  systems which requires that the communication be encrypted from the 
	 *  initial connection. The communication is usually done via port 465.
	 */
	class FORCEDSECURESMTPCLIENT_API ForcedSecureSMTPClient : public SecureSMTPClientBase
	{
	public:
		/**
		 *  @brief  Construct a new ForcedSecureSMTPClient. 
		 *  @param pFilename The full path of the file.
		 *  @param pName The display name of the file that will appear in 
		 *  the mail content  
		 */
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
