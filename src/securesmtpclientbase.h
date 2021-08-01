#ifndef SECURESMTPCLIENTBASE_H
#define SECURESMTPCLIENTBASE_H

#include "smtpclientbase.h"
#include <openssl/ssl.h>

#ifdef _WIN32
	#ifdef SMTPCLIENT_EXPORTS  
		#define SECURESMTPCLIENTBASE_API __declspec(dllexport)   
	#else  
		#define SECURESMTPCLIENTBASE_API __declspec(dllimport)   
	#endif  
#else
	#define SECURESMTPCLIENTBASE_API
#endif

namespace jed_utils
{
	class SECURESMTPCLIENTBASE_API SecureSMTPClientBase : public SMTPClientBase
	{
	public:
    	SecureSMTPClientBase(const char *pServerName, unsigned int pPort);
		~SecureSMTPClientBase();
		SecureSMTPClientBase(const SecureSMTPClientBase& other); //Copy constructor
        SecureSMTPClientBase& operator=(const SecureSMTPClientBase& other); //Copy assignment
		SecureSMTPClientBase(SecureSMTPClientBase&& other) noexcept; //Move constructor
		SecureSMTPClientBase& operator=(SecureSMTPClientBase&& other) noexcept; //Move assignement
	protected:
		//Methods
		void cleanup() override;
		BIO *getBIO() const;
		//Methods used to establish the connection with server
		int getServerSecureIdentification();
		int startTLSNegotiation();
		void initializeSSLContext();
		//Methods to send commands to the server
		int sendCommand(const char *pCommand, int pErrorCode) override;
		int sendCommandWithFeedback(const char *pCommand, int pErrorCode, int pTimeoutCode) override;
	private:
		//Attributes used to communicate with the server
		BIO *mBIO;
		SSL_CTX *mCTX;
		SSL *mSSL;
    };
} // namespace jed_utils

#endif