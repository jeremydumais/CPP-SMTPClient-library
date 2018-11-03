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
		Attachment(const char *pFilename, const char *pName = "");
		Attachment(const Attachment &);
		~Attachment();
		const Attachment& operator=(const Attachment &pAtt);
		const char *getName() const;
		const char *getFilename() const;
		const char *getBase64EncodedFile() const;
		const char *getMimeType() const;
		friend class Message;
	private:
		Attachment() {};
		char *mName = nullptr;
		char *mFilename = nullptr;
		std::string toUppercase(const std::string &pValue) const;
	};
}

#endif