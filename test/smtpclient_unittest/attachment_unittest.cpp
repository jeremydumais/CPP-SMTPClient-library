#include "gtest/gtest.h"
#include <gtest/gtest.h>
#include "../../src/attachment.h"
#include "../../src/cpp/attachment.hpp"

using namespace jed_utils;

template <typename T>
class MultiAttachmentFixture : public ::testing::Test {
 public:
    MultiAttachmentFixture<T>()
        : att("test.png", "test") {
    }
    T att;
};

using MyTypes = ::testing::Types<Attachment, cpp::Attachment>;
TYPED_TEST_SUITE(MultiAttachmentFixture, MyTypes);

TYPED_TEST(MultiAttachmentFixture, Constructor_FailEmptyFileName) {
    // Test with empty filename
    try {
        TypeParam att1("", "");
        FAIL();
    }
    catch(std::invalid_argument) {
    }
}

TYPED_TEST(MultiAttachmentFixture, Constructor_FailWhiteSpaceFileName) {
    // Test with empty filename
    try {
        TypeParam att1("   ", "");
        FAIL();
    }
    catch(std::invalid_argument) {
    }
}

TYPED_TEST(MultiAttachmentFixture, Constructor_ValidParam) {
    TypeParam att1("test.png", "");
}

TYPED_TEST(MultiAttachmentFixture, Constructor_ValidParamAndCID) {
    TypeParam att1("test.png", "", "CID1@localhost");
}

TYPED_TEST(MultiAttachmentFixture, CopyConstructor_AttachmentCopyConstructorValid) {
    TypeParam att1("test.png", "Test", "CID1@localhost");
    TypeParam att2(att1);
    ASSERT_EQ("test.png", std::string(att1.getFilename()));
    ASSERT_EQ("Test", std::string(att1.getName()));
    ASSERT_EQ("CID1@localhost", std::string(att1.getContentId()));
    ASSERT_EQ("test.png", std::string(att2.getFilename()));
    ASSERT_EQ("Test", std::string(att2.getName()));
    ASSERT_EQ("CID1@localhost", std::string(att2.getContentId()));
}

TYPED_TEST(MultiAttachmentFixture, CopyAssignment_AttachmentCopyAssignmentValid) {
    TypeParam att1("test.png", "123", "CID1@localhost");
    TypeParam att2("aaa.png", "bbb", "CID2@localhost");
    att2 = att1;
    ASSERT_EQ("test.png", std::string(att1.getFilename()));
    ASSERT_EQ("123", std::string(att1.getName()));
    ASSERT_EQ("CID1@localhost", std::string(att1.getContentId()));
    ASSERT_EQ("test.png", std::string(att2.getFilename()));
    ASSERT_EQ("123", std::string(att2.getName()));
    ASSERT_EQ("CID1@localhost", std::string(att2.getContentId()));
}

TYPED_TEST(MultiAttachmentFixture, MoveConstructor_AttachmentMoveConstructorValid) {
    TypeParam att1("test.png", "123", "CID1@localhost");
    TypeParam att2(std::move(att1));
    ASSERT_EQ("test.png", std::string(att2.getFilename()));
    ASSERT_EQ("123", std::string(att2.getName()));
    ASSERT_EQ("CID1@localhost", std::string(att2.getContentId()));
}

TYPED_TEST(MultiAttachmentFixture, MoveAssignment_AttachmentMoveAssignmentValid) {
    TypeParam att1("test.png", "123", "CID1@localhost");
    TypeParam att2("aaa.png", "bbb");
    att2 = std::move(att1);
    ASSERT_EQ("test.png", std::string(att2.getFilename()));
    ASSERT_EQ("123", std::string(att2.getName()));
    ASSERT_EQ("CID1@localhost", std::string(att2.getContentId()));
}

TYPED_TEST(MultiAttachmentFixture, getContentId_with_test_at_localhost_ReturnValid) {
    TypeParam att("test.png", "test", "test@localhost");
    ASSERT_EQ("test@localhost", std::string(att.getContentId()));
}

