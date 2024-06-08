#ifndef SMTPCLIENTBASE_H
#define SMTPCLIENTBASE_H

#include <string>
#include <vector>
#include "attachment.h"
#include "credential.h"
#include "message.h"
#include "messageaddress.h"
#include "serverauthoptions.h"

#ifdef _WIN32
    #ifdef SMTPCLIENT_EXPORTS
        #define SMTPCLIENTBASE_API __declspec(dllexport)
    #else
        #define SMTPCLIENTBASE_API __declspec(dllimport)
    #endif
#else
    #define SMTPCLIENTBASE_API
#endif

/** The max length of the communication log */
#define INITIAL_COMM_LOG_LENGTH 4096

/** The max length of the server response buffer */
#define SERVERRESPONSE_BUFFER_LENGTH 1024

namespace jed_utils {
/** @brief The SMTPClientBase represents the base class for all SMTP clients
 *  that will or will not use encryption for communication.
 */
class SMTPCLIENTBASE_API SMTPClientBase {
 public:
    /**
     *  @brief  Construct a new SMTPClientBase.
     *  @param pServerName The name of the server.
     *  Example: smtp.domainexample.com
     *  @param pPort The server port number.
     *  Example: 25, 465, 587
     */
    SMTPClientBase(const char *pServerName, unsigned int pPort);

    /** Destructor of the SMTPClientBase. */
    virtual ~SMTPClientBase();

    /** SMTPClientBase copy constructor. */
    SMTPClientBase(const SMTPClientBase& other);

    /** SMTPClientBase copy assignment operator. */
    SMTPClientBase& operator=(const SMTPClientBase& other);

    /** SMTPClientBase move constructor. */
    SMTPClientBase(SMTPClientBase&& other) noexcept;

    /** SMTPClientBase move assignment operator. */
    SMTPClientBase& operator=(SMTPClientBase&& other) noexcept;

    /** Return the server name. */
    const char *getServerName() const;

    /** Return the server port number. */
    unsigned int getServerPort() const;

    /** Return the batch mode enable flag. */
    bool getBatchMode() const;

    /** Return the command timeout in seconds. */
    unsigned int getCommandTimeout() const;

    /** Return the communication log produced by the sendMail method. */
    const char *getCommunicationLog() const;

    /** Return the credentials configured. */
    const Credential *getCredentials() const;

    /**
     *  @brief  Set the server name.
     *  @param pServerName A char array pointer of the server name.
     *  Example: smtp.domainexample.com
     */
    void setServerName(const char *pServerName);

    /**
     *  @brief  Set the server port number.
     *  @param pPort The port number.
     *  Example: 25, 465, 587
     */
    void setServerPort(unsigned int pPort);

    /**
     *  @brief  Set the batch mode flag.
     *  @param pEnabled Indicate if the batch mode is enabled.
     *  Default: false
     */
    void setBatchMode(bool pEnabled);

    /**
     *  @brief  Set the command timeout in seconds.
     *  @param pTimeOutInSeconds The timeout in seconds.
     *  Default: 3 seconds
     */
    void setCommandTimeout(unsigned int pTimeOutInSeconds);

    /**
     *  @brief  Set the credentials.
     *  @param pCredential The credential containing the username and the password.
     */
    void setCredentials(const Credential &pCredential);

    /**
     *  @brief  Indicate if the class will keep using base send command even
     *  if a child class as overriden the sendCommand and sendCommandWithFeedback.
     *
     *  This is used for example if you are using a secure client class but
     *  the STARTTLS feature is not available. The communication will then
     *  remain unsecured.
     *  @param pValue True to enable this behavior, false for the default
     */
    void setKeepUsingBaseSendCommands(bool pValue);

    /**
     *  @brief  Retreive the error message string that correspond to
     *  the error code provided.
     *  @return A pointer to an allocated char array that pointed to the
     *  error message. The user is responsible to delete this pointer after
     *  usage.
     */
    static char *getErrorMessage(int errorCode);

