#include "forcedsecuresmtpclient.hpp"
#include <string>

using namespace jed_utils::cpp;

ForcedSecureSMTPClient::ForcedSecureSMTPClient(const std::string &pServerName, unsigned int pPort)
    : jed_utils::ForcedSecureSMTPClient(pServerName.c_str(), pPort) {
}

std::string ForcedSecureSMTPClient::getServerName() const {
    return jed_utils::ForcedSecureSMTPClient::getServerName();
}

unsigned int ForcedSecureSMTPClient::getServerPort() const {
    return jed_utils::ForcedSecureSMTPClient::getServerPort();
}

bool ForcedSecureSMTPClient::getBatchMode() const {
    return jed_utils::ForcedSecureSMTPClient::getBatchMode();
}

unsigned int ForcedSecureSMTPClient::getCommandTimeout() const {
    return jed_utils::SMTPClientBase::getCommandTimeout();
}

std::string ForcedSecureSMTPClient::getCommunicationLog() const {
    return jed_utils::ForcedSecureSMTPClient::getCommunicationLog();
}

const Credential *ForcedSecureSMTPClient::getCredentials() const {
    return mCredential;
}

bool ForcedSecureSMTPClient::getAcceptSelfSignedCert() const {
    return jed_utils::SecureSMTPClientBase::getAcceptSelfSignedCert();
}

void ForcedSecureSMTPClient::setServerName(const std::string &pServerName) {
    jed_utils::ForcedSecureSMTPClient::setServerName(pServerName.c_str());
}

void ForcedSecureSMTPClient::setServerPort(unsigned int pPort) {
    jed_utils::ForcedSecureSMTPClient::setServerPort(pPort);
}

void ForcedSecureSMTPClient::setBatchMode(bool pEnabled) {
    jed_utils::ForcedSecureSMTPClient::setBatchMode(pEnabled);
}

void ForcedSecureSMTPClient::setCommandTimeout(unsigned int pTimeOutInSeconds) {
    jed_utils::SMTPClientBase::setCommandTimeout(pTimeOutInSeconds);
}

void ForcedSecureSMTPClient::setCredentials(const Credential &pCredential) {
    jed_utils::SMTPClientBase::setCredentials(jed_utils::Credential(pCredential.getUsername().c_str(),
                                                                    pCredential.getPassword().c_str(),
                                                                    pCredential.getRecommendedAuthOption()));
    delete mCredential;
    mCredential = new Credential(pCredential);
}

void ForcedSecureSMTPClient::setAcceptSelfSignedCert(bool pValue) {
    jed_utils::SecureSMTPClientBase::setAcceptSelfSignedCert(pValue);
}

void ForcedSecureSMTPClient::setKeepUsingBaseSendCommands(bool pValue) {
    jed_utils::SMTPClientBase::setKeepUsingBaseSendCommands(pValue);
}

std::string ForcedSecureSMTPClient::getErrorMessage(int errorCode) {
    return jed_utils::SMTPClientBase::getErrorMessage(errorCode);
}

int ForcedSecureSMTPClient::getErrorMessage_r(int errorCode,
                                  std::string &errorMessage) {
    const size_t MAXSIZE = 1024;
    char *errorMsg = new char[MAXSIZE];
    int result = jed_utils::SMTPClientBase::getErrorMessage_r(errorCode, errorMsg, MAXSIZE);
    errorMessage = errorMsg;
    return result;
}

int ForcedSecureSMTPClient::extractReturnCode(const std::string &pOutput) {
    return jed_utils::SMTPClientBase::extractReturnCode(pOutput.c_str());
}

jed_utils::ServerAuthOptions *ForcedSecureSMTPClient::extractAuthenticationOptions(const std::string &pEhloOutput) {
    return jed_utils::SMTPClientBase::extractAuthenticationOptions(pEhloOutput.c_str());
}

int ForcedSecureSMTPClient::sendMail(const jed_utils::Message &pMsg) {
    return jed_utils::ForcedSecureSMTPClient::sendMail(pMsg);
}
