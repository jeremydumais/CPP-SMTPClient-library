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
	class ATTACHMENT_API attachment
	{
	public:
		attachment(const char *filename, const char *name = "");
		attachment(const attachment &);
		~attachment();
		const attachment& operator=(const attachment &att);
		const char *get_name() const;
		const char *get_filename() const;
		const char *get_base64_encoded_file() const;
		const char *get_mime_type() const;
		friend class message;
	private:
		attachment() {};
		char *name = nullptr;
		char *filename = nullptr;
		std::string to_uppercase(const std::string &value) const;
	};
}

#endif