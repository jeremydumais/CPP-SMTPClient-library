# Changelog
All notable changes to this project will be documented in this file.

## [1.1.1]

### Added
- Add support for the cc and bcc field in the sendMail method

## [1.1.0]

### Added
- The SSL/TLS version of the SMTP Client (sslsmtpclient.cpp)
- Authentication capabilities have been added to the new SSL/TLS client
- Error code headers have been created so the return codes are now more descriptive (socketerrors.h and sslerrors.h)

### Bug fixes

- The MessageAddress class now support uppercase characters in the email address

## [1.0.0]

### Added
- The initial version development