TYPED_TEST(MultiAttachmentFixture, setContentId_with_test2_at_localhost_ReturnValid) {
    TypeParam att("test.png", "test", "test@localhost");
    ASSERT_EQ("test@localhost", std::string(att.getContentId()));
    att.setContentId("test2@localhost");
    ASSERT_EQ("test2@localhost", std::string(att.getContentId()));
}

TYPED_TEST(MultiAttachmentFixture, setContentId_with_empty_ReturnValid) {
    TypeParam att("test.png", "test", "test@localhost");
    ASSERT_EQ("test@localhost", std::string(att.getContentId()));
    att.setContentId("");
    ASSERT_EQ("", std::string(att.getContentId()));
}

TYPED_TEST(MultiAttachmentFixture, getmimetype_images_png) {
    TypeParam att1("test.png", "");
    ASSERT_EQ(std::string(att1.getMimeType()), "image/png");
}

TYPED_TEST(MultiAttachmentFixture, getmimetype_images_jpg) {
    TypeParam att1("test.jpg", "");
    ASSERT_EQ(std::string(att1.getMimeType()), "image/jpeg");
}

TYPED_TEST(MultiAttachmentFixture, getmimetype_images_jpeg) {
    TypeParam att1("test.jpeg", "");
    ASSERT_EQ(std::string(att1.getMimeType()), "image/jpeg");
}

TYPED_TEST(MultiAttachmentFixture, getmimetype_images_jpe) {
    TypeParam att1("test.jpe", "");
    ASSERT_EQ(std::string(att1.getMimeType()), "image/jpeg");
}

TYPED_TEST(MultiAttachmentFixture, getmimetype_images_gif) {
    TypeParam att1("test.gif", "");
    ASSERT_EQ(std::string(att1.getMimeType()), "image/gif");
}

TYPED_TEST(MultiAttachmentFixture, getmimetype_images_tif) {
    TypeParam att1("test.tif", "");
    ASSERT_EQ(std::string(att1.getMimeType()), "image/tiff");
}

TYPED_TEST(MultiAttachmentFixture, getmimetype_images_tiff) {
    TypeParam att1("test.tiff", "");
    ASSERT_EQ(std::string(att1.getMimeType()), "image/tiff");
}

TYPED_TEST(MultiAttachmentFixture, getmimetype_images_ico) {
    TypeParam att1("test.ico", "");
    ASSERT_EQ(std::string(att1.getMimeType()), "image/x-icon");
}

TYPED_TEST(MultiAttachmentFixture, getmimetype_applications_xml) {
    TypeParam att1("test.xml", "");
    ASSERT_EQ(std::string(att1.getMimeType()), "application/xml");
}

TYPED_TEST(MultiAttachmentFixture, getmimetype_applications_xsl) {
    TypeParam att1("test.xsl", "");
    ASSERT_EQ(std::string(att1.getMimeType()), "application/xml");
}

TYPED_TEST(MultiAttachmentFixture, getmimetype_applications_xhtml) {
    TypeParam att1("test.xhtml", "");
    ASSERT_EQ(std::string(att1.getMimeType()), "application/xhtml+xml");
}

TYPED_TEST(MultiAttachmentFixture, getmimetype_applications_xht) {
    TypeParam att1("test.xht", "");
    ASSERT_EQ(std::string(att1.getMimeType()), "application/xhtml+xml");
}
TYPED_TEST(MultiAttachmentFixture, getmimetype_applications_pdf) {
    TypeParam att1("test.pdf", "");
    ASSERT_EQ(std::string(att1.getMimeType()), "application/pdf");
}

TYPED_TEST(MultiAttachmentFixture, getmimetype_applications_js) {
    TypeParam att1("test.js", "");
    ASSERT_EQ(std::string(att1.getMimeType()), "application/javascript");
}

TYPED_TEST(MultiAttachmentFixture, getmimetype_text_css) {
    TypeParam att1("test.css", "");
    ASSERT_EQ(std::string(att1.getMimeType()), "text/css");
}

