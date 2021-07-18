#ifndef IMPLICITSSLSMTPCLIENT_H
#define IMPLICITSSLSMTPCLIENT_H

#include "smtpclientbase.h"
#include <openssl/ssl.h>

#ifdef _WIN32
	#ifdef SMTPCLIENT_EXPORTS  
		#define IMPLICITSSLSMTPCLIENT_API __declspec(dllexport)   
	#else  
		#define IMPLICITSSLSMTPCLIENT_API __declspec(dllimport)   
	#endif  
#else
	#define IMPLICITSSLSMTPCLIENT_API
#endif

namespace jed_utils
{
	class IMPLICITSSLSMTPCLIENT_API ImplicitSSLSmtpClient : public SmtpClientBase
	{
	public:
		ImplicitSSLSmtpClient(const char *pServerName, unsigned int pPort);
		~ImplicitSSLSmtpClient();
		ImplicitSSLSmtpClient(const ImplicitSSLSmtpClient& other); //Copy constructor
        ImplicitSSLSmtpClient& operator=(const ImplicitSSLSmtpClient& other); //Copy assignment
		ImplicitSSLSmtpClient(ImplicitSSLSmtpClient&& other) noexcept; //Move constructor
		ImplicitSSLSmtpClient& operator=(ImplicitSSLSmtpClient&& other) noexcept; //Move assignement
	protected:
		//Attributes used to communicate with the server
		BIO *mBIO;
		SSL_CTX *mCTX;
		SSL *mSSL;
		//Methods
		void cleanup() override;
		//Methods used to establish the connection with server
		int establishConnectionWithServer() override;
		int getServerSecureIdentification();
		//int upgradeToSecureConnection();
		int startTLSNegotiation();
		void initializeSSLContext();
		//Methods to send commands to the server
		int sendCommand(const char *pCommand, int pErrorCode) override;
		int sendCommandWithFeedback(const char *pCommand, int pErrorCode, int pTimeoutCode) override;
	};
} // namespace jed_utils

#endif
