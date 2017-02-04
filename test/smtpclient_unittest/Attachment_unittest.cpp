#include "../../Include/Attachment.h"
#include <assert.h>


using namespace jed_utils;
using namespace std;

void test_attachement_constructor()
{
	//Test with empty filename
	try
	{
		attachment att1("", "");
		assert(false);

	}
	catch (invalid_argument& err)
	{
		assert(strcmp(err.what(), "filename") == 0);
	}
}

void test_attachment_getmimetype()
{
	//Images
	attachment att1("test.png", "");
	assert(att1.get_mime_type() == "image/png" && "png Image");
	att1 = attachment("test.jpg", "");
	assert(att1.get_mime_type() == "image/jpeg" && "jpg Image");
	att1 = attachment("test.jpeg", "");
	assert(att1.get_mime_type() == "image/jpeg" && "jpeg Image");
	att1 = attachment("test.jpe", "");
	assert(att1.get_mime_type() == "image/jpeg" && "jpe Image");
	att1 = attachment("test.gif", "");
	assert(att1.get_mime_type() == "image/gif" && "gif Image");
	att1 = attachment("test.tif", "");
	assert(att1.get_mime_type() == "image/tiff" && "tif Image");
	att1 = attachment("test.tiff", "");
	assert(att1.get_mime_type() == "image/tiff" && "tiff Image");
	att1 = attachment("test.ico", "");
	assert(att1.get_mime_type() == "image/x-icon" && "ico Image");
	//Applications
	att1 = attachment("test.xml", "");
	assert(att1.get_mime_type() == "application/xml" && "xml Document");
	att1 = attachment("test.xsl", "");
	assert(att1.get_mime_type() == "application/xml" && "xsl Document");
	att1 = attachment("test.xhtml", "");
	assert(att1.get_mime_type() == "application/xhtml+xml" && "xhtml Document");	
	att1 = attachment("test.xht", "");
	assert(att1.get_mime_type() == "application/xhtml+xml" && "xht Document");
	att1 = attachment("test.pdf", "");
	assert(att1.get_mime_type() == "application/pdf" && "pdf Document");	
	att1 = attachment("test.js", "");
	assert(att1.get_mime_type() == "application/javascript" && "js Document");	
	//Text
	att1 = attachment("test.css", "");
	assert(att1.get_mime_type() == "text/css" && "css File");
	att1 = attachment("test.csv", "");
	assert(att1.get_mime_type() == "text/csv" && "csv File");
	att1 = attachment("test.html", "");
	assert(att1.get_mime_type() == "text/html" && "html File");
	att1 = attachment("test.htm", "");
	assert(att1.get_mime_type() == "text/html" && "htm File");
	att1 = attachment("test.txt", "");
	assert(att1.get_mime_type() == "text/plain" && "txt File");
	att1 = attachment("test.text", "");
	assert(att1.get_mime_type() == "text/plain" && "text File");
	att1 = attachment("test.conf", "");
	assert(att1.get_mime_type() == "text/plain" && "conf File");
	att1 = attachment("test.def", "");
	assert(att1.get_mime_type() == "text/plain" && "def File");
	att1 = attachment("test.list", "");
	assert(att1.get_mime_type() == "text/plain" && "list File");
	att1 = attachment("test.log", "");
	assert(att1.get_mime_type() == "text/plain" && "log File");
	att1 = attachment("test.in", "");
	assert(att1.get_mime_type() == "text/plain" && "in File");
	//Videos
	att1 = attachment("test.mpeg", "");
	assert(att1.get_mime_type() == "video/mpeg" && "mpeg File");
	att1 = attachment("test.mpg", "");
	assert(att1.get_mime_type() == "video/mpeg" && "mpg File");
	att1 = attachment("test.mpe", "");
	assert(att1.get_mime_type() == "video/mpeg" && "mpe File");
	att1 = attachment("test.m1v", "");
	assert(att1.get_mime_type() == "video/mpeg" && "m1v File");
	att1 = attachment("test.m2v", "");
	assert(att1.get_mime_type() == "video/mpeg" && "m2v File");
	att1 = attachment("test.mp4", "");
	assert(att1.get_mime_type() == "video/mp4" && "mp4 File");
	att1 = attachment("test.mp4v", "");
	assert(att1.get_mime_type() == "video/mp4" && "mp4v File");
	att1 = attachment("test.mpg4", "");
	assert(att1.get_mime_type() == "video/mp4" && "mpg4 File");
	att1 = attachment("test.qt", "");
	assert(att1.get_mime_type() == "video/quicktime" && "qt File");
	att1 = attachment("test.mov", "");
	assert(att1.get_mime_type() == "video/quicktime" && "mov File");	
	att1 = attachment("test.wmv", "");
	assert(att1.get_mime_type() == "video/x-ms-wmv" && "wmv File");		
	att1 = attachment("test.avi", "");
	assert(att1.get_mime_type() == "video/x-msvideo" && "avi File");	
	att1 = attachment("test.flv", "");
	assert(att1.get_mime_type() == "video/x-flv" && "flv File");
	att1 = attachment("test.webm", "");
	assert(att1.get_mime_type() == "video/webm" && "webm File");
	//Archives
	att1 = attachment("test.zip", "");
	assert(att1.get_mime_type() == "application/zip" && "zip Archive");
	att1 = attachment("test.rar", "");
	assert(att1.get_mime_type() == "application/x-rar-compressed" && "rar Archive");
	//Documents
	att1 = attachment("test.odt", "");
	assert(att1.get_mime_type() == "application/vnd.oasis.opendocument.text" && "odt Document");
	att1 = attachment("test.ods", "");
	assert(att1.get_mime_type() == "application/vnd.oasis.opendocument.spreadsheet" && "ods Document");
	att1 = attachment("test.odp", "");
	assert(att1.get_mime_type() == "application/vnd.oasis.opendocument.presentation" && "odp Document");
	att1 = attachment("test.odg", "");
	assert(att1.get_mime_type() == "application/vnd.oasis.opendocument.graphics" && "odg Document");
	att1 = attachment("test.xls", "");
	assert(att1.get_mime_type() == "application/vnd.ms-excel" && "xls Document");
	att1 = attachment("test.xlm", "");
	assert(att1.get_mime_type() == "application/vnd.ms-excel" && "xlm Document");
	att1 = attachment("test.xla", "");
	assert(att1.get_mime_type() == "application/vnd.ms-excel" && "xla Document");
	att1 = attachment("test.xlc", "");
	assert(att1.get_mime_type() == "application/vnd.ms-excel" && "xlc Document");
	att1 = attachment("test.xlt", "");
	assert(att1.get_mime_type() == "application/vnd.ms-excel" && "xlt Document");
	att1 = attachment("test.xlw", "");
	assert(att1.get_mime_type() == "application/vnd.ms-excel" && "xlw Document");
	att1 = attachment("test.xlam", "");
	assert(att1.get_mime_type() == "application/vnd.ms-excel.addin.macroenabled.12" && "xlam Document");
	att1 = attachment("test.xlsb", "");
	assert(att1.get_mime_type() == "application/vnd.ms-excel.sheet.binary.macroenabled.12" && "xlsb Document");
	att1 = attachment("test.xlsm", "");
	assert(att1.get_mime_type() == "application/vnd.ms-excel.sheet.macroenabled.12" && "xlsm Document");
	att1 = attachment("test.xltm", "");
	assert(att1.get_mime_type() == "application/vnd.ms-excel.template.macroenabled.12" && "xltm Document");
	att1 = attachment("test.xlsx", "");
	assert(att1.get_mime_type() == "application/vnd.openxmlformats-officedocument.spreadsheetml.sheet" && "xlsx Document");
	att1 = attachment("test.xltx", "");
	assert(att1.get_mime_type() == "application/vnd.openxmlformats-officedocument.spreadsheetml.template" && "xltx Document");
	att1 = attachment("test.ppt", "");
	assert(att1.get_mime_type() == "application/vnd.ms-powerpoint" && "ppt Document");
	att1 = attachment("test.pps", "");
	assert(att1.get_mime_type() == "application/vnd.ms-powerpoint" && "pps Document");
	att1 = attachment("test.pot", "");
	assert(att1.get_mime_type() == "application/vnd.ms-powerpoint" && "pot Document");
	att1 = attachment("test.ppam", "");
	assert(att1.get_mime_type() == "application/vnd.ms-powerpoint.addin.macroenabled.12" && "ppam Document");
	att1 = attachment("test.pptm", "");
	assert(att1.get_mime_type() == "application/vnd.ms-powerpoint.presentation.macroenabled.12" && "pptm Document");
	att1 = attachment("test.sldm", "");
	assert(att1.get_mime_type() == "application/vnd.ms-powerpoint.slide.macroenabled.12" && "sldm Document");
	att1 = attachment("test.ppsm", "");
	assert(att1.get_mime_type() == "application/vnd.ms-powerpoint.slideshow.macroenabled.12" && "ppsm Document");
	att1 = attachment("test.potm", "");
	assert(att1.get_mime_type() == "application/vnd.ms-powerpoint.template.macroenabled.12" && "potm Document");
	att1 = attachment("test.pptx", "");
	assert(att1.get_mime_type() == "application/vnd.openxmlformats-officedocument.presentationml.presentation" && "pptx Document");
	att1 = attachment("test.sldx", "");
	assert(att1.get_mime_type() == "application/vnd.openxmlformats-officedocument.presentationml.slide" && "sldx Document");
	att1 = attachment("test.ppsx", "");
	assert(att1.get_mime_type() == "application/vnd.openxmlformats-officedocument.presentationml.slideshow" && "ppsx Document");
	att1 = attachment("test.potx", "");
	assert(att1.get_mime_type() == "application/vnd.openxmlformats-officedocument.presentationml.template" && "potx Document");
	att1 = attachment("test.doc", "");
	assert(att1.get_mime_type() == "application/msword" && "doc Document");
	att1 = attachment("test.dot", "");
	assert(att1.get_mime_type() == "application/msword" && "dot Document");
	att1 = attachment("test.docx", "");
	assert(att1.get_mime_type() == "application/vnd.openxmlformats-officedocument.wordprocessingml.document" && "docx Document");
	att1 = attachment("test.dotx", "");
	assert(att1.get_mime_type() == "application/vnd.openxmlformats-officedocument.wordprocessingml.template" && "dotx Document");
	att1 = attachment("test.xul", "");
	assert(att1.get_mime_type() == "application/vnd.mozilla.xul+xml" && "xul Document");}

void attachment_unittest()
{
	test_attachement_constructor();
	test_attachment_getmimetype();
}