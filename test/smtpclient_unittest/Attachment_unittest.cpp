#include <gtest/gtest.h>
#include "../../Include/Attachment.h"
#include "Attachment.h"


using namespace jed_utils;
using namespace std;

TEST(Attachment_Constructor, FailEmptyParam)
{
	//Test with empty filename
	try
	{
		attachment att1("", "");
		FAIL();
	}
	catch(invalid_argument) 
	{
	}
}

TEST(Attachment_Constructor, ValidParam)
{
	attachment att1("test.png", "");
}

TEST(Attachment_getmimetype_images, png)
{
	attachment att1("test.png", "");
	ASSERT_EQ(_stricmp(att1.get_mime_type(), "image/png"), 0);
}

TEST(Attachment_getmimetype_images, jpg)
{
	attachment att1("test.jpg", "");
	ASSERT_EQ(_stricmp(att1.get_mime_type(), "image/jpeg"), 0);
}

TEST(Attachment_getmimetype_images, jpeg)
{
	attachment att1("test.jpeg", "");
	ASSERT_EQ(_stricmp(att1.get_mime_type(), "image/jpeg"), 0);
}
TEST(Attachment_getmimetype_images, jpe)
{
	attachment att1("test.jpe", "");
	ASSERT_EQ(_stricmp(att1.get_mime_type(), "image/jpeg") , 0);
}

TEST(Attachment_getmimetype_images, gif)
{
	attachment att1("test.gif", "");
	ASSERT_EQ(_stricmp(att1.get_mime_type(), "image/gif") , 0);
}

TEST(Attachment_getmimetype_images, tif)
{
	attachment att1("test.tif", "");
	ASSERT_EQ(_stricmp(att1.get_mime_type(), "image/tiff") , 0);
}

TEST(Attachment_getmimetype_images, tiff)
{
	attachment att1("test.tiff", "");
	ASSERT_EQ(_stricmp(att1.get_mime_type(), "image/tiff") , 0);
}

TEST(Attachment_getmimetype_images, ico)
{
	attachment att1("test.ico", "");
	ASSERT_EQ(_stricmp(att1.get_mime_type(), "image/x-icon") , 0);
}

TEST(Attachment_getmimetype_applications, xml)
{
	attachment att1("test.xml", "");
	ASSERT_EQ(_stricmp(att1.get_mime_type(), "application/xml") , 0);
}

TEST(Attachment_getmimetype_applications, xsl)
{
	attachment att1("test.xsl", "");
	ASSERT_EQ(_stricmp(att1.get_mime_type(), "application/xml") , 0);
}

TEST(Attachment_getmimetype_applications, xhtml)
{
	attachment att1("test.xhtml", "");
	ASSERT_EQ(_stricmp(att1.get_mime_type(), "application/xhtml+xml") , 0);	
}

TEST(Attachment_getmimetype_applications, xht)
{
	attachment att1("test.xht", "");
	ASSERT_EQ(_stricmp(att1.get_mime_type(), "application/xhtml+xml") , 0);
}
TEST(Attachment_getmimetype_applications, pdf)
{
	attachment att1("test.pdf", "");
	ASSERT_EQ(_stricmp(att1.get_mime_type(), "application/pdf") , 0);	
}

TEST(Attachment_getmimetype_applications, js)
{
	attachment att1("test.js", "");
	ASSERT_EQ(_stricmp(att1.get_mime_type(), "application/javascript") , 0);	
}

TEST(Attachment_getmimetype_text, css)
{
	attachment att1("test.css", "");
	ASSERT_EQ(_stricmp(att1.get_mime_type(), "text/css") , 0);
}

TEST(Attachment_getmimetype_text, csv)
{
	attachment att1("test.csv", "");
	ASSERT_EQ(_stricmp(att1.get_mime_type(), "text/csv") , 0);
}

TEST(Attachment_getmimetype_text, html)
{
	attachment att1("test.html", "");
	ASSERT_EQ(_stricmp(att1.get_mime_type(), "text/html") , 0);
}

TEST(Attachment_getmimetype_text, htm)
{
	attachment att1("test.htm", "");
	ASSERT_EQ(_stricmp(att1.get_mime_type(), "text/html") , 0);
}

