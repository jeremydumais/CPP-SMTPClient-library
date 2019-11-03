#ifndef SSLSMTPCLIENT_H
#define SSLSMTPCLIENT_H

#include "attachment.h"
#include "attachmenterror.h"
#include "communicationerror.h"
#include "credential.h"
#include "htmlmessage.h"
#include "messageaddress.h"
#include "plaintextmessage.h"
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
		//All Move dans Copy Constr
		int sendMail(const Message &pMsg);
		void setCredentials(const Credential &pCredential);
		void setCommandTimeout(unsigned int pTimeOutInSeconds);
		const char *getCommunicationLog() const;
		const Credential *getCredentials() const;
		unsigned int getCommandTimeout() const;
	protected:
		char *mServerName;
		unsigned int mPort;
		Credential *mCredential;
		char *mCommunicationLog;
		unsigned int mCommandTimeOut;
		int mLastSocketErrNo;
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
		int upgradeToSecureConnection();
		int startTLSNegotiation();
		void initializeSSLContext();
		//Methods to send an email
		int establishConnectionWithServer();
		int setMailRecipients(const Message &pMsg);
		int setMailHeaders(const Message &pMsg);
		int setMailBody(const Message &pMsg);
		//Methods to send commands to the server
		int sendRawCommand(const char *pCommand, int pErrorCode, int pTimeoutCode);
		int sendTLSCommand(const char *pCommand, int pErrorCode);
		int sendTLSCommandWithFeedback(const char *pCommand, int pErrorCode, int pTimeoutCode);
		std::string createAttachmentsText(const std::vector<Attachment*> &pAttachments) const;
	};
} // namespace jed_utils

#endif