    /**
     *  @brief  This is the reentrant version of the getErrorMessage method
     *  @param  errorCode  The error code return by the SMTP client.
     *  @param  errorMessagePtr  A pointer to an allocated char array
     *  @param  maxLength  The size of the allocated char array.
     *  @return Return 0 for success, -1 if an error occurred and a positive
     *  number representing the number of characters copied to errorMessagePtr
     *  if the message was longer than that allocated char array.
     *
     *  Retreive the error message string that correspond to the error code
     *  provided.
     */
    static int getErrorMessage_r(int errorCode,
            char *errorMessagePtr,
            const size_t maxLength);

    int sendMail(const Message &pMsg);

 protected:
    bool mIsConnected;
    virtual void cleanup() = 0;
    int getSocketFileDescriptor() const;
    void clearSocketFileDescriptor();
    const char *getLastServerResponse() const;
    void setLastSocketErrNo(int lastError);
    void setAuthenticationOptions(ServerAuthOptions *authOptions);
    // Methods used to establish the connection with server
    int initializeSession();
    #ifdef _WIN32
    int initializeSessionWinSock();
    int setSocketToNonBlockingWinSock();
    int setSocketToBlockingWinSock();
    bool isWSAStarted();
    void setWSAStopped();
    void addWSAMessageToCommunicationLog(const int errorCode);
    void doWSACleanup();
    #else
    int initializeSessionPOSIX();
    int setSocketToNonBlockingPOSIX();
    int setSocketToBlockingPOSIX();
    #endif
    int setSocketToNonBlocking();
    int setSocketToBlocking();
    int sendServerIdentification();
    virtual int establishConnectionWithServer() = 0;
    virtual int checkServerGreetings();
    // Methods to send commands to the server
    void setLastServerResponse(const char *pResponse);
    int sendRawCommand(const char *pCommand, int pErrorCode);
    int sendRawCommand(const char *pCommand, int pErrorCode, int pTimeoutCode);
    int getRawCommandReply();
    virtual int sendCommand(const char *pCommand, int pErrorCode) = 0;
    virtual int sendCommandWithFeedback(const char *pCommand, int pErrorCode, int pTimeoutCode) = 0;
    virtual int getServerReply() = 0;
    int sendQuitCommand();
    void crossPlatformSleep(unsigned int seconds);
    // Methods used for authentication
    int authenticateClient();
    int authenticateWithMethodPlain();
    int authenticateWithMethodLogin();
    int authenticatedWithMethodXOauth2();
    // Methods to send an email
    int setMailRecipients(const Message &pMsg);
    int addMailRecipients(jed_utils::MessageAddress **list, size_t count, const int RECIPIENT_OK);
    int setMailHeaders(const Message &pMsg);
    int addMailHeader(const char *field, const char *value, int pErrorCode);
    int setMailBody(const Message &pMsg);

    void addCommunicationLogItem(const char *pItem, const char *pPrefix = "c");
    static std::string createAttachmentsText(const std::vector<Attachment*> &pAttachments);
    static int extractReturnCode(const char *pOutput);
    static ServerAuthOptions *extractAuthenticationOptions(const char *pEhloOutput);
    static std::string generateHeaderAddressValues(const std::vector<jed_utils::MessageAddress *> &pList);

 private:
    char *mServerName;
    unsigned int mPort;
    bool mBatchMode;
    char *mCommunicationLog;
    size_t mCommunicationLogSize = 0;
    char *mLastServerResponse;
    unsigned int mCommandTimeOut;
    int mLastSocketErrNo;
    ServerAuthOptions *mAuthOptions;
    Credential *mCredential;
    int mSock = 0;
    #ifdef _WIN32
    bool mWSAStarted = false;
    #endif

    // This field indicate the class will keep using base send command even if a child class
    // as overriden the sendCommand and sendCommandWithFeedback.
    // This is used for example if you are using a secure client class but the STARTTLS
    // feature is not available. The communication will then remain unsecured.
    bool mKeepUsingBaseSendCommands;

    int (SMTPClientBase::*sendCommandPtr)(const char *pCommand, int pErrorCode);
    int (SMTPClientBase::*sendCommandWithFeedbackPtr)(const char *pCommand, int pErrorCode, int pTimeoutCode);
};
}  // namespace jed_utils

#endif
