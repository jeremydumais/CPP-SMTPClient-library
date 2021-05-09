#ifndef SMTPCLIENTBASE_H
#define SMTPCLIENTBASE_H

#include "attachment.h"
#include "attachmenterror.h"
#include "communicationerror.h"
#include "credential.h"
#include "htmlmessage.h"
#include "messageaddress.h"
#include "plaintextmessage.h"
#include "serverauthoptions.h"

#include <vector>

#ifdef _WIN32
	#ifdef SMTPCLIENT_EXPORTS  
		#define SMTPCLIENTBASE_API __declspec(dllexport)   
	#else  
		#define SMTPCLIENTBASE_API __declspec(dllimport)   
	#endif  
#else
	#define SMTPCLIENTBASE_API
#endif

namespace jed_utils
{
	class SMTPCLIENTBASE_API SmtpClientBase
	{
	public:
		SmtpClientBase(const char *pServerName, unsigned int pPort);
		virtual ~SmtpClientBase();
		SmtpClientBase(const SmtpClientBase& other); //Copy constructor
        SmtpClientBase& operator=(const SmtpClientBase& other); //Copy assignment
		SmtpClientBase(SmtpClientBase&& other) noexcept; //Move constructor
		SmtpClientBase& operator=(SmtpClientBase&& other) noexcept; //Move assignement
		const char *getServerName() const;
		unsigned int getServerPort() const;
		unsigned int getCommandTimeout() const;
		const char *getCommunicationLog() const;
		const Credential *getCredentials() const;
		void setServerName(const char *pServerName);
		void setServerPort(unsigned int pPort);
		void setCommandTimeout(unsigned int pTimeOutInSeconds);
		void setCredentials(const Credential &pCredential);
		int sendMail(const Message &pMsg);
	protected:
		char *mServerName;
		unsigned int mPort;
		char *mCommunicationLog;
		char *mLastServerResponse;
		unsigned int mCommandTimeOut;
		int mLastSocketErrNo;
		ServerAuthOptions *mAuthOptions;
		Credential *mCredential;
		int mSock;
		virtual void cleanup() = 0;
		//Methods used to establish the connection with server
		int initializeSession();
		int sendServerIdentification();
		virtual int establishConnectionWithServer() = 0;
		//Methods to send commands to the server
		void setLastServerResponse(const char *pResponse);
		int sendRawCommand(const char *pCommand, int pErrorCode);
		int sendRawCommand(const char *pCommand, int pErrorCode, int pTimeoutCode);
		virtual int sendCommand(const char *pCommand, int pErrorCode) = 0;
		virtual int sendCommandWithFeedback(const char *pCommand, int pErrorCode, int pTimeoutCode) = 0;
		//Methods used for authentication
		int authenticateClient();
		int authenticateWithMethodPlain();
		int authenticateWithMethodLogin();
		//Methods to send an email
		int setMailRecipients(const Message &pMsg);
		int addMailRecipients(jed_utils::MessageAddress **list, size_t count, const int RECIPIENT_OK);
		int setMailHeaders(const Message &pMsg);
		int addMailHeader(const char *field, const char *value, int pErrorCode);
		int setMailBody(const Message &pMsg);

		void addCommunicationLogItem(const char *pItem, const char *pPrefix = "c");
		std::string createAttachmentsText(const std::vector<Attachment*> &pAttachments) const;
		int extractReturnCode(const char *pOutput) const;
		static ServerAuthOptions *extractAuthenticationOptions(const char *pEhloOutput);

    };
} // namespace jed_utils

#endif