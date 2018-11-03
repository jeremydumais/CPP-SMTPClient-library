#ifndef MESSAGEADDRESS_H
#define MESSAGEADDRESS_H

#include <cstring>
#include <sstream>

#pragma once  

#ifdef SMTPCLIENT_EXPORTS  
#define MESSAGEADDRESS_API __declspec(dllexport)   
#else  
#define MESSAGEADDRESS_API __declspec(dllimport)   
#endif  

namespace jed_utils
{
	class MESSAGEADDRESS_API MessageAddress
	{
	public:
		MessageAddress(const char *email_address, const char *display_name = "");
		MessageAddress(const MessageAddress &);
		MessageAddress() {};
		~MessageAddress();
		const MessageAddress& operator=(const MessageAddress &msg_add);
		bool operator==(const MessageAddress &msg_comp) const;
		operator std::string() const;
		const char *get_email_address() const;
		const char *get_display_name() const;
		friend class message;
	private:	
		char *email_address = nullptr;
		char *display_name = nullptr;
	};
}

#endif