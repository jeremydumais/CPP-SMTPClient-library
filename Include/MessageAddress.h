#ifndef MESSAGEADDRESS_H
#define MESSAGEADDRESS_H

#include <cstring>
#include <sstream>

#pragma once  

#ifdef _WIN32
	#ifdef SMTPCLIENT_EXPORTS  
		#define MESSAGEADDRESS_API __declspec(dllexport)   
	#else  
		#define MESSAGEADDRESS_API __declspec(dllimport)   
	#endif 
#else
	#define MESSAGEADDRESS_API
#endif

namespace jed_utils
{
	class MESSAGEADDRESS_API MessageAddress
	{
	public:
		explicit MessageAddress(const std::string &pEmailAddress, const std::string &pDisplayName = "");
		bool operator==(const MessageAddress &pMsgComp) const;
		explicit operator std::string() const;
		const std::string &getEmailAddress() const;
		const std::string &getDisplayName() const;
		friend class message;
	private:	
		std::string mEmailAddress;
		std::string mDisplayName;
		bool isEmailAddressValid(const std::string &pEmailAddress) const;
	};
} // namespace jed_utils

#endif
