#ifndef ATTACHMENT_H
#define ATTACHMENT_H

#include <cstring>
#include <fstream>
#include "Base64.h"
#include "AttachmentError.h"

#ifdef SMTPCLIENT_EXPORTS  
#define ATTACHMENT_API __declspec(dllexport)   
#else  
#define ATTACHMENT_API __declspec(dllimport)   
#endif  

namespace jed_utils
{
	class ATTACHMENT_API Attachment
	{
	public:
		Attachment(const std::string &pFilename, const std::string &pName = "");
		Attachment(const Attachment &);
		~Attachment();
		const Attachment& operator=(const Attachment &pAtt);
		const std::string &getName() const;
		const std::string &getFilename() const;
		std::string getBase64EncodedFile() const;
		std::string getMimeType() const;
		friend class Message;
	private:
		Attachment() {};
		std::string *mName = nullptr;
		std::string *mFilename = nullptr;
		std::string toUppercase(const std::string &pValue) const;
	};
}

#endif