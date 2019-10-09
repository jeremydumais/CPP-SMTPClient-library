#ifndef SSLSMTPCLIENT_H
#define SSLSMTPCLIENT_H

#include "attachment.h"
#include "attachmenterror.h"
#include "communicationerror.h"
#include "htmlmessage.h"
#include "messageaddress.h"
#include "plaintextmessage.h"
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
		int initSession(const unsigned int pSock);
		int initClient(const unsigned int pSock);
		const char *getServerReply() const;
	protected:
		char *mServerName;
		unsigned int mPort;
		char *mServerReply;
		int extractReturnCode(const char *output) const;
	};
} // namespace jed_utils

#endif