TEST(Attachment_getmimetype_text, txt)
{
	attachment att1("test.txt", "");
	ASSERT_EQ(_stricmp(att1.get_mime_type(), "text/plain") , 0);
}

TEST(Attachment_getmimetype_text, text)
{
	attachment att1("test.text", "");
	ASSERT_EQ(_stricmp(att1.get_mime_type(), "text/plain") , 0);
}

TEST(Attachment_getmimetype_text, conf)
{
	attachment att1("test.conf", "");
	ASSERT_EQ(_stricmp(att1.get_mime_type(), "text/plain") , 0);
}

TEST(Attachment_getmimetype_text, def)
{
	attachment att1("test.def", "");
	ASSERT_EQ(_stricmp(att1.get_mime_type(), "text/plain") , 0);
}

TEST(Attachment_getmimetype_text, list)
{
	attachment att1("test.list", "");
	ASSERT_EQ(_stricmp(att1.get_mime_type(), "text/plain") , 0);
}

TEST(Attachment_getmimetype_text, log)
{
	attachment att1("test.log", "");
	ASSERT_EQ(_stricmp(att1.get_mime_type(), "text/plain") , 0);
}

TEST(Attachment_getmimetype_text, in)
{
	attachment att1("test.in", "");
	ASSERT_EQ(_stricmp(att1.get_mime_type(), "text/plain") , 0);
}

TEST(Attachment_getmimetype_videos, mpeg)
{
	attachment att1("test.mpeg", "");
	ASSERT_EQ(_stricmp(att1.get_mime_type(), "video/mpeg") , 0);
}

TEST(Attachment_getmimetype_videos, mpg)
{
	attachment att1("test.mpg", "");
	ASSERT_EQ(_stricmp(att1.get_mime_type(), "video/mpeg") , 0);
}

TEST(Attachment_getmimetype_videos, mpe)
{
	attachment att1("test.mpe", "");
	ASSERT_EQ(_stricmp(att1.get_mime_type(), "video/mpeg") , 0);
}

TEST(Attachment_getmimetype_videos, m1v)
{
	attachment att1("test.m1v", "");
	ASSERT_EQ(_stricmp(att1.get_mime_type(), "video/mpeg") , 0);
}

TEST(Attachment_getmimetype_videos, m2v)
{
	attachment att1("test.m2v", "");
	ASSERT_EQ(_stricmp(att1.get_mime_type(), "video/mpeg") , 0);
}

TEST(Attachment_getmimetype_videos, mp4)
{
	attachment att1("test.mp4", "");
	ASSERT_EQ(_stricmp(att1.get_mime_type(), "video/mp4") , 0);
}

TEST(Attachment_getmimetype_videos, mp4v)
{
	attachment att1("test.mp4v", "");
	ASSERT_EQ(_stricmp(att1.get_mime_type(), "video/mp4") , 0);
}

TEST(Attachment_getmimetype_videos, mpg4)
{
	attachment att1("test.mpg4", "");
	ASSERT_EQ(_stricmp(att1.get_mime_type(), "video/mp4") , 0);
}

TEST(Attachment_getmimetype_videos, qt)
{
	attachment att1("test.qt", "");
	ASSERT_EQ(_stricmp(att1.get_mime_type(), "video/quicktime") , 0);
}

TEST(Attachment_getmimetype_videos, mov)
{
	attachment att1("test.mov", "");
	ASSERT_EQ(_stricmp(att1.get_mime_type(), "video/quicktime") , 0);	
}

TEST(Attachment_getmimetype_videos, wmv)
{
	attachment att1("test.wmv", "");
	ASSERT_EQ(_stricmp(att1.get_mime_type(), "video/x-ms-wmv") , 0);		
}

TEST(Attachment_getmimetype_videos, avi)
{
	attachment att1("test.avi", "");
	ASSERT_EQ(_stricmp(att1.get_mime_type(), "video/x-msvideo") , 0);	
}

TEST(Attachment_getmimetype_videos, flv)
{
	attachment att1("test.flv", "");
	ASSERT_EQ(_stricmp(att1.get_mime_type(), "video/x-flv") , 0);
}

TEST(Attachment_getmimetype_videos, webm)
{
	attachment att1("test.webm", "");
	ASSERT_EQ(_stricmp(att1.get_mime_type(), "video/webm") , 0);
}