TYPED_TEST(MultiAttachmentFixture, getmimetype_text_csv) {
    TypeParam att1("test.csv", "");
    ASSERT_EQ(std::string(att1.getMimeType()), "text/csv");
}

TYPED_TEST(MultiAttachmentFixture, getmimetype_text_html) {
    TypeParam att1("test.html", "");
    ASSERT_EQ(std::string(att1.getMimeType()), "text/html");
}

TYPED_TEST(MultiAttachmentFixture, getmimetype_text_htm) {
    TypeParam att1("test.htm", "");
    ASSERT_EQ(std::string(att1.getMimeType()), "text/html");
}

TYPED_TEST(MultiAttachmentFixture, getmimetype_text_txt) {
    TypeParam att1("test.txt", "");
    ASSERT_EQ(std::string(att1.getMimeType()), "text/plain");
}

TYPED_TEST(MultiAttachmentFixture, getmimetype_text_text) {
    TypeParam att1("test.text", "");
    ASSERT_EQ(std::string(att1.getMimeType()), "text/plain");
}

TYPED_TEST(MultiAttachmentFixture, getmimetype_text_conf) {
    TypeParam att1("test.conf", "");
    ASSERT_EQ(std::string(att1.getMimeType()), "text/plain");
}

TYPED_TEST(MultiAttachmentFixture, getmimetype_text_def) {
    TypeParam att1("test.def", "");
    ASSERT_EQ(std::string(att1.getMimeType()), "text/plain");
}

TYPED_TEST(MultiAttachmentFixture, getmimetype_text_list) {
    TypeParam att1("test.list", "");
    ASSERT_EQ(std::string(att1.getMimeType()), "text/plain");
}

TYPED_TEST(MultiAttachmentFixture, getmimetype_text_log) {
    TypeParam att1("test.log", "");
    ASSERT_EQ(std::string(att1.getMimeType()), "text/plain");
}

TYPED_TEST(MultiAttachmentFixture, getmimetype_text_in) {
    TypeParam att1("test.in", "");
    ASSERT_EQ(std::string(att1.getMimeType()), "text/plain");
}

TYPED_TEST(MultiAttachmentFixture, getmimetype_videos_mpeg) {
    TypeParam att1("test.mpeg", "");
    ASSERT_EQ(std::string(att1.getMimeType()), "video/mpeg");
}

TYPED_TEST(MultiAttachmentFixture, getmimetype_videos_mpg) {
    TypeParam att1("test.mpg", "");
    ASSERT_EQ(std::string(att1.getMimeType()), "video/mpeg");
}

TYPED_TEST(MultiAttachmentFixture, getmimetype_videos_mpe) {
    TypeParam att1("test.mpe", "");
    ASSERT_EQ(std::string(att1.getMimeType()), "video/mpeg");
}

TYPED_TEST(MultiAttachmentFixture, getmimetype_videos_m1v) {
    TypeParam att1("test.m1v", "");
    ASSERT_EQ(std::string(att1.getMimeType()), "video/mpeg");
}

TYPED_TEST(MultiAttachmentFixture, getmimetype_videos_m2v) {
    TypeParam att1("test.m2v", "");
    ASSERT_EQ(std::string(att1.getMimeType()), "video/mpeg");
}

TYPED_TEST(MultiAttachmentFixture, getmimetype_videos_mp4) {
    TypeParam att1("test.mp4", "");
    ASSERT_EQ(std::string(att1.getMimeType()), "video/mp4");
}

TYPED_TEST(MultiAttachmentFixture, getmimetype_videos_mp4v) {
    TypeParam att1("test.mp4v", "");
    ASSERT_EQ(std::string(att1.getMimeType()), "video/mp4");
}

TYPED_TEST(MultiAttachmentFixture, getmimetype_videos_mpg4) {
    TypeParam att1("test.mpg4", "");
    ASSERT_EQ(std::string(att1.getMimeType()), "video/mp4");
}

