#include <gtest/gtest.h>
#include "../../src/attachment.h"

using namespace jed_utils;

TEST(Attachment_Constructor, FailEmptyFileName) {
    // Test with empty filename
    try {
        Attachment att1("", "");
        FAIL();
    }
    catch(std::invalid_argument) {
    }
}

TEST(Attachment_Constructor, FailWhiteSpaceFileName) {
    // Test with empty filename
    try {
        Attachment att1("   ", "");
        FAIL();
    }
    catch(std::invalid_argument) {
    }
}

TEST(Attachment_Constructor, ValidParam) {
    Attachment att1("test.png", "");
}

TEST(Attachment_CopyConstructor, AttachmentCopyConstructorValid) {
    Attachment att1("test.png", "Test");
    Attachment att2(att1);
    ASSERT_STREQ("test.png", att1.getFilename());
    ASSERT_STREQ("Test", att1.getName());
    ASSERT_STREQ("test.png", att2.getFilename());
    ASSERT_STREQ("Test", att2.getName());
}

TEST(Attachment_CopyAssignment, AttachmentCopyAssignmentValid) {
    Attachment att1("test.png", "123");
    Attachment att2("aaa.png", "bbb");
    att2 = att1;
    ASSERT_STREQ("test.png", att1.getFilename());
    ASSERT_STREQ("123", att1.getName());
    ASSERT_STREQ("test.png", att2.getFilename());
    ASSERT_STREQ("123", att2.getName());
}

TEST(Attachment_MoveConstructor, AttachmentMoveConstructorValid) {
    Attachment att1("test.png", "123");
    Attachment att2(std::move(att1));
    ASSERT_STREQ("test.png", att2.getFilename());
    ASSERT_STREQ("123", att2.getName());
}

TEST(Attachment_MoveAssignment, AttachmentMoveAssignmentValid) {
    Attachment att1("test.png", "123");
    Attachment att2("aaa.png", "bbb");
    att2 = std::move(att1);
    ASSERT_STREQ("test.png", att2.getFilename());
    ASSERT_STREQ("123", att2.getName());
}

TEST(Attachment_getmimetype_images, png) {
    Attachment att1("test.png", "");
    ASSERT_STREQ(att1.getMimeType(), "image/png");
}

TEST(Attachment_getmimetype_images, jpg) {
    Attachment att1("test.jpg", "");
    ASSERT_STREQ(att1.getMimeType(), "image/jpeg");
}

TEST(Attachment_getmimetype_images, jpeg) {
    Attachment att1("test.jpeg", "");
    ASSERT_STREQ(att1.getMimeType(), "image/jpeg");
}

TEST(Attachment_getmimetype_images, jpe) {
    Attachment att1("test.jpe", "");
    ASSERT_STREQ(att1.getMimeType(), "image/jpeg");
}

TEST(Attachment_getmimetype_images, gif) {
    Attachment att1("test.gif", "");
    ASSERT_STREQ(att1.getMimeType(), "image/gif");
}

TEST(Attachment_getmimetype_images, tif) {
    Attachment att1("test.tif", "");
    ASSERT_STREQ(att1.getMimeType(), "image/tiff");
}

TEST(Attachment_getmimetype_images, tiff) {
    Attachment att1("test.tiff", "");
    ASSERT_STREQ(att1.getMimeType(), "image/tiff");
}

TEST(Attachment_getmimetype_images, ico) {
    Attachment att1("test.ico", "");
    ASSERT_STREQ(att1.getMimeType(), "image/x-icon");
}

TEST(Attachment_getmimetype_applications, xml) {
    Attachment att1("test.xml", "");
    ASSERT_STREQ(att1.getMimeType(), "application/xml");
}

TEST(Attachment_getmimetype_applications, xsl) {
    Attachment att1("test.xsl", "");
    ASSERT_STREQ(att1.getMimeType(), "application/xml");
}

TEST(Attachment_getmimetype_applications, xhtml) {
    Attachment att1("test.xhtml", "");
    ASSERT_STREQ(att1.getMimeType(), "application/xhtml+xml");
}

