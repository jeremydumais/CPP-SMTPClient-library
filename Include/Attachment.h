#ifndef ATTACHMENT_H
#define ATTACHMENT_H

#include "AttachmentError.h"
#include "Base64.h"
#include <cstring>
#include <fstream>

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
		explicit Attachment(const std::string &pFilename, const std::string &pName = "");
		const std::string &getName() const;
		const std::string &getFilename() const;
		std::string getBase64EncodedFile() const;
		std::string getMimeType() const;
		friend class Message;
	private:
		Attachment() = default;
		std::string mName;
		std::string mFilename;
		std::string toUppercase(const std::string &pValue) const;
	};
} // namespace jed_utils

#endif