TYPED_TEST(MultiAttachmentFixture, getmimetype_videos_qt) {
    TypeParam att1("test.qt", "");
    ASSERT_EQ(std::string(att1.getMimeType()), "video/quicktime");
}

TYPED_TEST(MultiAttachmentFixture, getmimetype_videos_mov) {
    TypeParam att1("test.mov", "");
    ASSERT_EQ(std::string(att1.getMimeType()), "video/quicktime");
}

TYPED_TEST(MultiAttachmentFixture, getmimetype_videos_wmv) {
    TypeParam att1("test.wmv", "");
    ASSERT_EQ(std::string(att1.getMimeType()), "video/x-ms-wmv");
}

TYPED_TEST(MultiAttachmentFixture, getmimetype_videos_avi) {
    TypeParam att1("test.avi", "");
    ASSERT_EQ(std::string(att1.getMimeType()), "video/x-msvideo");
}

TYPED_TEST(MultiAttachmentFixture, getmimetype_videos_flv) {
    TypeParam att1("test.flv", "");
    ASSERT_EQ(std::string(att1.getMimeType()), "video/x-flv");
}

TYPED_TEST(MultiAttachmentFixture, getmimetype_videos_webm) {
    TypeParam att1("test.webm", "");
    ASSERT_EQ(std::string(att1.getMimeType()), "video/webm");
}

TYPED_TEST(MultiAttachmentFixture, getmimetype_audio_wav) {
        TypeParam att1("test.wav", "");
            ASSERT_EQ(std::string(att1.getMimeType()), "audio/wav");
}

TYPED_TEST(MultiAttachmentFixture, getmimetype_audio_mp3) {
        TypeParam att1("test.mp3", "");
            ASSERT_EQ(std::string(att1.getMimeType()), "audio/mpeg");
}

TYPED_TEST(MultiAttachmentFixture, getmimetype_audio_ogg) {
        TypeParam att1("test.oga", "");
            ASSERT_EQ(std::string(att1.getMimeType()), "audio/ogg");
}

TYPED_TEST(MultiAttachmentFixture, getmimetype_audio_opus) {
        TypeParam att1("test.opus", "");
            ASSERT_EQ(std::string(att1.getMimeType()), "audio/opus");
}

TYPED_TEST(MultiAttachmentFixture, getmimetype_audio_aac) {
        TypeParam att1("test.aac", "");
            ASSERT_EQ(std::string(att1.getMimeType()), "audio/aac");
}

TYPED_TEST(MultiAttachmentFixture, getmimetype_archives_zip) {
    TypeParam att1("test.zip", "");
    ASSERT_EQ(std::string(att1.getMimeType()), "application/zip");
}

TYPED_TEST(MultiAttachmentFixture, getmimetype_archives_rar) {
    TypeParam att1("test.rar", "");
    ASSERT_EQ(std::string(att1.getMimeType()), "application/x-rar-compressed");
}

TYPED_TEST(MultiAttachmentFixture, getmimetype_documents_odt) {
    TypeParam att1("test.odt", "");
    ASSERT_EQ(std::string(att1.getMimeType()), "application/vnd.oasis.opendocument.text");
}

TYPED_TEST(MultiAttachmentFixture, getmimetype_documents_ods) {
    TypeParam att1("test.ods", "");
    ASSERT_EQ(std::string(att1.getMimeType()), "application/vnd.oasis.opendocument.spreadsheet");
}

TYPED_TEST(MultiAttachmentFixture, getmimetype_documents_odp) {
    TypeParam att1("test.odp", "");
    ASSERT_EQ(std::string(att1.getMimeType()), "application/vnd.oasis.opendocument.presentation");
}

TYPED_TEST(MultiAttachmentFixture, getmimetype_documents_odg) {
    TypeParam att1("test.odg", "");
    ASSERT_EQ(std::string(att1.getMimeType()), "application/vnd.oasis.opendocument.graphics");
}

