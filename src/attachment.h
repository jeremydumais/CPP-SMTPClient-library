#ifndef ATTACHMENT_H
#define ATTACHMENT_H

#include "attachmenterror.h"
#include "base64.h"
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
		explicit Attachment(const char *pFilename, const char *pName = "");
		~Attachment();
		Attachment(const Attachment& other); //Copy constructor
        Attachment& operator=(const Attachment& other); //Copy assignment
		Attachment(Attachment&& other) noexcept; //Move constructor
		Attachment& operator=(Attachment&& other) noexcept; //Move assignement
		const char *getName() const;
		const char *getFilename() const;
		const char *getBase64EncodedFile() const;
		const char *getMimeType() const;
		friend class Message;
	private:
		Attachment() = default;
		char *mName;
		char *mFilename;
	};
} // namespace jed_utils

#endif
