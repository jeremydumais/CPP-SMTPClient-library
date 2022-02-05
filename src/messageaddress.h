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
	/** @brief The MessageAddress class represents a sender or a recipient address containing
	 *  the email address and the display name. 
	 *  Example : joeblow@domainexample.com Joe Blow 
	 */
	class MESSAGEADDRESS_API MessageAddress
	{
	public:
		/**
		 *  @brief  Construct a new MessageAddress. 
		 *  @param pEmailAddress The email address. The prefix appears to the left of the @ symbol. 
		 *  The domain appears to the right of the @ symbol.
		 *  @param pDisplayName The display name of the address that will appear in 
		 *  the message. Example : Joe Blow  
		 */
		explicit MessageAddress(const char *pEmailAddress, const char *pDisplayName = "");

		/** Destructor of the MessageAddress */
		~MessageAddress();

		/** MessageAddress copy constructor. */
		MessageAddress(const MessageAddress& other);

		/** MessageAddress copy assignment operator. */
        MessageAddress& operator=(const MessageAddress& other); //Copy assignment

		/** MessageAddress move constructor. */
		MessageAddress(MessageAddress&& other) noexcept; //Move constructor

		/** MessageAddress move assignment operator. */
		MessageAddress& operator=(MessageAddress&& other) noexcept; //Move assignement

		/** MessageAddress equality operator. */
		bool operator==(const MessageAddress &pMsgComp) const;
		
		/** MessageAddress implicit string conversion operator. */
		explicit operator std::string() const;

		/** Return the email address. */
		const char *getEmailAddress() const;

		/** Return the display name. */
		const char *getDisplayName() const;
		
		friend class message;
	private:	
		char * mEmailAddress;
		char * mDisplayName;
		bool isEmailAddressValid(const std::string &pEmailAddress) const;
	};
} // namespace jed_utils

#endif