TYPED_TEST(MultiAttachmentFixture, getmimetype_documents_xls) {
    TypeParam att1("test.xls", "");
    ASSERT_EQ(std::string(att1.getMimeType()), "application/vnd.ms-excel");
}

TYPED_TEST(MultiAttachmentFixture, getmimetype_documents_xlm) {
    TypeParam att1("test.xlm", "");
    ASSERT_EQ(std::string(att1.getMimeType()), "application/vnd.ms-excel");
}

TYPED_TEST(MultiAttachmentFixture, getmimetype_documents_xla) {
    TypeParam att1("test.xla", "");
    ASSERT_EQ(std::string(att1.getMimeType()), "application/vnd.ms-excel");
}

TYPED_TEST(MultiAttachmentFixture, getmimetype_documents_xlc) {
    TypeParam att1("test.xlc", "");
    ASSERT_EQ(std::string(att1.getMimeType()), "application/vnd.ms-excel");
}

TYPED_TEST(MultiAttachmentFixture, getmimetype_documents_xlt) {
    TypeParam att1("test.xlt", "");
    ASSERT_EQ(std::string(att1.getMimeType()), "application/vnd.ms-excel");
}

TYPED_TEST(MultiAttachmentFixture, getmimetype_documents_xlw) {
    TypeParam att1("test.xlw", "");
    ASSERT_EQ(std::string(att1.getMimeType()), "application/vnd.ms-excel");
}

TYPED_TEST(MultiAttachmentFixture, getmimetype_documents_xlam) {
    TypeParam att1("test.xlam", "");
    ASSERT_EQ(std::string(att1.getMimeType()), "application/vnd.ms-excel.addin.macroenabled.12");
}

TYPED_TEST(MultiAttachmentFixture, getmimetype_documents_xlsb) {
    TypeParam att1("test.xlsb", "");
    ASSERT_EQ(std::string(att1.getMimeType()), "application/vnd.ms-excel.sheet.binary.macroenabled.12");
}

TYPED_TEST(MultiAttachmentFixture, getmimetype_documents_xlsm) {
    TypeParam att1("test.xlsm", "");
    ASSERT_EQ(std::string(att1.getMimeType()), "application/vnd.ms-excel.sheet.macroenabled.12");
}

TYPED_TEST(MultiAttachmentFixture, getmimetype_documents_xltm) {
    TypeParam att1("test.xltm", "");
    ASSERT_EQ(std::string(att1.getMimeType()), "application/vnd.ms-excel.template.macroenabled.12");
}

TYPED_TEST(MultiAttachmentFixture, getmimetype_documents_xlsx) {
    TypeParam att1("test.xlsx", "");
    ASSERT_EQ(std::string(att1.getMimeType()), "application/vnd.openxmlformats-officedocument.spreadsheetml.sheet");
}

TYPED_TEST(MultiAttachmentFixture, getmimetype_documents_xltx) {
    TypeParam att1("test.xltx", "");
    ASSERT_EQ(std::string(att1.getMimeType()), "application/vnd.openxmlformats-officedocument.spreadsheetml.template");
}

TYPED_TEST(MultiAttachmentFixture, getmimetype_documents_ppt) {
    TypeParam att1("test.ppt", "");
    ASSERT_EQ(std::string(att1.getMimeType()), "application/vnd.ms-powerpoint");
}

TYPED_TEST(MultiAttachmentFixture, getmimetype_documents_pps) {
    TypeParam att1("test.pps", "");
    ASSERT_EQ(std::string(att1.getMimeType()), "application/vnd.ms-powerpoint");
}

TYPED_TEST(MultiAttachmentFixture, getmimetype_documents_pot) {
    TypeParam att1("test.pot", "");
    ASSERT_EQ(std::string(att1.getMimeType()), "application/vnd.ms-powerpoint");
}

TYPED_TEST(MultiAttachmentFixture, getmimetype_documents_ppam) {
    TypeParam att1("test.ppam", "");
    ASSERT_EQ(std::string(att1.getMimeType()), "application/vnd.ms-powerpoint.addin.macroenabled.12");
}

