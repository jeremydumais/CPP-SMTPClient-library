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
		
		explicit MessageAddress(const char *pEmailAddress, const char *pDisplayName = "");
		~MessageAddress();
		MessageAddress(const MessageAddress& other); //Copy constructor
        MessageAddress& operator=(const MessageAddress& other); //Copy assignment
		MessageAddress(MessageAddress&& other) noexcept; //Move constructor
		MessageAddress& operator=(MessageAddress&& other) noexcept; //Move assignement
		bool operator==(const MessageAddress &pMsgComp) const;
		explicit operator std::string() const;
		const char *getEmailAddress() const;
		const char *getDisplayName() const;
		friend class message;
	private:	
		char * mEmailAddress;
		char * mDisplayName;
		bool isEmailAddressValid(const std::string &pEmailAddress) const;
	};
} // namespace jed_utils

#endif
