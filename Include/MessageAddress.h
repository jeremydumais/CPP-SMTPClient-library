#ifndef MESSAGEADDRESS_H
#define MESSAGEADDRESS_H

#include <string>
#include <sstream>

#pragma once  

#ifdef SMTPCLIENT_EXPORTS  
#define MESSAGEADDRESS_API __declspec(dllexport)   
#else  
#define MESSAGEADDRESS_API __declspec(dllimport)   
#endif  

namespace jed_utils
{
	class MESSAGEADDRESS_API message_address
	{
	public:
		message_address(std::string email_address, std::string display_name = "");
		message_address(const message_address &);
		~message_address();
		const message_address& operator=(const message_address &msg_add);
		operator std::string() const;// { return ""; }
		std::string get_email_address() const;
		std::string get_display_name() const;
		friend class message;
	private:
		message_address() {};
		char *email_address = NULL;
		char *display_name = NULL;
	};
}

#endif