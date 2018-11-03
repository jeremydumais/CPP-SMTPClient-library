#include <gtest/gtest.h>
#include "../../Include/Attachment.h"

using namespace jed_utils;
using namespace std;

TEST(Attachment_Constructor, FailEmptyParam)
{
	//Test with empty filename
	try
	{
		Attachment att1("", "");
		FAIL();
	}
	catch(invalid_argument) 
	{
	}
}

TEST(Attachment_Constructor, ValidParam)
{
	Attachment att1("test.png", "");
}

TEST(Attachment_getmimetype_images, png)
{
	Attachment att1("test.png", "");
	ASSERT_EQ(_stricmp(att1.getMimeType(), "image/png"), 0);
}

TEST(Attachment_getmimetype_images, jpg)
{
	Attachment att1("test.jpg", "");
	ASSERT_EQ(_stricmp(att1.getMimeType(), "image/jpeg"), 0);
}

TEST(Attachment_getmimetype_images, jpeg)
{
	Attachment att1("test.jpeg", "");
	ASSERT_EQ(_stricmp(att1.getMimeType(), "image/jpeg"), 0);
}
TEST(Attachment_getmimetype_images, jpe)
{
	Attachment att1("test.jpe", "");
	ASSERT_EQ(_stricmp(att1.getMimeType(), "image/jpeg") , 0);
}

TEST(Attachment_getmimetype_images, gif)
{
	Attachment att1("test.gif", "");
	ASSERT_EQ(_stricmp(att1.getMimeType(), "image/gif") , 0);
}

TEST(Attachment_getmimetype_images, tif)
{
	Attachment att1("test.tif", "");
	ASSERT_EQ(_stricmp(att1.getMimeType(), "image/tiff") , 0);
}

TEST(Attachment_getmimetype_images, tiff)
{
	Attachment att1("test.tiff", "");
	ASSERT_EQ(_stricmp(att1.getMimeType(), "image/tiff") , 0);
}

TEST(Attachment_getmimetype_images, ico)
{
	Attachment att1("test.ico", "");
	ASSERT_EQ(_stricmp(att1.getMimeType(), "image/x-icon") , 0);
}

TEST(Attachment_getmimetype_applications, xml)
{
	Attachment att1("test.xml", "");
	ASSERT_EQ(_stricmp(att1.getMimeType(), "application/xml") , 0);
}

TEST(Attachment_getmimetype_applications, xsl)
{
	Attachment att1("test.xsl", "");
	ASSERT_EQ(_stricmp(att1.getMimeType(), "application/xml") , 0);
}

TEST(Attachment_getmimetype_applications, xhtml)
{
	Attachment att1("test.xhtml", "");
	ASSERT_EQ(_stricmp(att1.getMimeType(), "application/xhtml+xml") , 0);	
}

TEST(Attachment_getmimetype_applications, xht)
{
	Attachment att1("test.xht", "");
	ASSERT_EQ(_stricmp(att1.getMimeType(), "application/xhtml+xml") , 0);
}
TEST(Attachment_getmimetype_applications, pdf)
{
	Attachment att1("test.pdf", "");
	ASSERT_EQ(_stricmp(att1.getMimeType(), "application/pdf") , 0);	
}

TEST(Attachment_getmimetype_applications, js)
{
	Attachment att1("test.js", "");
	ASSERT_EQ(_stricmp(att1.getMimeType(), "application/javascript") , 0);	
}

TEST(Attachment_getmimetype_text, css)
{
	Attachment att1("test.css", "");
	ASSERT_EQ(_stricmp(att1.getMimeType(), "text/css") , 0);
}

TEST(Attachment_getmimetype_text, csv)
{
	Attachment att1("test.csv", "");
	ASSERT_EQ(_stricmp(att1.getMimeType(), "text/csv") , 0);
}

TEST(Attachment_getmimetype_text, html)
{
	Attachment att1("test.html", "");
	ASSERT_EQ(_stricmp(att1.getMimeType(), "text/html") , 0);
}

TEST(Attachment_getmimetype_text, htm)
{
	Attachment att1("test.htm", "");
	ASSERT_EQ(_stricmp(att1.getMimeType(), "text/html") , 0);
}

