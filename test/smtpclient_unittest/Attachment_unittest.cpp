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
	assert(_stricmp(att1.get_mime_type(), "image/png") == 0 && "png Image");
	att1 = attachment("test.jpg", "");
	assert(_stricmp(att1.get_mime_type(), "image/jpeg") == 0 && "jpg Image");
	att1 = attachment("test.jpeg", "");
	assert(_stricmp(att1.get_mime_type(), "image/jpeg") == 0 && "jpeg Image");
	att1 = attachment("test.jpe", "");
	assert(_stricmp(att1.get_mime_type(), "image/jpeg") == 0 && "jpe Image");
	att1 = attachment("test.gif", "");
	assert(_stricmp(att1.get_mime_type(), "image/gif") == 0 && "gif Image");
	att1 = attachment("test.tif", "");
	assert(_stricmp(att1.get_mime_type(), "image/tiff") == 0 && "tif Image");
	att1 = attachment("test.tiff", "");
	assert(_stricmp(att1.get_mime_type(), "image/tiff") == 0 && "tiff Image");
	att1 = attachment("test.ico", "");
	assert(_stricmp(att1.get_mime_type(), "image/x-icon") == 0 && "ico Image");
	//Applications
	att1 = attachment("test.xml", "");
	assert(_stricmp(att1.get_mime_type(), "application/xml") == 0 && "xml Document");
	att1 = attachment("test.xsl", "");
	assert(_stricmp(att1.get_mime_type(), "application/xml") == 0 && "xsl Document");
	att1 = attachment("test.xhtml", "");
	assert(_stricmp(att1.get_mime_type(), "application/xhtml+xml") == 0 && "xhtml Document");	
	att1 = attachment("test.xht", "");
	assert(_stricmp(att1.get_mime_type(), "application/xhtml+xml") == 0 && "xht Document");
	att1 = attachment("test.pdf", "");
	assert(_stricmp(att1.get_mime_type(), "application/pdf") == 0 && "pdf Document");	
	att1 = attachment("test.js", "");
	assert(_stricmp(att1.get_mime_type(), "application/javascript") == 0 && "js Document");	
	//Text
	att1 = attachment("test.css", "");
	assert(_stricmp(att1.get_mime_type(), "text/css") == 0 && "css File");
	att1 = attachment("test.csv", "");
	assert(_stricmp(att1.get_mime_type(), "text/csv") == 0 && "csv File");
	att1 = attachment("test.html", "");
	assert(_stricmp(att1.get_mime_type(), "text/html") == 0 && "html File");
	att1 = attachment("test.htm", "");
	assert(_stricmp(att1.get_mime_type(), "text/html") == 0 && "htm File");
	att1 = attachment("test.txt", "");
	assert(_stricmp(att1.get_mime_type(), "text/plain") == 0 && "txt File");
	att1 = attachment("test.text", "");
	assert(_stricmp(att1.get_mime_type(), "text/plain") == 0 && "text File");
	att1 = attachment("test.conf", "");
	assert(_stricmp(att1.get_mime_type(), "text/plain") == 0 && "conf File");
	att1 = attachment("test.def", "");
	assert(_stricmp(att1.get_mime_type(), "text/plain") == 0 && "def File");
	att1 = attachment("test.list", "");
	assert(_stricmp(att1.get_mime_type(), "text/plain") == 0 && "list File");
	att1 = attachment("test.log", "");
	assert(_stricmp(att1.get_mime_type(), "text/plain") == 0 && "log File");
	att1 = attachment("test.in", "");
	assert(_stricmp(att1.get_mime_type(), "text/plain") == 0 && "in File");
	//Videos
	att1 = attachment("test.mpeg", "");
	assert(_stricmp(att1.get_mime_type(), "video/mpeg") == 0 && "mpeg File");
	att1 = attachment("test.mpg", "");
	assert(_stricmp(att1.get_mime_type(), "video/mpeg") == 0 && "mpg File");
	att1 = attachment("test.mpe", "");
	assert(_stricmp(att1.get_mime_type(), "video/mpeg") == 0 && "mpe File");
	att1 = attachment("test.m1v", "");
	assert(_stricmp(att1.get_mime_type(), "video/mpeg") == 0 && "m1v File");
	att1 = attachment("test.m2v", "");
	assert(_stricmp(att1.get_mime_type(), "video/mpeg") == 0 && "m2v File");
	att1 = attachment("test.mp4", "");
	assert(_stricmp(att1.get_mime_type(), "video/mp4") == 0 && "mp4 File");
	att1 = attachment("test.mp4v", "");
	assert(_stricmp(att1.get_mime_type(), "video/mp4") == 0 && "mp4v File");
	att1 = attachment("test.mpg4", "");
	assert(_stricmp(att1.get_mime_type(), "video/mp4") == 0 && "mpg4 File");
	att1 = attachment("test.qt", "");
	assert(_stricmp(att1.get_mime_type(), "video/quicktime") == 0 && "qt File");
	att1 = attachment("test.mov", "");
	assert(_stricmp(att1.get_mime_type(), "video/quicktime") == 0 && "mov File");	
	att1 = attachment("test.wmv", "");
	assert(_stricmp(att1.get_mime_type(), "video/x-ms-wmv") == 0 && "wmv File");		
	att1 = attachment("test.avi", "");
	assert(_stricmp(att1.get_mime_type(), "video/x-msvideo") == 0 && "avi File");	
	att1 = attachment("test.flv", "");
	assert(_stricmp(att1.get_mime_type(), "video/x-flv") == 0 && "flv File");
	att1 = attachment("test.webm", "");
	assert(_stricmp(att1.get_mime_type(), "video/webm") == 0 && "webm File");
	//Archives
	att1 = attachment("test.zip", "");
	assert(_stricmp(att1.get_mime_type(), "application/zip") == 0 && "zip Archive");
	att1 = attachment("test.rar", "");
	assert(_stricmp(att1.get_mime_type(), "application/x-rar-compressed") == 0 && "rar Archive");
	//Documents
	att1 = attachment("test.odt", "");
	assert(_stricmp(att1.get_mime_type(), "application/vnd.oasis.opendocument.text") == 0 && "odt Document");
	att1 = attachment("test.ods", "");
	assert(_stricmp(att1.get_mime_type(), "application/vnd.oasis.opendocument.spreadsheet") == 0 && "ods Document");
	att1 = attachment("test.odp", "");
	assert(_stricmp(att1.get_mime_type(), "application/vnd.oasis.opendocument.presentation") == 0 && "odp Document");
	att1 = attachment("test.odg", "");
	assert(_stricmp(att1.get_mime_type(), "application/vnd.oasis.opendocument.graphics") == 0 && "odg Document");
	att1 = attachment("test.xls", "");
	assert(_stricmp(att1.get_mime_type(), "application/vnd.ms-excel") == 0 && "xls Document");
	att1 = attachment("test.xlm", "");
	assert(_stricmp(att1.get_mime_type(), "application/vnd.ms-excel") == 0 && "xlm Document");
	att1 = attachment("test.xla", "");
	assert(_stricmp(att1.get_mime_type(), "application/vnd.ms-excel") == 0 && "xla Document");
	att1 = attachment("test.xlc", "");
	assert(_stricmp(att1.get_mime_type(), "application/vnd.ms-excel") == 0 && "xlc Document");
	att1 = attachment("test.xlt", "");
	assert(_stricmp(att1.get_mime_type(), "application/vnd.ms-excel") == 0 && "xlt Document");
	att1 = attachment("test.xlw", "");
	assert(_stricmp(att1.get_mime_type(), "application/vnd.ms-excel") == 0 && "xlw Document");
	att1 = attachment("test.xlam", "");
	assert(_stricmp(att1.get_mime_type(), "application/vnd.ms-excel.addin.macroenabled.12") == 0 && "xlam Document");
	att1 = attachment("test.xlsb", "");
	assert(_stricmp(att1.get_mime_type(), "application/vnd.ms-excel.sheet.binary.macroenabled.12") == 0 && "xlsb Document");
	att1 = attachment("test.xlsm", "");
	assert(_stricmp(att1.get_mime_type(), "application/vnd.ms-excel.sheet.macroenabled.12") == 0 && "xlsm Document");
	att1 = attachment("test.xltm", "");
	assert(_stricmp(att1.get_mime_type(), "application/vnd.ms-excel.template.macroenabled.12") == 0 && "xltm Document");
	att1 = attachment("test.xlsx", "");
	assert(_stricmp(att1.get_mime_type(), "application/vnd.openxmlformats-officedocument.spreadsheetml.sheet") == 0 && "xlsx Document");
	att1 = attachment("test.xltx", "");
	assert(_stricmp(att1.get_mime_type(), "application/vnd.openxmlformats-officedocument.spreadsheetml.template") == 0 && "xltx Document");
	att1 = attachment("test.ppt", "");
	assert(_stricmp(att1.get_mime_type(), "application/vnd.ms-powerpoint") == 0 && "ppt Document");
	att1 = attachment("test.pps", "");
	assert(_stricmp(att1.get_mime_type(), "application/vnd.ms-powerpoint") == 0 && "pps Document");
	att1 = attachment("test.pot", "");
	assert(_stricmp(att1.get_mime_type(), "application/vnd.ms-powerpoint") == 0 && "pot Document");
	att1 = attachment("test.ppam", "");
	assert(_stricmp(att1.get_mime_type(), "application/vnd.ms-powerpoint.addin.macroenabled.12") == 0 && "ppam Document");
	att1 = attachment("test.pptm", "");
	assert(_stricmp(att1.get_mime_type(), "application/vnd.ms-powerpoint.presentation.macroenabled.12") == 0 && "pptm Document");
	att1 = attachment("test.sldm", "");
	assert(_stricmp(att1.get_mime_type(), "application/vnd.ms-powerpoint.slide.macroenabled.12") == 0 && "sldm Document");
	att1 = attachment("test.ppsm", "");
	assert(_stricmp(att1.get_mime_type(), "application/vnd.ms-powerpoint.slideshow.macroenabled.12") == 0 && "ppsm Document");
	att1 = attachment("test.potm", "");
	assert(_stricmp(att1.get_mime_type(), "application/vnd.ms-powerpoint.template.macroenabled.12") == 0 && "potm Document");
	att1 = attachment("test.pptx", "");
	assert(_stricmp(att1.get_mime_type(), "application/vnd.openxmlformats-officedocument.presentationml.presentation") == 0 && "pptx Document");
	att1 = attachment("test.sldx", "");
	assert(_stricmp(att1.get_mime_type(), "application/vnd.openxmlformats-officedocument.presentationml.slide") == 0 && "sldx Document");
	att1 = attachment("test.ppsx", "");
	assert(_stricmp(att1.get_mime_type(), "application/vnd.openxmlformats-officedocument.presentationml.slideshow") == 0 && "ppsx Document");
	att1 = attachment("test.potx", "");
	assert(_stricmp(att1.get_mime_type(), "application/vnd.openxmlformats-officedocument.presentationml.template") == 0 && "potx Document");
	att1 = attachment("test.doc", "");
	assert(_stricmp(att1.get_mime_type(), "application/msword") == 0 && "doc Document");
	att1 = attachment("test.dot", "");
	assert(_stricmp(att1.get_mime_type(), "application/msword") == 0 && "dot Document");
	att1 = attachment("test.docx", "");
	assert(_stricmp(att1.get_mime_type(), "application/vnd.openxmlformats-officedocument.wordprocessingml.document") == 0 && "docx Document");
	att1 = attachment("test.dotx", "");
	assert(_stricmp(att1.get_mime_type(), "application/vnd.openxmlformats-officedocument.wordprocessingml.template") == 0 && "dotx Document");
	att1 = attachment("test.xul", "");
	assert(_stricmp(att1.get_mime_type(), "application/vnd.mozilla.xul+xml") == 0 && "xul Document");
}

void attachment_unittest()
{
	test_attachement_constructor();
	test_attachment_getmimetype();
}