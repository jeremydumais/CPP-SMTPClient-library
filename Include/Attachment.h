#ifndef ATTACHMENT_H
#define ATTACHMENT_H

#include <string>
#include <fstream>
#include "Base64.h"
#include "AttachmentError.h"

#pragma once  

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
		attachment(const std::string filename, const std::string name = "");
		attachment(const attachment &);
		~attachment();
		const attachment& operator=(const attachment &att);
		std::string get_name() const;
		std::string get_filename() const;
		std::string get_base64_encoded_file() const;
		std::string get_mime_type() const;
		friend class message;
	private:
		attachment() {};
		char *name = NULL;
		char *filename = NULL;
		std::string to_uppercase(const std::string &value) const;
	};
}

#endif