TYPED_TEST(MultiAttachmentFixture, getmimetype_documents_pptm) {
    TypeParam att1("test.pptm", "");
    ASSERT_EQ(std::string(att1.getMimeType()), "application/vnd.ms-powerpoint.presentation.macroenabled.12");
}

TYPED_TEST(MultiAttachmentFixture, getmimetype_documents_sldm) {
    TypeParam att1("test.sldm", "");
    ASSERT_EQ(std::string(att1.getMimeType()), "application/vnd.ms-powerpoint.slide.macroenabled.12");
}

TYPED_TEST(MultiAttachmentFixture, getmimetype_documents_ppsm) {
    TypeParam att1("test.ppsm", "");
    ASSERT_EQ(std::string(att1.getMimeType()), "application/vnd.ms-powerpoint.slideshow.macroenabled.12");
}

TYPED_TEST(MultiAttachmentFixture, getmimetype_documents_potm) {
    TypeParam att1("test.potm", "");
    ASSERT_EQ(std::string(att1.getMimeType()), "application/vnd.ms-powerpoint.template.macroenabled.12");
}

TYPED_TEST(MultiAttachmentFixture, getmimetype_documents_pptx) {
    TypeParam att1("test.pptx", "");
    ASSERT_EQ(std::string(att1.getMimeType()), "application/vnd.openxmlformats-officedocument.presentationml.presentation");
}

TYPED_TEST(MultiAttachmentFixture, getmimetype_documents_sldx) {
    TypeParam att1("test.sldx", "");
    ASSERT_EQ(std::string(att1.getMimeType()), "application/vnd.openxmlformats-officedocument.presentationml.slide");
}

TYPED_TEST(MultiAttachmentFixture, getmimetype_documents_ppsx) {
    TypeParam att1("test.ppsx", "");
    ASSERT_EQ(std::string(att1.getMimeType()), "application/vnd.openxmlformats-officedocument.presentationml.slideshow");
}

TYPED_TEST(MultiAttachmentFixture, getmimetype_documents_potx) {
    TypeParam att1("test.potx", "");
    ASSERT_EQ(std::string(att1.getMimeType()), "application/vnd.openxmlformats-officedocument.presentationml.template");
}

TYPED_TEST(MultiAttachmentFixture, getmimetype_documents_doc) {
    TypeParam att1("test.doc", "");
    ASSERT_EQ(std::string(att1.getMimeType()), "application/msword");
}

TYPED_TEST(MultiAttachmentFixture, getmimetype_documents_dot) {
    TypeParam att1("test.dot", "");
    ASSERT_EQ(std::string(att1.getMimeType()), "application/msword");
}

TYPED_TEST(MultiAttachmentFixture, getmimetype_documents_docx) {
    TypeParam att1("test.docx", "");
    ASSERT_EQ(std::string(att1.getMimeType()), "application/vnd.openxmlformats-officedocument.wordprocessingml.document");
}

TYPED_TEST(MultiAttachmentFixture, getmimetype_documents_dotx) {
    TypeParam att1("test.dotx", "");
    ASSERT_EQ(std::string(att1.getMimeType()), "application/vnd.openxmlformats-officedocument.wordprocessingml.template");
}

TYPED_TEST(MultiAttachmentFixture, getmimetype_documents_xul) {
    TypeParam att1("test.xul", "");
    ASSERT_EQ(std::string(att1.getMimeType()), "application/vnd.mozilla.xul+xml");
}

TEST(Attachment, getBase64EncodedFile_NonExsitantFile_ReturnNullPTR) {
    Attachment att1("C:\\NonExistantfile.txt", "");
    ASSERT_EQ(att1.getBase64EncodedFile(), nullptr);
}

TEST(CPPAttachement, getBase64EncodedFile_NonExsitantFile_ReturnNullPTR) {
    cpp::Attachment att1("C:\\NonExistantfile.txt", "");
    ASSERT_EQ(att1.getBase64EncodedFile(), "");
}

