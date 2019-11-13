#ifndef SSLSMTPCLIENT_H
#define SSLSMTPCLIENT_H

#include "attachment.h"
#include "attachmenterror.h"
#include "communicationerror.h"
#include "credential.h"
#include "htmlmessage.h"
#include "messageaddress.h"
#include "plaintextmessage.h"
#include "serverauthoptions.h"
#include <openssl/ssl.h>
#include <string>
#include <vector>

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
	class SSLSMTPCLIENT_API SSLSmtpClient
	{
	public:
		SSLSmtpClient(const char *pServerName, unsigned int pPort);
		virtual ~SSLSmtpClient();
		SSLSmtpClient(const SSLSmtpClient& other); //Copy constructor
        SSLSmtpClient& operator=(const SSLSmtpClient& other); //Copy assignment
		SSLSmtpClient(SSLSmtpClient&& other) noexcept; //Move constructor
		SSLSmtpClient& operator=(SSLSmtpClient&& other) noexcept; //Move assignement
		unsigned int getCommandTimeout() const;
		const char *getCommunicationLog() const;
		const Credential *getCredentials() const;
		const char *getServerName() const;
		unsigned int getServerPort() const;
		int sendMail(const Message &pMsg);
		void setCommandTimeout(unsigned int pTimeOutInSeconds);
		void setCredentials(const Credential &pCredential);
		void setServerName(const char *pServerName);
		void setServerPort(unsigned int pPort);
	protected:
		char *mServerName;
		unsigned int mPort;
		Credential *mCredential;
		char *mCommunicationLog;
		char *mLastServerResponse;
		unsigned int mCommandTimeOut;
		int mLastSocketErrNo;
		ServerAuthOptions *mAuthOptions;
		//Attributes used to communicate with the server
		int mSock;
		BIO *mBIO;
		SSL_CTX *mCTX;
		SSL *mSSL;
		//Methods
		void cleanup();
		int extractReturnCode(const char *pOutput) const;
		void addCommunicationLogItem(const char *pItem, const char *pPrefix = "c");
		//Methods used to establish the connection with server
		int initializeSession();
		int getServerIdentification();
		int getServerSecureIdentification();
		int authenticateClient();
		int authenticateWithMethodPlain();
		int authenticateWithMethodLogin();
		int upgradeToSecureConnection();
		int startTLSNegotiation();
		void initializeSSLContext();
		//Methods to send an email
		int establishConnectionWithServer();
		int setMailRecipients(const Message &pMsg);
		int setMailHeaders(const Message &pMsg);
		int setMailBody(const Message &pMsg);
		//Methods to send commands to the server
		void setLastServerResponse(const char *pResponse);
		int sendRawCommand(const char *pCommand, int pErrorCode, int pTimeoutCode);
		int sendTLSCommand(const char *pCommand, int pErrorCode);
		int sendTLSCommandWithFeedback(const char *pCommand, int pErrorCode, int pTimeoutCode);
		std::string createAttachmentsText(const std::vector<Attachment*> &pAttachments) const;
		static ServerAuthOptions *extractAuthenticationOptions(const char *pEhloOutput);
	};
} // namespace jed_utils

#endif
