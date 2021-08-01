#ifndef SMTPCLIENT_H
#define SMTPCLIENT_H

#include "smtpclientbase.h"

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
	class SMTPCLIENT_API SmtpClient : public SMTPClientBase
	{
	public:
		SmtpClient(const char *pServerName, unsigned int pPort);
		virtual ~SmtpClient();
        SmtpClient(const SmtpClient &other) = default; //Copy constructor
        SmtpClient& operator=(const SmtpClient &other); //Copy assignment
        SmtpClient(SmtpClient &&other) noexcept; //Move constructor
        SmtpClient& operator=(SmtpClient &&other) noexcept; //Move assignement
	protected:
		void cleanup() override;
		//Methods used to establish the connection with server
		int establishConnectionWithServer() override;
		//Methods to send commands to the server
		int sendCommand(const char *pCommand, int pErrorCode) override;
		int sendCommandWithFeedback(const char *pCommand, int pErrorCode, int pTimeoutCode) override;
	};
} // namespace jed_utils

#endif