TEST(Attachment_getmimetype_text, txt)
{
	Attachment att1("test.txt", "");
	ASSERT_EQ(_stricmp(att1.getMimeType(), "text/plain") , 0);
}

TEST(Attachment_getmimetype_text, text)
{
	Attachment att1("test.text", "");
	ASSERT_EQ(_stricmp(att1.getMimeType(), "text/plain") , 0);
}

TEST(Attachment_getmimetype_text, conf)
{
	Attachment att1("test.conf", "");
	ASSERT_EQ(_stricmp(att1.getMimeType(), "text/plain") , 0);
}

TEST(Attachment_getmimetype_text, def)
{
	Attachment att1("test.def", "");
	ASSERT_EQ(_stricmp(att1.getMimeType(), "text/plain") , 0);
}

TEST(Attachment_getmimetype_text, list)
{
	Attachment att1("test.list", "");
	ASSERT_EQ(_stricmp(att1.getMimeType(), "text/plain") , 0);
}

TEST(Attachment_getmimetype_text, log)
{
	Attachment att1("test.log", "");
	ASSERT_EQ(_stricmp(att1.getMimeType(), "text/plain") , 0);
}

TEST(Attachment_getmimetype_text, in)
{
	Attachment att1("test.in", "");
	ASSERT_EQ(_stricmp(att1.getMimeType(), "text/plain") , 0);
}

TEST(Attachment_getmimetype_videos, mpeg)
{
	Attachment att1("test.mpeg", "");
	ASSERT_EQ(_stricmp(att1.getMimeType(), "video/mpeg") , 0);
}

TEST(Attachment_getmimetype_videos, mpg)
{
	Attachment att1("test.mpg", "");
	ASSERT_EQ(_stricmp(att1.getMimeType(), "video/mpeg") , 0);
}

TEST(Attachment_getmimetype_videos, mpe)
{
	Attachment att1("test.mpe", "");
	ASSERT_EQ(_stricmp(att1.getMimeType(), "video/mpeg") , 0);
}

TEST(Attachment_getmimetype_videos, m1v)
{
	Attachment att1("test.m1v", "");
	ASSERT_EQ(_stricmp(att1.getMimeType(), "video/mpeg") , 0);
}

TEST(Attachment_getmimetype_videos, m2v)
{
	Attachment att1("test.m2v", "");
	ASSERT_EQ(_stricmp(att1.getMimeType(), "video/mpeg") , 0);
}

TEST(Attachment_getmimetype_videos, mp4)
{
	Attachment att1("test.mp4", "");
	ASSERT_EQ(_stricmp(att1.getMimeType(), "video/mp4") , 0);
}

TEST(Attachment_getmimetype_videos, mp4v)
{
	Attachment att1("test.mp4v", "");
	ASSERT_EQ(_stricmp(att1.getMimeType(), "video/mp4") , 0);
}

TEST(Attachment_getmimetype_videos, mpg4)
{
	Attachment att1("test.mpg4", "");
	ASSERT_EQ(_stricmp(att1.getMimeType(), "video/mp4") , 0);
}

TEST(Attachment_getmimetype_videos, qt)
{
	Attachment att1("test.qt", "");
	ASSERT_EQ(_stricmp(att1.getMimeType(), "video/quicktime") , 0);
}

TEST(Attachment_getmimetype_videos, mov)
{
	Attachment att1("test.mov", "");
	ASSERT_EQ(_stricmp(att1.getMimeType(), "video/quicktime") , 0);	
}

TEST(Attachment_getmimetype_videos, wmv)
{
	Attachment att1("test.wmv", "");
	ASSERT_EQ(_stricmp(att1.getMimeType(), "video/x-ms-wmv") , 0);		
}

TEST(Attachment_getmimetype_videos, avi)
{
	Attachment att1("test.avi", "");
	ASSERT_EQ(_stricmp(att1.getMimeType(), "video/x-msvideo") , 0);	
}

TEST(Attachment_getmimetype_videos, flv)
{
	Attachment att1("test.flv", "");
	ASSERT_EQ(_stricmp(att1.getMimeType(), "video/x-flv") , 0);
}

TEST(Attachment_getmimetype_videos, webm)
{
	Attachment att1("test.webm", "");
	ASSERT_EQ(_stricmp(att1.getMimeType(), "video/webm") , 0);
}

