#include "smtpclient.hpp"
#include <string>

using namespace jed_utils::cpp;

SmtpClient::SmtpClient(const std::string &pServerName, unsigned int pPort)
    : jed_utils::SmtpClient(pServerName.c_str(), pPort) {
}

std::string SmtpClient::getServerName() const {
    return jed_utils::SmtpClient::getServerName();
}

unsigned int SmtpClient::getServerPort() const {
    return jed_utils::SmtpClient::getServerPort();
}

bool SmtpClient::getBatchMode() const {
    return jed_utils::SmtpClient::getBatchMode();
}

unsigned int SmtpClient::getCommandTimeout() const {
    return jed_utils::SMTPClientBase::getCommandTimeout();
}

std::string SmtpClient::getCommunicationLog() const {
    return jed_utils::SmtpClient::getCommunicationLog();
}

const Credential *SmtpClient::getCredentials() const {
    return mCredential;
}

void SmtpClient::setServerName(const std::string &pServerName) {
    jed_utils::SmtpClient::setServerName(pServerName.c_str());
}

void SmtpClient::setServerPort(unsigned int pPort) {
    jed_utils::SmtpClient::setServerPort(pPort);
}

void SmtpClient::setBatchMode(bool pEnabled) {
    jed_utils::SmtpClient::setBatchMode(pEnabled);
}

void SmtpClient::setCommandTimeout(unsigned int pTimeOutInSeconds) {
    jed_utils::SMTPClientBase::setCommandTimeout(pTimeOutInSeconds);
}

void SmtpClient::setCredentials(const Credential &pCredential) {
    jed_utils::SMTPClientBase::setCredentials(jed_utils::Credential(pCredential.getUsername().c_str(),
                                                                    pCredential.getPassword().c_str()));
    delete mCredential;
    mCredential = new Credential(pCredential);
}

void SmtpClient::setKeepUsingBaseSendCommands(bool pValue) {
    jed_utils::SMTPClientBase::setKeepUsingBaseSendCommands(pValue);
}

std::string SmtpClient::getErrorMessage(int errorCode) {
    return jed_utils::SMTPClientBase::getErrorMessage(errorCode);
}

int SmtpClient::getErrorMessage_r(int errorCode,
                                  std::string &errorMessage) {
    const size_t MAXSIZE = 1024;
    char *errorMsg = new char[MAXSIZE];
    int result = jed_utils::SMTPClientBase::getErrorMessage_r(errorCode, errorMsg, MAXSIZE);
    errorMessage = errorMsg;
    return result;
}

int SmtpClient::extractReturnCode(const std::string &pOutput) {
    return jed_utils::SMTPClientBase::extractReturnCode(pOutput.c_str());
}

jed_utils::ServerAuthOptions *SmtpClient::extractAuthenticationOptions(const std::string &pEhloOutput) {
    return jed_utils::SMTPClientBase::extractAuthenticationOptions(pEhloOutput.c_str());
}

int SmtpClient::sendMail(const jed_utils::Message &pMsg) {
    return jed_utils::SmtpClient::sendMail(pMsg);
}
