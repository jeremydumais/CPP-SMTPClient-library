# Changelog
All notable changes to this project will be documented in this file

## [1.1.3]

### Updated
- Rename the class SSLSmtpClient to OpportunisticSecureSMTPClient but added a typedef and kept the sslsmtpclient.h for backward compatibility.

### Added
- Add support for forced ssl connection (SMTP port 465) via the ForcedSecureSMTPClient class
- Add the new base class SecureSMTPClientBase to centralize the common code of the classes ForcedSecureSMTPClient and OpportunisticSecureSMTPClient.

---
## [1.1.2]

### Updated
- Refactor the code of the SmtpClient class to inherit the SmtpClientBase class.
- You must now call the method getCommunicationLog() instead of getServerReply()
---
## [1.1.1]

### Added
- Add support for the cc and bcc field in the sendMail method
---
## [1.1.0]

### Added
- The SSL/TLS version of the SMTP Client (sslsmtpclient.cpp)
- Authentication capabilities have been added to the new SSL/TLS client
- Error code headers have been created so the return codes are now more descriptive (socketerrors.h and sslerrors.h)

### Bug fixes

- The MessageAddress class now support uppercase characters in the email address
---
## [1.0.0]

### Added
- The initial version development