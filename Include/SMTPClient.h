#include <string>
#include "CommunicationError.h"

#pragma once  

#ifndef SMTPCLIENT_EXPORTS  
#define SMTPCLIENT_API __declspec(dllexport)   
#else  
#define SMTPCLIENT_API __declspec(dllimport)   
#endif  

namespace jed_utils
{
	class SMTPCLIENT_API smtp_client
	{
	public:
		smtp_client(const std::string server_name, const unsigned int port);
		void send_mail(const std::string from,
			const std::string to,
			const std::string subject,
			const std::string body);
		const std::string get_server_reply();
	protected:
		std::string server_name;
		unsigned int port;
		std::string server_reply;
		void write_command(const unsigned int sock, 
			const std::string str, 
			const std::string arg, 
			const bool ask_for_reply = true);
	};
}