TEST(Attachment_getmimetype_applications, xht) {
    Attachment att1("test.xht", "");
    ASSERT_STREQ(att1.getMimeType(), "application/xhtml+xml");
}
TEST(Attachment_getmimetype_applications, pdf) {
    Attachment att1("test.pdf", "");
    ASSERT_STREQ(att1.getMimeType(), "application/pdf");
}

TEST(Attachment_getmimetype_applications, js) {
    Attachment att1("test.js", "");
    ASSERT_STREQ(att1.getMimeType(), "application/javascript");
}

TEST(Attachment_getmimetype_text, css) {
    Attachment att1("test.css", "");
    ASSERT_STREQ(att1.getMimeType(), "text/css");
}

TEST(Attachment_getmimetype_text, csv) {
    Attachment att1("test.csv", "");
    ASSERT_STREQ(att1.getMimeType(), "text/csv");
}

TEST(Attachment_getmimetype_text, html) {
    Attachment att1("test.html", "");
    ASSERT_STREQ(att1.getMimeType(), "text/html");
}

TEST(Attachment_getmimetype_text, htm) {
    Attachment att1("test.htm", "");
    ASSERT_STREQ(att1.getMimeType(), "text/html");
}

TEST(Attachment_getmimetype_text, txt) {
    Attachment att1("test.txt", "");
    ASSERT_STREQ(att1.getMimeType(), "text/plain");
}

TEST(Attachment_getmimetype_text, text) {
    Attachment att1("test.text", "");
    ASSERT_STREQ(att1.getMimeType(), "text/plain");
}

TEST(Attachment_getmimetype_text, conf) {
    Attachment att1("test.conf", "");
    ASSERT_STREQ(att1.getMimeType(), "text/plain");
}

TEST(Attachment_getmimetype_text, def) {
    Attachment att1("test.def", "");
    ASSERT_STREQ(att1.getMimeType(), "text/plain");
}

TEST(Attachment_getmimetype_text, list) {
    Attachment att1("test.list", "");
    ASSERT_STREQ(att1.getMimeType(), "text/plain");
}

TEST(Attachment_getmimetype_text, log) {
    Attachment att1("test.log", "");
    ASSERT_STREQ(att1.getMimeType(), "text/plain");
}

TEST(Attachment_getmimetype_text, in) {
    Attachment att1("test.in", "");
    ASSERT_STREQ(att1.getMimeType(), "text/plain");
}

TEST(Attachment_getmimetype_videos, mpeg) {
    Attachment att1("test.mpeg", "");
    ASSERT_STREQ(att1.getMimeType(), "video/mpeg");
}

TEST(Attachment_getmimetype_videos, mpg) {
    Attachment att1("test.mpg", "");
    ASSERT_STREQ(att1.getMimeType(), "video/mpeg");
}

TEST(Attachment_getmimetype_videos, mpe) {
    Attachment att1("test.mpe", "");
    ASSERT_STREQ(att1.getMimeType(), "video/mpeg");
}

TEST(Attachment_getmimetype_videos, m1v) {
    Attachment att1("test.m1v", "");
    ASSERT_STREQ(att1.getMimeType(), "video/mpeg");
}

TEST(Attachment_getmimetype_videos, m2v) {
    Attachment att1("test.m2v", "");
    ASSERT_STREQ(att1.getMimeType(), "video/mpeg");
}

TEST(Attachment_getmimetype_videos, mp4) {
    Attachment att1("test.mp4", "");
    ASSERT_STREQ(att1.getMimeType(), "video/mp4");
}

TEST(Attachment_getmimetype_videos, mp4v) {
    Attachment att1("test.mp4v", "");
    ASSERT_STREQ(att1.getMimeType(), "video/mp4");
}

TEST(Attachment_getmimetype_videos, mpg4) {
    Attachment att1("test.mpg4", "");
    ASSERT_STREQ(att1.getMimeType(), "video/mp4");
}

TEST(Attachment_getmimetype_videos, qt) {
    Attachment att1("test.qt", "");
    ASSERT_STREQ(att1.getMimeType(), "video/quicktime");
}

TEST(Attachment_getmimetype_videos, mov) {
    Attachment att1("test.mov", "");
    ASSERT_STREQ(att1.getMimeType(), "video/quicktime");
}

TEST(Attachment_getmimetype_videos, wmv) {
    Attachment att1("test.wmv", "");
    ASSERT_STREQ(att1.getMimeType(), "video/x-ms-wmv");
}

