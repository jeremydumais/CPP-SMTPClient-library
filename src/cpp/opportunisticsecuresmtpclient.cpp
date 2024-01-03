#include "opportunisticsecuresmtpclient.hpp"
#include <string>

using namespace jed_utils::cpp;

OpportunisticSecureSMTPClient::OpportunisticSecureSMTPClient(const std::string &pServerName, unsigned int pPort)
    : jed_utils::OpportunisticSecureSMTPClient(pServerName.c_str(), pPort) {
}

std::string OpportunisticSecureSMTPClient::getServerName() const {
    return jed_utils::OpportunisticSecureSMTPClient::getServerName();
}

unsigned int OpportunisticSecureSMTPClient::getServerPort() const {
    return jed_utils::OpportunisticSecureSMTPClient::getServerPort();
}

bool OpportunisticSecureSMTPClient::getBatchMode() const {
    return jed_utils::OpportunisticSecureSMTPClient::getBatchMode();
}

unsigned int OpportunisticSecureSMTPClient::getCommandTimeout() const {
    return jed_utils::SMTPClientBase::getCommandTimeout();
}

std::string OpportunisticSecureSMTPClient::getCommunicationLog() const {
    return jed_utils::OpportunisticSecureSMTPClient::getCommunicationLog();
}

const Credential *OpportunisticSecureSMTPClient::getCredentials() const {
    return mCredential;
}

bool OpportunisticSecureSMTPClient::getAcceptSelfSignedCert() const {
    return jed_utils::SecureSMTPClientBase::getAcceptSelfSignedCert();
}

void OpportunisticSecureSMTPClient::setServerName(const std::string &pServerName) {
    jed_utils::OpportunisticSecureSMTPClient::setServerName(pServerName.c_str());
}

void OpportunisticSecureSMTPClient::setServerPort(unsigned int pPort) {
    jed_utils::OpportunisticSecureSMTPClient::setServerPort(pPort);
}

void OpportunisticSecureSMTPClient::setBatchMode(bool pEnabled) {
    jed_utils::OpportunisticSecureSMTPClient::setBatchMode(pEnabled);
}

void OpportunisticSecureSMTPClient::setCommandTimeout(unsigned int pTimeOutInSeconds) {
    jed_utils::SMTPClientBase::setCommandTimeout(pTimeOutInSeconds);
}

void OpportunisticSecureSMTPClient::setCredentials(const Credential &pCredential) {
    jed_utils::SMTPClientBase::setCredentials(jed_utils::Credential(pCredential.getUsername().c_str(),
                                                                    pCredential.getPassword().c_str(),
                                                                    pCredential.getRecommendedAuthOption()));
    delete mCredential;
    mCredential = new Credential(pCredential);
}

void OpportunisticSecureSMTPClient::setAcceptSelfSignedCert(bool pValue) {
    jed_utils::SecureSMTPClientBase::setAcceptSelfSignedCert(pValue);
}

void OpportunisticSecureSMTPClient::setKeepUsingBaseSendCommands(bool pValue) {
    jed_utils::SMTPClientBase::setKeepUsingBaseSendCommands(pValue);
}

std::string OpportunisticSecureSMTPClient::getErrorMessage(int errorCode) {
    return jed_utils::SMTPClientBase::getErrorMessage(errorCode);
}

int OpportunisticSecureSMTPClient::getErrorMessage_r(int errorCode,
                                  std::string &errorMessage) {
    const size_t MAXSIZE = 1024;
    char *errorMsg = new char[MAXSIZE];
    int result = jed_utils::SMTPClientBase::getErrorMessage_r(errorCode, errorMsg, MAXSIZE);
    errorMessage = errorMsg;
    return result;
}

int OpportunisticSecureSMTPClient::extractReturnCode(const std::string &pOutput) {
    return jed_utils::SMTPClientBase::extractReturnCode(pOutput.c_str());
}

jed_utils::ServerAuthOptions *OpportunisticSecureSMTPClient::extractAuthenticationOptions(const std::string &pEhloOutput) {
    return jed_utils::SMTPClientBase::extractAuthenticationOptions(pEhloOutput.c_str());
}

int OpportunisticSecureSMTPClient::sendMail(const jed_utils::Message &pMsg) {
    return jed_utils::OpportunisticSecureSMTPClient::sendMail(pMsg);
}
