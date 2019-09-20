#ifndef SMTPCLIENT_H
#define SMTPCLIENT_H

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
		#define SMTPCLIENT_API __declspec(dllexport)   
	#else  
		#define SMTPCLIENT_API __declspec(dllimport)   
	#endif  
#else
	#define SMTPCLIENT_API
#endif

namespace jed_utils
{
	class SMTPCLIENT_API SmtpClient
	{
	public:
		SmtpClient(const char *pServerName, unsigned int pPort);
		virtual ~SmtpClient();
        SmtpClient(const SmtpClient &other); //Copy constructor
        SmtpClient& operator=(const SmtpClient &other); //Copy assignment
        SmtpClient(SmtpClient &&other) noexcept; //Move constructor
        SmtpClient& operator=(SmtpClient &&other) noexcept; //Move assignement
		int sendMail(const Message &pMsg);
		const char *getServerReply() const;
	protected:
		char *mServerName;
		unsigned int mPort;
		char *mServerReply;
		int writeCommand(unsigned int pSock,
			const char *pStr,
			const char *pArg,
			bool pAskForReply = true);
		std::string createAttachmentsText(const std::vector<Attachment*> &pAttachments);
	};
} // namespace jed_utils

#endif
