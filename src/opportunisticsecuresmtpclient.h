#ifndef OPPORTUNISTICSECURESMTPCLIENT_H
#define OPPORTUNISTICSECURESMTPCLIENT_H

#include "securesmtpclientbase.h"

#ifdef _WIN32
	#ifdef SMTPCLIENT_EXPORTS  
		#define OPPORTUNISTICSECURESMTPCLIENT_API __declspec(dllexport)   
	#else  
		#define OPPORTUNISTICSECURESMTPCLIENT_API __declspec(dllimport)   
	#endif  
#else
	#define OPPORTUNISTICSECURESMTPCLIENT_API
#endif

namespace jed_utils
{
	class OPPORTUNISTICSECURESMTPCLIENT_API OpportunisticSecureSMTPClient : public SecureSMTPClientBase
	{
	public:
		OpportunisticSecureSMTPClient(const char *pServerName, unsigned int pPort);
		~OpportunisticSecureSMTPClient() = default;
		OpportunisticSecureSMTPClient(const OpportunisticSecureSMTPClient& other) = default; //Copy constructor
        OpportunisticSecureSMTPClient& operator=(const OpportunisticSecureSMTPClient& other); //Copy assignment
		OpportunisticSecureSMTPClient(OpportunisticSecureSMTPClient&& other) noexcept; //Move constructor
		OpportunisticSecureSMTPClient& operator=(OpportunisticSecureSMTPClient&& other) noexcept; //Move assignement
	protected:
		int establishConnectionWithServer() override;
		int upgradeToSecureConnection();
		static bool isStartTLSSupported(const char *pServerResponse);
	};
} // namespace jed_utils


#endif
