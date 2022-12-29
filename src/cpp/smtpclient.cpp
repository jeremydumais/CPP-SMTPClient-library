#include "smtpclient.hpp"
#include <string>
#include <utility>

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

unsigned int SmtpClient::getCommandTimeout() const {
    return jed_utils::SMTPClientBase::getCommandTimeout();
}

std::string SmtpClient::getCommunicationLog() const {
    return jed_utils::SmtpClient::getCommunicationLog();
}

const jed_utils::Credential *SmtpClient::getCredentials() const {
    return jed_utils::SMTPClientBase::getCredentials();
}

void SmtpClient::setServerName(const std::string &pServerName) {
    jed_utils::SmtpClient::setServerName(pServerName.c_str());
}

void SmtpClient::setServerPort(unsigned int pPort) {
    jed_utils::SmtpClient::setServerPort(pPort);
}

void SmtpClient::setCommandTimeout(unsigned int pTimeOutInSeconds) {
    jed_utils::SMTPClientBase::setCommandTimeout(pTimeOutInSeconds);
}

void SmtpClient::setCredentials(const jed_utils::Credential &pCredential) {
    jed_utils::SMTPClientBase::setCredentials(pCredential);
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

//TODO To implement
//int sendMail(const Message &pMsg) {

//}
