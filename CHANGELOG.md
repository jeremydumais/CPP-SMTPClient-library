# Changelog

All notable changes to this project will be documented in this file

## [1.1.8]

## Enhancement / Bug fixes
- Some SMTP server send their list of supported extensions in multiple
buffers like Zoho Mail. The EHLO command when in uncrypted mode, now supports
receiving multiple buffers. In return, a delay of one second must be added for
each segment sent by the SMTP server. For SMTP servers that send the list of
supported extensions in a single segment like Gmail and Live, no additional
delay is added for the EHLO command. This doesn't affect the other commands.
- Now when we send an email to multiple recipients (to or cc), the recipients
appears as a single mail header instead of multiple headers. The old method was
not RFC 5322 compliant.

  Before:

  To: test@example.com

  To: test2@example.com

  After:

  To: test@example.com, test2@example.com


## [1.1.7]

### Added
- Added an option in the Credential class to indicate the preferred
authentication option. Support for the XOAUTH2 authentication has also been
added.This change has been made by rcosnita (https://github.com/rcosnita).
Many thanks!
- Added a new flag in the different SMTP client classes to indicate whether we
want to send emails in batch (getBatchMode/setBatchMode). In this mode the connection to an
SMTP server will only be made once when the first email is sent and will
remain open until the client instance is destroy.
- Added the authentication feature on the SMTPClient class.
- Added a new flag on the ForcedSecureSMTPClient and OpportunisticSecureSMTPClient
to indicate whether we accept self signed certificate
(getAcceptSelfSignedCert/setAcceptSelfSignedCert).


### Enhancement / Bug fixes
The following changes have been made by ino-josh (https://github.com/ino-josh).
Many thanks!

- Changed the default MAIL FROM format to fit the RFC.
- mCredential being a member of SMTPClientBase is now freed by it.
- Base64 encoding: added CRLF every so often to prevent rejection.
- Attachments: added mime types for audio files.
- Fix massive memory leak in createAttachmentsText of the SMTPClientBase class.


## [1.1.6]

### Added

- Added support in the attachment class for Content-ID. It will be really
useful to uniquely identify and reference resources to embed in the message.
This change has been made by hesa2020 (https://github.com/hesa2020).
Many thanks!

### Enhancement

- Correction to the CMakeLists.txt, so when the repository is added as a git
submodule and linked in the parent cmake project, it will now compile.
This change has been made by hesa2020 (https://github.com/hesa2020).
Many thanks!

## [1.1.5]

### Added

- Added OpenSSL variables in CMakeLists to be able to specify include,
library path and library files.
- A set of new classes has been added to the jed_utils::cpp namespace
to provide a pure C++ way to consume the library. This is the new
standard from version 1.1.5. See the new class documentation in the wiki.

### Updated

- The ErrorResolver class now compiles on Windows.
- Changed the ErrorResolver field mErrorMessage from an std::string to an
char * to keep a Plain C Interface.
- Code formatting applied throughout the project using cpplint and following
Google's C++ style guide.
- Configured Linux Socket connect function to non-blocking mode to make
the SmtpClientBase timeout working as expected.
- Added WSACleanup error return code to the communication log.

### Bug fixes

- Changed the size of the communication log buffer from static (4096 bytes) to an
auto-growing dynamic buffer.

### Security fixes

- Replaced all insecure strcpy by functions that support length arguments like
strncpy.

## [1.1.4]

### Added

- Add the BUILD_TESTING flag in the CMake project so the unit tests are not
build by default and Google Test is no longer required.
- Add a new uninstall target in the CMake project.
- Add a new ErrorResolver class to get a string representation (error message)
of a return code obtained by the
  sendMail method from the different classes of SMTP clients.
- Two new methods has been added to the SMTPClientBase class : getErrorMessage
and getErrorMessage_r. Those two methods can be used to get a string
representation (error message) of a return code obtained by the sendMail
method from the different classes of SMTP clients.

### Updated

- The Google Test dependency branch has been switched from master to main.
- Code: The using namespace std; has been removed as it is considered bad practice.
- The Windows documentation has been updated to explain how to use
OPENSSL_ROOT_DIR variable.
- Added documentation in all headers files for public methods.

### Removed

- The exception classes AttachmentError and CommunicationError has been removed.

## [1.1.3]

### Updated

- Rename the class SSLSmtpClient to OpportunisticSecureSMTPClient but added a
typedef and kept the sslsmtpclient.h for backward compatibility.

### Added

- Add support for forced ssl connection (SMTP port 465) via the
ForcedSecureSMTPClient class
- Add the new base class SecureSMTPClientBase to centralize the common code of
the classes ForcedSecureSMTPClient and OpportunisticSecureSMTPClient.

## [1.1.2]

### Updated

- Refactor the code of the SmtpClient class to inherit the SmtpClientBase class.
- You must now call the method getCommunicationLog() instead of getServerReply()

## [1.1.1]

### Added

- Add support for the cc and bcc field in the sendMail method

## [1.1.0]

### Added

- The SSL/TLS version of the SMTP Client (sslsmtpclient.cpp)
- Authentication capabilities have been added to the new SSL/TLS client
- Error code headers have been created so the return codes are now more
descriptive (socketerrors.h and sslerrors.h)

### Bug fixes

- The MessageAddress class now support uppercase characters in the email address

## [1.0.0]

### Added

- The initial version development
