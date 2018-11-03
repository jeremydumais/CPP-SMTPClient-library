#include "../Include/Attachment.h"
#include <iostream>

using namespace std;

namespace jed_utils
{
	Attachment::Attachment(const string &pFilename, const string &pName)
	{
		if (pFilename.length() == 0)
			throw invalid_argument("filename");
		this->mFilename = new string(pFilename);
		this->mName = new string(pName);
	}

	Attachment::Attachment(const Attachment &pItem)
	{
		mFilename = pItem.mFilename;
		mName = pItem.mName;
	}

	const Attachment& Attachment::operator=(const Attachment &pAtt)
	{
		if (this != &pAtt)
		{
			delete mFilename;
			delete mName;

			mFilename = new string(*pAtt.mFilename);
			mName = new string(*pAtt.mName);
		}
		return *this;
	}

	Attachment::~Attachment()
	{
		if (mFilename)
			delete mFilename;
		if (mName)
			delete mName;
	}

	const string &Attachment::getName() const
	{
		return *mName;
	}

	const string &Attachment::getFilename() const
	{
		return *mFilename;
	}

	string Attachment::getBase64EncodedFile() const
	{
		//Open the file
		ifstream in(*mFilename, std::ios::in | std::ios::binary);
		if (in)
		{
			std::string contents;
			in.seekg(0, std::ios::end);
			contents.resize((unsigned int)in.tellg());
			in.seekg(0, std::ios::beg);
			in.read(&contents[0], contents.size());
			in.close();
			string base64_result = base64_encode(reinterpret_cast<const unsigned char*>(contents.c_str()), contents.length());
			char *base64_file = new char[base64_result.length() + 1];
			strcpy_s(base64_file, base64_result.length() + 1, base64_result.c_str());
			return base64_file;
		}
		else
			throw AttachmentError((string("Could not open file ") + string(*mFilename)).c_str());
	}

	string Attachment::getMimeType() const
	{
		string filename_str(*mFilename);
		const string extension = toUppercase(filename_str.substr(filename_str.find_last_of(".") + 1));
		//Images
		if (extension == "PNG")
			return "image/png";
		else if (extension == "JPEG" || extension == "JPG" || extension == "JPE")
			return "image/jpeg";
		else if (extension == "GIF")
			return "image/gif";
		else if (extension == "TIFF" || extension == "TIF")
			return "image/tiff";
		else if (extension == "ICO")
			return "image/x-icon";
		//Application
		else if (extension == "XML" || extension == "XSL")
			return "application/xml";
		else if (extension == "XHTML" || extension == "XHT")
			return "application/xhtml+xml";
		else if (extension == "PDF")
			return "application/pdf";
		else if (extension == "JS")
			return "application/javascript";
		//Text
		else if (extension == "CSS")
			return "text/css";
		else if (extension == "CSV")
			return "text/csv";
		else if (extension == "HTML" || extension == "HTM")
			return "text/html";
		else if (extension == "TXT" || extension == "TEXT" || extension == "CONF"
			|| extension == "DEF" || extension == "LIST" || extension == "LOG"
			|| extension == "IN")
			return "text/plain";
		//Videos
		else if (extension == "MPEG" || extension == "MPG" || extension == "MPE"
			|| extension == "M1V" || extension == "M2V")
			return "video/mpeg";
		else if (extension == "MP4" || extension == "MP4V" || extension == "MPG4")
			return "video/mp4";
		else if (extension == "QT" || extension == "MOV")
			return "video/quicktime";
		else if (extension == "WMV")
			return "video/x-ms-wmv";
		else if (extension == "AVI")
			return "video/x-msvideo";
		else if (extension == "FLV")
			return "video/x-flv";
		else if (extension == "WEBM")
			return "video/webm";
		//Archives
		else if (extension == "ZIP")
			return "application/zip";
		else if (extension == "RAR")
			return "application/x-rar-compressed";
		//Documents
		else if (extension == "ODT")
			return "application/vnd.oasis.opendocument.text";
		else if (extension == "ODS")
			return "application/vnd.oasis.opendocument.spreadsheet";
		else if (extension == "ODP")
			return "application/vnd.oasis.opendocument.presentation";
		else if (extension == "ODG")
			return "application/vnd.oasis.opendocument.graphics";
		else if (extension == "XLS" || extension == "XLM" || extension == "XLA"
			|| extension == "XLC" || extension == "XLT" || extension == "XLW")
			return "application/vnd.ms-excel";
		else if (extension == "XLAM")
			return "application/vnd.ms-excel.addin.macroenabled.12";
		else if (extension == "XLSB")
			return "application/vnd.ms-excel.sheet.binary.macroenabled.12";
		else if (extension == "XLSM")
			return "application/vnd.ms-excel.sheet.macroenabled.12";
		else if (extension == "XLTM")
			return "application/vnd.ms-excel.template.macroenabled.12";
		else if (extension == "XLSX")
			return "application/vnd.openxmlformats-officedocument.spreadsheetml.sheet";
		else if (extension == "XLTX")
			return "application/vnd.openxmlformats-officedocument.spreadsheetml.template";
		else if (extension == "PPT" || extension == "PPS" || extension == "POT")
			return "application/vnd.ms-powerpoint";
		else if (extension == "PPAM")
			return "application/vnd.ms-powerpoint.addin.macroenabled.12";
		else if (extension == "PPTM")
			return "application/vnd.ms-powerpoint.presentation.macroenabled.12";
		else if (extension == "SLDM")
			return "application/vnd.ms-powerpoint.slide.macroenabled.12";
		else if (extension == "PPSM")
			return "application/vnd.ms-powerpoint.slideshow.macroenabled.12";
		else if (extension == "POTM")
			return "application/vnd.ms-powerpoint.template.macroenabled.12";
		else if (extension == "PPTX")
			return "application/vnd.openxmlformats-officedocument.presentationml.presentation";
		else if (extension == "SLDX")
			return "application/vnd.openxmlformats-officedocument.presentationml.slide";
		else if (extension == "PPSX")
			return "application/vnd.openxmlformats-officedocument.presentationml.slideshow";
		else if (extension == "POTX")
			return "application/vnd.openxmlformats-officedocument.presentationml.template";
		else if (extension == "DOC")
			return "application/msword";
		else if (extension == "DOT")
			return "application/msword";
		else if (extension == "DOCX")
			return "application/vnd.openxmlformats-officedocument.wordprocessingml.document";
		else if (extension == "DOTX")
			return "application/vnd.openxmlformats-officedocument.wordprocessingml.template";
		else if (extension == "XUL")
			return "application/vnd.mozilla.xul+xml";

		return "";
	}

	string Attachment::toUppercase(const string &pValue) const
	{
		string retval = "";
		for (unsigned int c = 0; c < pValue.length(); c++)
			retval += toupper(pValue[c]);

		return retval;
	}
}