TEST(Attachment_getmimetype_videos, avi) {
    Attachment att1("test.avi", "");
    ASSERT_STREQ(att1.getMimeType(), "video/x-msvideo");
}

TEST(Attachment_getmimetype_videos, flv) {
    Attachment att1("test.flv", "");
    ASSERT_STREQ(att1.getMimeType(), "video/x-flv");
}

TEST(Attachment_getmimetype_videos, webm) {
    Attachment att1("test.webm", "");
    ASSERT_STREQ(att1.getMimeType(), "video/webm");
}

TEST(Attachment_getmimetype_archives, zip) {
    // Archives
    Attachment att1("test.zip", "");
    ASSERT_STREQ(att1.getMimeType(), "application/zip");
}

TEST(Attachment_getmimetype_archives, rar) {
    Attachment att1("test.rar", "");
    ASSERT_STREQ(att1.getMimeType(), "application/x-rar-compressed");
}

TEST(Attachment_getmimetype_documents, odt) {
    Attachment att1("test.odt", "");
    ASSERT_STREQ(att1.getMimeType(), "application/vnd.oasis.opendocument.text");
}

TEST(Attachment_getmimetype_documents, ods) {
    Attachment att1("test.ods", "");
    ASSERT_STREQ(att1.getMimeType(), "application/vnd.oasis.opendocument.spreadsheet");
}

TEST(Attachment_getmimetype_documents, odp) {
    Attachment att1("test.odp", "");
    ASSERT_STREQ(att1.getMimeType(), "application/vnd.oasis.opendocument.presentation");
}

TEST(Attachment_getmimetype_documents, odg) {
    Attachment att1("test.odg", "");
    ASSERT_STREQ(att1.getMimeType(), "application/vnd.oasis.opendocument.graphics");
}

TEST(Attachment_getmimetype_documents, xls) {
    Attachment att1("test.xls", "");
    ASSERT_STREQ(att1.getMimeType(), "application/vnd.ms-excel");
}

TEST(Attachment_getmimetype_documents, xlm) {
    Attachment att1("test.xlm", "");
    ASSERT_STREQ(att1.getMimeType(), "application/vnd.ms-excel");
}

TEST(Attachment_getmimetype_documents, xla) {
    Attachment att1("test.xla", "");
    ASSERT_STREQ(att1.getMimeType(), "application/vnd.ms-excel");
}

TEST(Attachment_getmimetype_documents, xlc) {
    Attachment att1("test.xlc", "");
    ASSERT_STREQ(att1.getMimeType(), "application/vnd.ms-excel");
}

TEST(Attachment_getmimetype_documents, xlt) {
    Attachment att1("test.xlt", "");
    ASSERT_STREQ(att1.getMimeType(), "application/vnd.ms-excel");
}

TEST(Attachment_getmimetype_documents, xlw) {
    Attachment att1("test.xlw", "");
    ASSERT_STREQ(att1.getMimeType(), "application/vnd.ms-excel");
}

TEST(Attachment_getmimetype_documents, xlam) {
    Attachment att1("test.xlam", "");
    ASSERT_STREQ(att1.getMimeType(), "application/vnd.ms-excel.addin.macroenabled.12");
}

TEST(Attachment_getmimetype_documents, xlsb) {
    Attachment att1("test.xlsb", "");
    ASSERT_STREQ(att1.getMimeType(), "application/vnd.ms-excel.sheet.binary.macroenabled.12");
}

TEST(Attachment_getmimetype_documents, xlsm) {
    Attachment att1("test.xlsm", "");
    ASSERT_STREQ(att1.getMimeType(), "application/vnd.ms-excel.sheet.macroenabled.12");
}

TEST(Attachment_getmimetype_documents, xltm) {
    Attachment att1("test.xltm", "");
    ASSERT_STREQ(att1.getMimeType(), "application/vnd.ms-excel.template.macroenabled.12");
}

TEST(Attachment_getmimetype_documents, xlsx) {
    Attachment att1("test.xlsx", "");
    ASSERT_STREQ(att1.getMimeType(), "application/vnd.openxmlformats-officedocument.spreadsheetml.sheet");
}