TEST(Attachment_getmimetype_archives, zip)
{
	//Archives
	Attachment att1("test.zip", "");
	ASSERT_EQ(_stricmp(att1.getMimeType(), "application/zip") , 0);
}

TEST(Attachment_getmimetype_archives, rar)
{
	Attachment att1("test.rar", "");
	ASSERT_EQ(_stricmp(att1.getMimeType(), "application/x-rar-compressed") , 0);
}

TEST(Attachment_getmimetype_documents, odt)
{
	Attachment att1("test.odt", "");
	ASSERT_EQ(_stricmp(att1.getMimeType(), "application/vnd.oasis.opendocument.text") , 0);
}

TEST(Attachment_getmimetype_documents, ods)
{
	Attachment att1("test.ods", "");
	ASSERT_EQ(_stricmp(att1.getMimeType(), "application/vnd.oasis.opendocument.spreadsheet") , 0);
}

TEST(Attachment_getmimetype_documents, odp)
{
	Attachment att1("test.odp", "");
	ASSERT_EQ(_stricmp(att1.getMimeType(), "application/vnd.oasis.opendocument.presentation") , 0);
}

TEST(Attachment_getmimetype_documents, odg)
{
	Attachment att1("test.odg", "");
	ASSERT_EQ(_stricmp(att1.getMimeType(), "application/vnd.oasis.opendocument.graphics") , 0);
}

TEST(Attachment_getmimetype_documents, xls)
{
	Attachment att1("test.xls", "");
	ASSERT_EQ(_stricmp(att1.getMimeType(), "application/vnd.ms-excel") , 0);
}

TEST(Attachment_getmimetype_documents, xlm)
{
	Attachment att1("test.xlm", "");
	ASSERT_EQ(_stricmp(att1.getMimeType(), "application/vnd.ms-excel") , 0);
}

TEST(Attachment_getmimetype_documents, xla)
{
	Attachment att1("test.xla", "");
	ASSERT_EQ(_stricmp(att1.getMimeType(), "application/vnd.ms-excel") , 0);
}

TEST(Attachment_getmimetype_documents, xlc)
{
	Attachment att1("test.xlc", "");
	ASSERT_EQ(_stricmp(att1.getMimeType(), "application/vnd.ms-excel") , 0);
}

TEST(Attachment_getmimetype_documents, xlt)
{
	Attachment att1("test.xlt", "");
	ASSERT_EQ(_stricmp(att1.getMimeType(), "application/vnd.ms-excel") , 0);
}

TEST(Attachment_getmimetype_documents, xlw)
{
	Attachment att1("test.xlw", "");
	ASSERT_EQ(_stricmp(att1.getMimeType(), "application/vnd.ms-excel") , 0);
}

TEST(Attachment_getmimetype_documents, xlam)
{
	Attachment att1("test.xlam", "");
	ASSERT_EQ(_stricmp(att1.getMimeType(), "application/vnd.ms-excel.addin.macroenabled.12") , 0);
}

TEST(Attachment_getmimetype_documents, xlsb)
{
	Attachment att1("test.xlsb", "");
	ASSERT_EQ(_stricmp(att1.getMimeType(), "application/vnd.ms-excel.sheet.binary.macroenabled.12") , 0);
}

TEST(Attachment_getmimetype_documents, xlsm)
{
	Attachment att1("test.xlsm", "");
	ASSERT_EQ(_stricmp(att1.getMimeType(), "application/vnd.ms-excel.sheet.macroenabled.12") , 0);
}

TEST(Attachment_getmimetype_documents, xltm)
{
	Attachment att1("test.xltm", "");
	ASSERT_EQ(_stricmp(att1.getMimeType(), "application/vnd.ms-excel.template.macroenabled.12") , 0);
}

TEST(Attachment_getmimetype_documents, xlsx)
{
	Attachment att1("test.xlsx", "");
	ASSERT_EQ(_stricmp(att1.getMimeType(), "application/vnd.openxmlformats-officedocument.spreadsheetml.sheet") , 0);
}

TEST(Attachment_getmimetype_documents, xltx)
{
	Attachment att1("test.xltx", "");
	ASSERT_EQ(_stricmp(att1.getMimeType(), "application/vnd.openxmlformats-officedocument.spreadsheetml.template") , 0);
}

