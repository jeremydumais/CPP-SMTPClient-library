#ifndef SSLSMTPCLIENT_H
#define SSLSMTPCLIENT_H

#include "attachment.h"
#include "attachmenterror.h"
#include "communicationerror.h"
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
		int initSession();
		int initClient();
		int initSecureClient();
		int authenticate(const char* pUsername, const char* pPassword);
		int initTLS();
		int startTLSNegotiation();
		int sendMail(const Message &pMsg);
		const char *getCommunicationLog() const;
	protected:
		char *mServerName;
		unsigned int mPort;
		char *mCommunicationLog;
		unsigned int mCommandTimeOut;
		int mLastSocketErrNo;
		int mSock;
		BIO *mBIO;
		SSL_CTX *mCTX;
		SSL *mSSL;
		void cleanup();
		int extractReturnCode(const char *pOutput) const;
		void addCommunicationLogItem(const char *pItem, const char *pPrefix = "c");
		void InitSSL_CTX();
		int sendCommand(const char *pCommand, int pErrorCode, int pTimeoutCode);
		int sendTLSCommand(const char *pCommand, int pErrorCode);
		int sendTLSCommandWithFeedback(const char *pCommand, int pErrorCode, int pTimeoutCode);
		std::string createAttachmentsText(const std::vector<Attachment*> &pAttachments) const;

	};
} // namespace jed_utils

#endif