TEST(Attachment_getmimetype_documents, xltx) {
    Attachment att1("test.xltx", "");
    ASSERT_STREQ(att1.getMimeType(), "application/vnd.openxmlformats-officedocument.spreadsheetml.template");
}

TEST(Attachment_getmimetype_documents, ppt) {
    Attachment att1("test.ppt", "");
    ASSERT_STREQ(att1.getMimeType(), "application/vnd.ms-powerpoint");
}

TEST(Attachment_getmimetype_documents, pps) {
    Attachment att1("test.pps", "");
    ASSERT_STREQ(att1.getMimeType(), "application/vnd.ms-powerpoint");
}

TEST(Attachment_getmimetype_documents, pot) {
    Attachment att1("test.pot", "");
    ASSERT_STREQ(att1.getMimeType(), "application/vnd.ms-powerpoint");
}

TEST(Attachment_getmimetype_documents, ppam) {
    Attachment att1("test.ppam", "");
    ASSERT_STREQ(att1.getMimeType(), "application/vnd.ms-powerpoint.addin.macroenabled.12");
}

TEST(Attachment_getmimetype_documents, pptm) {
    Attachment att1("test.pptm", "");
    ASSERT_STREQ(att1.getMimeType(), "application/vnd.ms-powerpoint.presentation.macroenabled.12");
}

TEST(Attachment_getmimetype_documents, sldm) {
    Attachment att1("test.sldm", "");
    ASSERT_STREQ(att1.getMimeType(), "application/vnd.ms-powerpoint.slide.macroenabled.12");
}

TEST(Attachment_getmimetype_documents, ppsm) {
    Attachment att1("test.ppsm", "");
    ASSERT_STREQ(att1.getMimeType(), "application/vnd.ms-powerpoint.slideshow.macroenabled.12");
}

TEST(Attachment_getmimetype_documents, potm) {
    Attachment att1("test.potm", "");
    ASSERT_STREQ(att1.getMimeType(), "application/vnd.ms-powerpoint.template.macroenabled.12");
}

TEST(Attachment_getmimetype_documents, pptx) {
    Attachment att1("test.pptx", "");
    ASSERT_STREQ(att1.getMimeType(), "application/vnd.openxmlformats-officedocument.presentationml.presentation");
}

TEST(Attachment_getmimetype_documents, sldx) {
    Attachment att1("test.sldx", "");
    ASSERT_STREQ(att1.getMimeType(), "application/vnd.openxmlformats-officedocument.presentationml.slide");
}

TEST(Attachment_getmimetype_documents, ppsx) {
    Attachment att1("test.ppsx", "");
    ASSERT_STREQ(att1.getMimeType(), "application/vnd.openxmlformats-officedocument.presentationml.slideshow");
}

TEST(Attachment_getmimetype_documents, potx) {
    Attachment att1("test.potx", "");
    ASSERT_STREQ(att1.getMimeType(), "application/vnd.openxmlformats-officedocument.presentationml.template");
}

TEST(Attachment_getmimetype_documents, doc) {
    Attachment att1("test.doc", "");
    ASSERT_STREQ(att1.getMimeType(), "application/msword");
}

TEST(Attachment_getmimetype_documents, dot) {
    Attachment att1("test.dot", "");
    ASSERT_STREQ(att1.getMimeType(), "application/msword");
}

TEST(Attachment_getmimetype_documents, docx) {
    Attachment att1("test.docx", "");
    ASSERT_STREQ(att1.getMimeType(), "application/vnd.openxmlformats-officedocument.wordprocessingml.document");
}

TEST(Attachment_getmimetype_documents, dotx) {
    Attachment att1("test.dotx", "");
    ASSERT_STREQ(att1.getMimeType(), "application/vnd.openxmlformats-officedocument.wordprocessingml.template");
}

TEST(Attachment_getmimetype_documents, xul) {
    Attachment att1("test.xul", "");
    ASSERT_STREQ(att1.getMimeType(), "application/vnd.mozilla.xul+xml");
}

TEST(Attachment_getBase64EncodedFile_NonExsitantFile, ReturnNullPTR) {
    Attachment att1("C:\\NonExistantfile.txt", "");
    ASSERT_EQ(att1.getBase64EncodedFile(), nullptr);
}

