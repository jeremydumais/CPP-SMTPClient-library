#include "../Include/Attachment.h"
#include <iostream>

using namespace jed_utils;
using namespace std;

attachment::attachment(const string filename, const string name)
{
	if (filename.length() == 0)
		throw invalid_argument("filename");
	const std::string::size_type size_filename = filename.size();
	this->filename = new char[size_filename + 1];
	memcpy(this->filename, filename.c_str(), size_filename + 1);
	
	const std::string::size_type size_name = name.size();
	this->name = new char[size_name + 1]; 
	memcpy(this->name, name.c_str(), size_name + 1);
}

attachment::attachment(const attachment &item)
{
	filename = new char[strlen(item.filename) + 1]; 
	memcpy(filename, item.filename, strlen(item.filename) + 1);

	name = new char[strlen(item.name) + 1]; 
	memcpy(name, item.name, strlen(item.name) + 1);
}

const attachment& attachment::operator=(const attachment &att)
{
	if (this != &att)
	{
		delete filename;
		delete name;
		filename = new char[strlen(att.filename) + 1];
		memcpy(filename, att.filename, strlen(att.filename) + 1);

		name = new char[strlen(att.name) + 1];
		memcpy(name, att.name, strlen(att.name) + 1);
	}
	return *this;
}

attachment::~attachment()
{
	delete filename;
	delete name;
}

string attachment::get_name() const
{
	return string(name);
}

string attachment::get_filename() const
{
	return string(filename);
}

string attachment::get_base64_encoded_file() const
{
	//Open the file
	ifstream in(filename, std::ios::in | std::ios::binary);
	if (in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize((unsigned int)in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(base64_encode(reinterpret_cast<const unsigned char*>(contents.c_str()), contents.length()));
	}
	else
		throw attachment_error(string("Could not open file ") + string(filename));
}

string attachment::get_mime_type() const
{
	string retval = "";
	string filename_str(filename);
	const string extension = to_uppercase(filename_str.substr(filename_str.find_last_of(".") + 1));
	//Images
	if (extension == "PNG")
		retval = "image/png";
	else if (extension == "JPEG" || extension == "JPG" || extension == "JPE")
		retval = "image/jpeg";
	else if (extension == "GIF")
		retval = "image/gif";
	else if (extension == "TIFF" || extension == "TIF")
		retval = "image/tiff";
	else if (extension == "ICO")
		retval = "image/x-icon";
	//Application
	else if (extension == "XML" || extension == "XSL")
		retval = "application/xml";
	else if (extension == "XHTML" || extension == "XHT")
		retval = "application/xhtml+xml";
	else if (extension == "PDF")
		retval = "application/pdf";
	else if (extension == "JS")
		retval = "application/javascript";
	//Text
	else if (extension == "CSS")
		retval = "text/css";
	else if (extension == "CSV")
		retval = "text/csv";
	else if (extension == "HTML" || extension == "HTM")
		retval = "text/html";
	else if (extension == "TXT" || extension == "TEXT" || extension == "CONF"
		|| extension == "DEF" || extension == "LIST" || extension == "LOG"
		|| extension == "IN")
		retval = "text/plain";
	//Videos
	else if (extension == "MPEG" || extension == "MPG" || extension == "MPE" 
		|| extension == "M1V" || extension == "M2V")
		retval = "video/mpeg";
	else if (extension == "MP4" || extension == "MP4V" || extension == "MPG4")
		retval = "video/mp4";
	else if (extension == "QT" || extension == "MOV")
		retval = "video/quicktime";
	else if (extension == "WMV")
		retval = "video/x-ms-wmv";
	else if (extension == "AVI")
		retval = "video/x-msvideo";
	else if (extension == "FLV")
		retval = "video/x-flv";
	else if (extension == "WEBM")
		retval = "video/webm";
	//Archives
	else if (extension == "ZIP")
		retval = "application/zip";
	else if (extension == "RAR")
		retval = "application/x-rar-compressed";
	//Documents
	else if (extension == "ODT")
		retval = "application/vnd.oasis.opendocument.text";	
	else if (extension == "ODS")
		retval = "application/vnd.oasis.opendocument.spreadsheet";
	else if (extension == "ODP")
		retval = "application/vnd.oasis.opendocument.presentation";	
	else if (extension == "ODG")
		retval = "application/vnd.oasis.opendocument.graphics";		
	else if (extension == "XLS" || extension == "XLM" || extension == "XLA" 
		|| extension == "XLC" || extension == "XLT" || extension == "XLW")
		retval = "application/vnd.ms-excel";		
	else if (extension == "XLAM")
		retval = "application/vnd.ms-excel.addin.macroenabled.12";	
	else if (extension == "XLSB")
		retval = "application/vnd.ms-excel.sheet.binary.macroenabled.12";
	else if (extension == "XLSM")
		retval = "application/vnd.ms-excel.sheet.macroenabled.12";
	else if (extension == "XLTM")
		retval = "application/vnd.ms-excel.template.macroenabled.12";
	else if (extension == "XLSX")
		retval = "application/vnd.openxmlformats-officedocument.spreadsheetml.sheet";
	else if (extension == "XLTX")
		retval = "application/vnd.openxmlformats-officedocument.spreadsheetml.template";
	else if (extension == "PPT" || extension == "PPS" || extension == "POT")
		retval = "application/vnd.ms-powerpoint";
	else if (extension == "PPAM")
		retval = "application/vnd.ms-powerpoint.addin.macroenabled.12";
	else if (extension == "PPTM")
		retval = "application/vnd.ms-powerpoint.presentation.macroenabled.12";
	else if (extension == "SLDM")
		retval = "application/vnd.ms-powerpoint.slide.macroenabled.12";
	else if (extension == "PPSM")
		retval = "application/vnd.ms-powerpoint.slideshow.macroenabled.12";
	else if (extension == "POTM")
		retval = "application/vnd.ms-powerpoint.template.macroenabled.12";
	else if (extension == "PPTX")
		retval = "application/vnd.openxmlformats-officedocument.presentationml.presentation";
	else if (extension == "SLDX")
		retval = "application/vnd.openxmlformats-officedocument.presentationml.slide";
	else if (extension == "PPSX")
		retval = "application/vnd.openxmlformats-officedocument.presentationml.slideshow";
	else if (extension == "POTX")
		retval = "application/vnd.openxmlformats-officedocument.presentationml.template";
	else if (extension == "DOC")
		retval = "application/msword";
	else if (extension == "DOT")
		retval = "application/msword";
	else if (extension == "DOCX")
		retval = "application/vnd.openxmlformats-officedocument.wordprocessingml.document";
	else if (extension == "DOTX")
		retval = "application/vnd.openxmlformats-officedocument.wordprocessingml.template";
	else if (extension == "XUL")
		retval = "application/vnd.mozilla.xul+xml";

	return retval;
}

string attachment::to_uppercase(const string &value) const
{
	string retval = "";
	for (unsigned int c = 0; c < value.length(); c++)
		retval += toupper(value[c]);

	return retval;
}