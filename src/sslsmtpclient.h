#ifndef SSLSMTPCLIENT_H
#define SSLSMTPCLIENT_H

#include "smtpclientbase.h"
#include <openssl/ssl.h>

#ifdef _WIN32
	#ifdef SMTPCLIENT_EXPORTS  
		#define SSLSMTPCLIENT_API __declspec(dllexport)   
	#else  
		#define SSLSMTPCLIENT_API __declspec(dllimport)   
	#endif  
#else
	#define SSLSMTPCLIENT_API
#endif

namespace jed_utils
{
	class SSLSMTPCLIENT_API SSLSmtpClient : public SmtpClientBase
	{
	public:
		SSLSmtpClient(const char *pServerName, unsigned int pPort);
		~SSLSmtpClient();
		SSLSmtpClient(const SSLSmtpClient& other); //Copy constructor
        SSLSmtpClient& operator=(const SSLSmtpClient& other); //Copy assignment
		SSLSmtpClient(SSLSmtpClient&& other) noexcept; //Move constructor
		SSLSmtpClient& operator=(SSLSmtpClient&& other) noexcept; //Move assignement
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
		int upgradeToSecureConnection();
		int startTLSNegotiation();
		void initializeSSLContext();
		//Methods to send commands to the server
		int sendCommand(const char *pCommand, int pErrorCode) override;
		int sendCommandWithFeedback(const char *pCommand, int pErrorCode, int pTimeoutCode) override;
	};
} // namespace jed_utils

#endif