TEST(Attachment_getmimetype_documents, ppt)
{
	Attachment att1("test.ppt", "");
	ASSERT_EQ(_stricmp(att1.getMimeType(), "application/vnd.ms-powerpoint") , 0);
}

TEST(Attachment_getmimetype_documents, pps)
{
	Attachment att1("test.pps", "");
	ASSERT_EQ(_stricmp(att1.getMimeType(), "application/vnd.ms-powerpoint") , 0);
}

TEST(Attachment_getmimetype_documents, pot)
{
	Attachment att1("test.pot", "");
	ASSERT_EQ(_stricmp(att1.getMimeType(), "application/vnd.ms-powerpoint") , 0);
}

TEST(Attachment_getmimetype_documents, ppam)
{
	Attachment att1("test.ppam", "");
	ASSERT_EQ(_stricmp(att1.getMimeType(), "application/vnd.ms-powerpoint.addin.macroenabled.12") , 0);
}

TEST(Attachment_getmimetype_documents, pptm)
{
	Attachment att1("test.pptm", "");
	ASSERT_EQ(_stricmp(att1.getMimeType(), "application/vnd.ms-powerpoint.presentation.macroenabled.12") , 0);
}

TEST(Attachment_getmimetype_documents, sldm)
{
	Attachment att1("test.sldm", "");
	ASSERT_EQ(_stricmp(att1.getMimeType(), "application/vnd.ms-powerpoint.slide.macroenabled.12") , 0);
}

TEST(Attachment_getmimetype_documents, ppsm)
{
	Attachment att1("test.ppsm", "");
	ASSERT_EQ(_stricmp(att1.getMimeType(), "application/vnd.ms-powerpoint.slideshow.macroenabled.12") , 0);
}

TEST(Attachment_getmimetype_documents, potm)
{
	Attachment att1("test.potm", "");
	ASSERT_EQ(_stricmp(att1.getMimeType(), "application/vnd.ms-powerpoint.template.macroenabled.12") , 0);
}

TEST(Attachment_getmimetype_documents, pptx)
{
	Attachment att1("test.pptx", "");
	ASSERT_EQ(_stricmp(att1.getMimeType(), "application/vnd.openxmlformats-officedocument.presentationml.presentation") , 0);
}

TEST(Attachment_getmimetype_documents, sldx)
{
	Attachment att1("test.sldx", "");
	ASSERT_EQ(_stricmp(att1.getMimeType(), "application/vnd.openxmlformats-officedocument.presentationml.slide") , 0);
}

TEST(Attachment_getmimetype_documents, ppsx)
{
	Attachment att1("test.ppsx", "");
	ASSERT_EQ(_stricmp(att1.getMimeType(), "application/vnd.openxmlformats-officedocument.presentationml.slideshow") , 0);
}

TEST(Attachment_getmimetype_documents, potx)
{
	Attachment att1("test.potx", "");
	ASSERT_EQ(_stricmp(att1.getMimeType(), "application/vnd.openxmlformats-officedocument.presentationml.template") , 0);
}

TEST(Attachment_getmimetype_documents, doc)
{
	Attachment att1("test.doc", "");
	ASSERT_EQ(_stricmp(att1.getMimeType(), "application/msword") , 0);
}

TEST(Attachment_getmimetype_documents, dot)
{
	Attachment att1("test.dot", "");
	ASSERT_EQ(_stricmp(att1.getMimeType(), "application/msword") , 0);
}

TEST(Attachment_getmimetype_documents, docx)
{
	Attachment att1("test.docx", "");
	ASSERT_EQ(_stricmp(att1.getMimeType(), "application/vnd.openxmlformats-officedocument.wordprocessingml.document") , 0);
}

TEST(Attachment_getmimetype_documents, dotx)
{
	Attachment att1("test.dotx", "");
	ASSERT_EQ(_stricmp(att1.getMimeType(), "application/vnd.openxmlformats-officedocument.wordprocessingml.template") , 0);
}

TEST(Attachment_getmimetype_documents, xul)
{
	Attachment att1("test.xul", "");
	ASSERT_EQ(_stricmp(att1.getMimeType(), "application/vnd.mozilla.xul+xml") , 0);
}