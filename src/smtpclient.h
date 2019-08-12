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
		SmtpClient(const std::string &pServerName, unsigned int pPort);
		void sendMail(const Message &pMsg);
		const std::string &getServerReply() const;
	protected:
		std::string mServerName;
		unsigned int mPort;
		std::string mServerReply;
		void writeCommand(unsigned int pSock,
			const std::string &pStr,
			const std::string &pArg,
			bool pAskForReply = true);
		std::string createAttachmentsText(const std::vector<Attachment> &pAttachments);
	};
} // namespace jed_utils

#endif
