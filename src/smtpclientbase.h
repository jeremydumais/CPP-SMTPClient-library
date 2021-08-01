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
#include <tuple>
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

#define COMMUNICATIONLOG_LENGTH			4096	/* The max length of the communication log */
#define SERVERRESPONSE_BUFFER_LENGTH	1024	/* The max length of the server response buffer */

namespace jed_utils
{
	class SMTPCLIENTBASE_API SMTPClientBase
	{
	public:
		SMTPClientBase(const char *pServerName, unsigned int pPort);
		virtual ~SMTPClientBase();
		SMTPClientBase(const SMTPClientBase& other); //Copy constructor
        SMTPClientBase& operator=(const SMTPClientBase& other); //Copy assignment
		SMTPClientBase(SMTPClientBase&& other) noexcept; //Move constructor
		SMTPClientBase& operator=(SMTPClientBase&& other) noexcept; //Move assignement
		const char *getServerName() const;
		unsigned int getServerPort() const;
		unsigned int getCommandTimeout() const;
		const char *getCommunicationLog() const;
		const Credential *getCredentials() const;
		void setServerName(const char *pServerName);
		void setServerPort(unsigned int pPort);
		void setCommandTimeout(unsigned int pTimeOutInSeconds);
		void setCredentials(const Credential &pCredential);
		void setKeepUsingBaseSendCommands(bool pValue);
		int sendMail(const Message &pMsg);
	protected:  
		virtual void cleanup() = 0;
		int getSocketFileDescriptor() const;
		void clearSocketFileDescriptor();
		const char *getLastServerResponse() const;
		void setLastSocketErrNo(int lastError);
		void setAuthenticationOptions(ServerAuthOptions *authOptions);
		//Methods used to establish the connection with server
		int initializeSession();
		int sendServerIdentification();
		virtual int establishConnectionWithServer() = 0;
		virtual int checkServerGreetings();
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
		static std::string createAttachmentsText(const std::vector<Attachment*> &pAttachments);
		static int extractReturnCode(const char *pOutput);
		static ServerAuthOptions *extractAuthenticationOptions(const char *pEhloOutput);
	private:
		char *mServerName;
		unsigned int mPort;
		char *mCommunicationLog;
		char *mLastServerResponse;
		unsigned int mCommandTimeOut;
		int mLastSocketErrNo;
		ServerAuthOptions *mAuthOptions;
		Credential *mCredential;
		int mSock;
		// This field indicate the class will keep using base send command even if a child class
		// as overriden the sendCommand and sendCommandWithFeedback.
		// This is used for example if you are using a secure client class but the STARTTLS
		// feature is not available. The communication will then remain unsecured.
		bool mKeepUsingBaseSendCommands;
	    int (SMTPClientBase::*sendCommandPtr)(const char *pCommand, int pErrorCode);
    	int (SMTPClientBase::*sendCommandWithFeedbackPtr)(const char *pCommand, int pErrorCode, int pTimeoutCode);
    };
} // namespace jed_utils

#endif