TEST(Attachment_getmimetype_archives, zip)
{
	//Archives
	attachment att1("test.zip", "");
	ASSERT_EQ(_stricmp(att1.get_mime_type(), "application/zip") , 0);
}

TEST(Attachment_getmimetype_archives, rar)
{
	attachment att1("test.rar", "");
	ASSERT_EQ(_stricmp(att1.get_mime_type(), "application/x-rar-compressed") , 0);
}

TEST(Attachment_getmimetype_documents, odt)
{
	attachment att1("test.odt", "");
	ASSERT_EQ(_stricmp(att1.get_mime_type(), "application/vnd.oasis.opendocument.text") , 0);
}

TEST(Attachment_getmimetype_documents, ods)
{
	attachment att1("test.ods", "");
	ASSERT_EQ(_stricmp(att1.get_mime_type(), "application/vnd.oasis.opendocument.spreadsheet") , 0);
}

TEST(Attachment_getmimetype_documents, odp)
{
	attachment att1("test.odp", "");
	ASSERT_EQ(_stricmp(att1.get_mime_type(), "application/vnd.oasis.opendocument.presentation") , 0);
}

TEST(Attachment_getmimetype_documents, odg)
{
	attachment att1("test.odg", "");
	ASSERT_EQ(_stricmp(att1.get_mime_type(), "application/vnd.oasis.opendocument.graphics") , 0);
}

TEST(Attachment_getmimetype_documents, xls)
{
	attachment att1("test.xls", "");
	ASSERT_EQ(_stricmp(att1.get_mime_type(), "application/vnd.ms-excel") , 0);
}

TEST(Attachment_getmimetype_documents, xlm)
{
	attachment att1("test.xlm", "");
	ASSERT_EQ(_stricmp(att1.get_mime_type(), "application/vnd.ms-excel") , 0);
}

TEST(Attachment_getmimetype_documents, xla)
{
	attachment att1("test.xla", "");
	ASSERT_EQ(_stricmp(att1.get_mime_type(), "application/vnd.ms-excel") , 0);
}

TEST(Attachment_getmimetype_documents, xlc)
{
	attachment att1("test.xlc", "");
	ASSERT_EQ(_stricmp(att1.get_mime_type(), "application/vnd.ms-excel") , 0);
}

TEST(Attachment_getmimetype_documents, xlt)
{
	attachment att1("test.xlt", "");
	ASSERT_EQ(_stricmp(att1.get_mime_type(), "application/vnd.ms-excel") , 0);
}

TEST(Attachment_getmimetype_documents, xlw)
{
	attachment att1("test.xlw", "");
	ASSERT_EQ(_stricmp(att1.get_mime_type(), "application/vnd.ms-excel") , 0);
}

TEST(Attachment_getmimetype_documents, xlam)
{
	attachment att1("test.xlam", "");
	ASSERT_EQ(_stricmp(att1.get_mime_type(), "application/vnd.ms-excel.addin.macroenabled.12") , 0);
}

TEST(Attachment_getmimetype_documents, xlsb)
{
	attachment att1("test.xlsb", "");
	ASSERT_EQ(_stricmp(att1.get_mime_type(), "application/vnd.ms-excel.sheet.binary.macroenabled.12") , 0);
}

TEST(Attachment_getmimetype_documents, xlsm)
{
	attachment att1("test.xlsm", "");
	ASSERT_EQ(_stricmp(att1.get_mime_type(), "application/vnd.ms-excel.sheet.macroenabled.12") , 0);
}

TEST(Attachment_getmimetype_documents, xltm)
{
	attachment att1("test.xltm", "");
	ASSERT_EQ(_stricmp(att1.get_mime_type(), "application/vnd.ms-excel.template.macroenabled.12") , 0);
}

TEST(Attachment_getmimetype_documents, xlsx)
{
	attachment att1("test.xlsx", "");
	ASSERT_EQ(_stricmp(att1.get_mime_type(), "application/vnd.openxmlformats-officedocument.spreadsheetml.sheet") , 0);
}

TEST(Attachment_getmimetype_documents, xltx)
{
	attachment att1("test.xltx", "");
	ASSERT_EQ(_stricmp(att1.get_mime_type(), "application/vnd.openxmlformats-officedocument.spreadsheetml.template") , 0);
}

