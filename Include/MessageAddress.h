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
		MessageAddress(const std::string &pEmailAddress, const std::string &pDisplayName = "");
		MessageAddress(const MessageAddress &);
		MessageAddress() {};
		~MessageAddress();
		MessageAddress &operator=(const MessageAddress &pMsgAdd);
		bool operator==(const MessageAddress &pMsgComp) const;
		operator std::string() const;
		const std::string &getEmailAddress() const;
		const std::string &getDisplayName() const;
		friend class message;
	private:	
		std::string *mEmailAddress = nullptr;
		std::string *mDisplayName = nullptr;
		bool isEmailAddressValid(const std::string &pEmailAddress) const;
	};
}

#endif