#ifndef ATTACHMENT_H
#define ATTACHMENT_H

#include <cstring>
#include <fstream>
#include "Base64.h"
#include "AttachmentError.h"

#ifdef _WIN32
	#ifdef SMTPCLIENT_EXPORTS  
		#define ATTACHMENT_API __declspec(dllexport)   
	#else  
		#define ATTACHMENT_API __declspec(dllimport)   
	#endif
#else
	#define ATTACHMENT_API
#endif

namespace jed_utils
{
	class ATTACHMENT_API Attachment
	{
	public:
		Attachment(const std::string &pFilename, const std::string &pName = "");
		/*Attachment(const Attachment &); //Copy constructor
		~Attachment();
		Attachment &operator=(const Attachment &pAtt); //Copy assignment
		Attachment(Attachment&&) noexcept; //Move constructor
		Attachment& operator=(Attachment&&) noexcept; //Move assignement*/
		const std::string &getName() const;
		const std::string &getFilename() const;
		std::string getBase64EncodedFile() const;
		std::string getMimeType() const;
		friend class Message;
	private:
		Attachment() {};
		std::string mName;
		std::string mFilename;
		std::string toUppercase(const std::string &pValue) const;
	};
}

#endif