TEST(Attachment_getmimetype_documents, ppt)
{
	attachment att1("test.ppt", "");
	ASSERT_EQ(_stricmp(att1.get_mime_type(), "application/vnd.ms-powerpoint") , 0);
}

TEST(Attachment_getmimetype_documents, pps)
{
	attachment att1("test.pps", "");
	ASSERT_EQ(_stricmp(att1.get_mime_type(), "application/vnd.ms-powerpoint") , 0);
}

TEST(Attachment_getmimetype_documents, pot)
{
	attachment att1("test.pot", "");
	ASSERT_EQ(_stricmp(att1.get_mime_type(), "application/vnd.ms-powerpoint") , 0);
}

TEST(Attachment_getmimetype_documents, ppam)
{
	attachment att1("test.ppam", "");
	ASSERT_EQ(_stricmp(att1.get_mime_type(), "application/vnd.ms-powerpoint.addin.macroenabled.12") , 0);
}

TEST(Attachment_getmimetype_documents, pptm)
{
	attachment att1("test.pptm", "");
	ASSERT_EQ(_stricmp(att1.get_mime_type(), "application/vnd.ms-powerpoint.presentation.macroenabled.12") , 0);
}

TEST(Attachment_getmimetype_documents, sldm)
{
	attachment att1("test.sldm", "");
	ASSERT_EQ(_stricmp(att1.get_mime_type(), "application/vnd.ms-powerpoint.slide.macroenabled.12") , 0);
}

TEST(Attachment_getmimetype_documents, ppsm)
{
	attachment att1("test.ppsm", "");
	ASSERT_EQ(_stricmp(att1.get_mime_type(), "application/vnd.ms-powerpoint.slideshow.macroenabled.12") , 0);
}

TEST(Attachment_getmimetype_documents, potm)
{
	attachment att1("test.potm", "");
	ASSERT_EQ(_stricmp(att1.get_mime_type(), "application/vnd.ms-powerpoint.template.macroenabled.12") , 0);
}

TEST(Attachment_getmimetype_documents, pptx)
{
	attachment att1("test.pptx", "");
	ASSERT_EQ(_stricmp(att1.get_mime_type(), "application/vnd.openxmlformats-officedocument.presentationml.presentation") , 0);
}

TEST(Attachment_getmimetype_documents, sldx)
{
	attachment att1("test.sldx", "");
	ASSERT_EQ(_stricmp(att1.get_mime_type(), "application/vnd.openxmlformats-officedocument.presentationml.slide") , 0);
}

TEST(Attachment_getmimetype_documents, ppsx)
{
	attachment att1("test.ppsx", "");
	ASSERT_EQ(_stricmp(att1.get_mime_type(), "application/vnd.openxmlformats-officedocument.presentationml.slideshow") , 0);
}

TEST(Attachment_getmimetype_documents, potx)
{
	attachment att1("test.potx", "");
	ASSERT_EQ(_stricmp(att1.get_mime_type(), "application/vnd.openxmlformats-officedocument.presentationml.template") , 0);
}

TEST(Attachment_getmimetype_documents, doc)
{
	attachment att1("test.doc", "");
	ASSERT_EQ(_stricmp(att1.get_mime_type(), "application/msword") , 0);
}

TEST(Attachment_getmimetype_documents, dot)
{
	attachment att1("test.dot", "");
	ASSERT_EQ(_stricmp(att1.get_mime_type(), "application/msword") , 0);
}

TEST(Attachment_getmimetype_documents, docx)
{
	attachment att1("test.docx", "");
	ASSERT_EQ(_stricmp(att1.get_mime_type(), "application/vnd.openxmlformats-officedocument.wordprocessingml.document") , 0);
}

TEST(Attachment_getmimetype_documents, dotx)
{
	attachment att1("test.dotx", "");
	ASSERT_EQ(_stricmp(att1.get_mime_type(), "application/vnd.openxmlformats-officedocument.wordprocessingml.template") , 0);
}

TEST(Attachment_getmimetype_documents, xul)
{
	attachment att1("test.xul", "");
	ASSERT_EQ(_stricmp(att1.get_mime_type(), "application/vnd.mozilla.xul+xml") , 0);
}