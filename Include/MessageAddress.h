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
		MessageAddress(const char *pEmailAddress, const char *pDisplayName = "");
		MessageAddress(const MessageAddress &);
		MessageAddress() {};
		~MessageAddress();
		const MessageAddress& operator=(const MessageAddress &pMsgAdd);
		bool operator==(const MessageAddress &pMsgComp) const;
		operator std::string() const;
		const char *getEmailAddress() const;
		const char *getDisplayName() const;
		friend class message;
	private:	
		char *mEmailAddress = nullptr;
		char *mDisplayName = nullptr;
	};
}

#endif