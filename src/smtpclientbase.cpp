#include "base64.h"
#include "message.h"
#include "messageaddress.h"
#include "serverauthoptions.h"
#include "smtpclientbase.h"
#include "smtpclienterrors.h"
#include "socketerrors.h"
#include "stringutils.h"
#include <algorithm>
#include <stdexcept>
#include <string>
#include <sstream>
#ifdef _WIN32
	#include <WinSock2.h>
    #include <ws2tcpip.h>
    #include <BaseTsd.h>
    typedef SSIZE_T ssize_t;
    #include <windows.h>
    constexpr auto sleep = Sleep;
#else
    #include <fcntl.h>
    #include <netdb.h>
    #include <unistd.h>
    #include <netinet/in.h>
    #include <sys/socket.h>
    #include <sys/types.h>  
#endif


using namespace jed_utils;
using namespace std;

SmtpClientBase::SmtpClientBase(const char *pServerName, unsigned int pPort) 
    : mServerName(nullptr),
      mPort(pPort),
      mCommunicationLog(nullptr),
      mLastServerResponse(nullptr),
      mCommandTimeOut(3),
      mLastSocketErrNo(0),
      mAuthOptions(nullptr),
      mCredential(nullptr),
      mSock(0)
{
    string servername_str { pServerName == nullptr ? "" : pServerName };
    if (pServerName == nullptr || strcmp(pServerName, "") == 0  || StringUtils::trim(servername_str).empty()) {
        throw invalid_argument("Server name cannot be null or empty");
    }
    size_t server_name_len = strlen(pServerName);
	mServerName = new char[server_name_len + 1];
	strncpy(mServerName, pServerName, server_name_len);
    mServerName[server_name_len] = '\0';
}

SmtpClientBase::~SmtpClientBase() 
{
    delete[] mServerName;
    mServerName = nullptr;
    delete[] mCommunicationLog;
    mCommunicationLog = nullptr;
    delete[] mLastServerResponse;
    mLastServerResponse = nullptr;
    delete mAuthOptions;
    mAuthOptions = nullptr;
    mCredential = nullptr;
}

//Copy constructor
SmtpClientBase::SmtpClientBase(const SmtpClientBase& other)
    :  mServerName(new char[strlen(other.mServerName) + 1]),
       mPort(other.mPort),
       mCommunicationLog(other.mCommunicationLog != nullptr ? new char[strlen(other.mCommunicationLog) + 1]: nullptr),
       mLastServerResponse(other.mLastServerResponse != nullptr ? new char[strlen(other.mLastServerResponse) + 1]: nullptr),
       mCommandTimeOut(other.mCommandTimeOut),
       mLastSocketErrNo(other.mLastSocketErrNo),
       mAuthOptions(other.mAuthOptions != nullptr ? new ServerAuthOptions(*other.mAuthOptions) : nullptr),
       mCredential(other.mCredential != nullptr ? new Credential(*other.mCredential) : nullptr),
       mSock(0)
{
    strncpy(mServerName, other.mServerName, strlen(other.mServerName) + 1);
	mServerName[strlen(other.mServerName)] = '\0';
    
    if (mCommunicationLog != nullptr) {
	    strncpy(mCommunicationLog, other.mCommunicationLog, strlen(other.mCommunicationLog) + 1);
	    mCommunicationLog[strlen(other.mCommunicationLog)] = '\0';
    }

    if (mLastServerResponse != nullptr) {
	    strncpy(mLastServerResponse, other.mLastServerResponse, strlen(other.mLastServerResponse) + 1);
	    mLastServerResponse[strlen(other.mLastServerResponse)] = '\0';
    }
}

//Assignment operator
SmtpClientBase& SmtpClientBase::operator=(const SmtpClientBase& other)
{
    if (this != &other) {
        //mServerName
        delete[] mServerName;
		mServerName = new char[strlen(other.mServerName) + 1];
		strncpy(mServerName, other.mServerName, strlen(other.mServerName) + 1);
		mServerName[strlen(other.mServerName)] = '\0';
        //mPort
        mPort = other.mPort;
        //mCommunicationLog
        mCommunicationLog = other.mCommunicationLog != nullptr ? new char[strlen(other.mCommunicationLog) + 1]: nullptr;
        if (mCommunicationLog != nullptr) {
            strncpy(mCommunicationLog, other.mCommunicationLog, strlen(other.mCommunicationLog) + 1);
            mCommunicationLog[strlen(other.mCommunicationLog)] = '\0';
        }
        //mLastServerResponse
        mLastServerResponse = other.mLastServerResponse != nullptr ? new char[strlen(other.mLastServerResponse) + 1]: nullptr;
        if (mLastServerResponse != nullptr) {
            strncpy(mLastServerResponse, other.mLastServerResponse, strlen(other.mLastServerResponse) + 1);
            mLastServerResponse[strlen(other.mLastServerResponse)] = '\0';
        }
        mCommandTimeOut = other.mCommandTimeOut;
        mLastSocketErrNo = other.mLastSocketErrNo;

        delete mAuthOptions;
        mAuthOptions = other.mAuthOptions != nullptr ? new ServerAuthOptions(*other.mAuthOptions) : nullptr;
        //mCredential
        mCredential = other.mCredential != nullptr ? new Credential(*other.mCredential) : nullptr;
        mSock = 0;
    }
    return *this;
}

//Move constructor
SmtpClientBase::SmtpClientBase(SmtpClientBase&& other) noexcept
    : mServerName(other.mServerName),
      mPort(other.mPort),
      mCommunicationLog(other.mCommunicationLog),
      mLastServerResponse(other.mLastServerResponse),
      mCommandTimeOut(other.mCommandTimeOut),
      mLastSocketErrNo(other.mLastSocketErrNo),
      mAuthOptions(other.mAuthOptions),
      mCredential(other.mCredential),
      mSock(other.mSock)
{
    other.mServerName = nullptr;
    other.mPort = 0;
    other.mCommunicationLog = nullptr;
    other.mLastServerResponse = nullptr;
    other.mCommandTimeOut = 0;
    other.mLastSocketErrNo = 0;
    other.mAuthOptions = nullptr;
    other.mCredential = nullptr;
    other.mSock = 0;
}

//Move assignement operator
SmtpClientBase& SmtpClientBase::operator=(SmtpClientBase&& other) noexcept
{
    if (this != &other) {
        delete[] mServerName;
        delete[] mCommunicationLog;
        delete[] mLastServerResponse;
        delete mAuthOptions;
        delete mCredential;
        // Copy the data pointer and its length from the source object.
        mServerName = other.mServerName;
        mPort = other.mPort;
        mCommunicationLog = other.mCommunicationLog;
        mLastServerResponse = other.mLastServerResponse;
        mCommandTimeOut = other.mCommandTimeOut;
        mLastSocketErrNo = other.mLastSocketErrNo;
        mAuthOptions = other.mAuthOptions;
        mCredential = other.mCredential;
        mSock = other.mSock;
        // Release the data pointer from the source object so that
		// the destructor does not free the memory multiple times.
		other.mServerName = nullptr;
		other.mPort = 0;
        other.mCommunicationLog = nullptr;
        other.mLastServerResponse = nullptr;
        other.mCommandTimeOut = 0;
        other.mLastSocketErrNo = 0;
        other.mAuthOptions = nullptr;
        other.mCredential = nullptr;
        other.mSock = 0;
    }
	return *this;
}

const char *SmtpClientBase::getServerName() const
{
    return mServerName;
}

unsigned int SmtpClientBase::getServerPort() const
{
    return mPort;
}

unsigned int SmtpClientBase::getCommandTimeout() const
{
    return mCommandTimeOut;
}

const char *SmtpClientBase::getCommunicationLog() const
{
    return mCommunicationLog == nullptr ? "" : mCommunicationLog;
}

const Credential *SmtpClientBase::getCredentials() const
{
    return mCredential;
}

void SmtpClientBase::setServerPort(unsigned int pPort)
{
    mPort = pPort;
}

void SmtpClientBase::setServerName(const char *pServerName)
{
    string servername_str { pServerName == nullptr ? "" : pServerName };
    if (pServerName == nullptr || strcmp(pServerName, "") == 0  || StringUtils::trim(servername_str).empty()) {
        throw invalid_argument("Server name cannot be null or empty");
    }
    delete []mServerName;
    size_t server_name_len = strlen(pServerName);
	mServerName = new char[server_name_len + 1];
	strncpy(mServerName, pServerName, server_name_len);
    mServerName[server_name_len] = '\0';
}

void SmtpClientBase::setCommandTimeout(unsigned int pTimeOutInSeconds)
{
    mCommandTimeOut = pTimeOutInSeconds;
}

void SmtpClientBase::setCredentials(const Credential &pCredential)
{
    delete mCredential;
    mCredential = new Credential(pCredential);
}

int SmtpClientBase::sendMail(const Message &pMsg)
{
    int client_connect_ret_code = establishConnectionWithServer();
    if (client_connect_ret_code != 0) {
        return client_connect_ret_code;
    }

    int set_mail_recipients_ret_code = setMailRecipients(pMsg);
    if (set_mail_recipients_ret_code != 0) {
        return set_mail_recipients_ret_code;
    }

    int set_mail_headers_ret_code = setMailHeaders(pMsg);
    if (set_mail_headers_ret_code != 0) {
        return set_mail_headers_ret_code;
    }

    int set_mail_body_ret_code = setMailBody(pMsg);
    if (set_mail_body_ret_code != 0) {
        return set_mail_body_ret_code;
    }

    cleanup(); 
    return 0;
}


int SmtpClientBase::initializeSession() 
{
    delete[] mCommunicationLog;
    mCommunicationLog = new char[4096];
    mCommunicationLog[0] = '\0';

    #ifdef _WIN32
    //Windows Sockets version
        WSADATA wsaData;
        WORD wVersionRequested = MAKEWORD(2, 2);
        int wsa_retVal = WSAStartup(wVersionRequested, &wsaData);
        if (wsa_retVal != 0) {
            mLastSocketErrNo = wsa_retVal;
            return SOCKET_INIT_SESSION_WINSOCKET_STARTUP_ERROR;
        }
        struct addrinfo *result = nullptr;
        struct addrinfo hints; 
        memset(&hints, 0, sizeof hints);
        hints.ai_family = AF_UNSPEC;  // use IPv4 or IPv6, whichever
        hints.ai_socktype = SOCK_STREAM;

        wsa_retVal = getaddrinfo(getServerName(), to_string(getServerPort()).c_str(), &hints, &result);
        if (wsa_retVal != 0) 
        {
            WSACleanup();
            mLastSocketErrNo = wsa_retVal;
            return SOCKET_INIT_SESSION_WINSOCKET_GETADDRINFO_ERROR;
        }

        mSock = static_cast<unsigned int>(socket(result->ai_family, result->ai_socktype, result->ai_protocol));
        if (mSock == INVALID_SOCKET) {
            WSACleanup();
            mLastSocketErrNo = WSAGetLastError();
            return SOCKET_INIT_SESSION_CREATION_ERROR;
        }
        wsa_retVal = connect(mSock, result->ai_addr, static_cast<int>(result->ai_addrlen));
        if (wsa_retVal == SOCKET_ERROR) 
        {
            WSACleanup();
            mLastSocketErrNo = WSAGetLastError();
            return SOCKET_INIT_SESSION_CONNECT_ERROR;
        }
    #else
    //POSIX socket version
        mSock = socket(AF_INET, SOCK_STREAM, 0);
        if (mSock < 0) {
            mLastSocketErrNo = errno;
            return SOCKET_INIT_SESSION_CREATION_ERROR;
        }
        struct hostent *host = gethostbyname(getServerName());
        struct sockaddr_in saddr_in {};
        saddr_in.sin_family = AF_INET;
        saddr_in.sin_port = htons(static_cast<u_short>(getServerPort()));
        saddr_in.sin_addr.s_addr = 0;
        memcpy(reinterpret_cast<char*>(&(saddr_in.sin_addr)), host->h_addr, host->h_length);
        stringstream ss;
        ss << "Trying to connect to " << getServerName() << " on port " << getServerPort();
        addCommunicationLogItem(ss.str().c_str());
        if (connect(mSock, reinterpret_cast<struct sockaddr*>(&saddr_in), sizeof(saddr_in)) == -1) {
            mLastSocketErrNo = errno;
            return SOCKET_INIT_SESSION_CONNECT_ERROR;
        } 
    #endif

    char outbuf[1024];
    unsigned int waitTime = 0;
    ssize_t bytes_received = 0;
    while ((bytes_received = recv(mSock, outbuf, 1024, 0)) < 0 && waitTime < mCommandTimeOut)
    {
        sleep(1);
        waitTime += 1;
    }
    if (waitTime < mCommandTimeOut) {
        outbuf[bytes_received-1] = '\0';
        addCommunicationLogItem(outbuf, "s");
        int status_code = extractReturnCode(outbuf);
        if (status_code == 220) {
            addCommunicationLogItem("Connected!");
        }
        return status_code;
    }
    return SOCKET_INIT_SESSION_CONNECT_TIMEOUT;
}

int SmtpClientBase::sendServerIdentification() 
{
    string ehlo { "ehlo localhost\r\n" };
    addCommunicationLogItem(ehlo.c_str());
    return sendRawCommand(ehlo.c_str(), 
        SOCKET_INIT_CLIENT_SEND_EHLO_ERROR, 
        SOCKET_INIT_CLIENT_SEND_EHLO_TIMEOUT);
}

int SmtpClientBase::sendRawCommand(const char *pCommand, int pErrorCode, int pTimeoutCode)
{
    unsigned int waitTime {0};
    ssize_t bytes_received {0};
    char outbuf[1024];
    if (send(mSock, pCommand, strlen(pCommand), 0) == -1) {
        mLastSocketErrNo = errno;
        return pErrorCode;
    }

    while ((bytes_received = recv(mSock, outbuf, 1024, 0)) < 0 && waitTime < mCommandTimeOut) {
        sleep(1);
        waitTime += 1;
    }
    if (waitTime < mCommandTimeOut) {
        outbuf[bytes_received-1] = '\0';
        setLastServerResponse(outbuf);
        addCommunicationLogItem(outbuf, "s");
        return extractReturnCode(outbuf);
    }
    
    return pTimeoutCode;
}

void SmtpClientBase::setLastServerResponse(const char *pResponse)
{
    delete[] mLastServerResponse;
    size_t response_len = strlen(pResponse);
	mLastServerResponse = new char[response_len + 1];
	strncpy(mLastServerResponse, pResponse, response_len);
    mLastServerResponse[response_len] = '\0';
}        


int SmtpClientBase::authenticateClient()
{
    if (mCredential != nullptr) {
        if (mAuthOptions->Plain == true) {
            return authenticateWithMethodPlain();
        }
        else if (mAuthOptions->Login == true) {
            return authenticateWithMethodLogin();
        }
        else {
            return CLIENT_AUTHENTICATION_METHOD_NOTSUPPORTED;
        }
    }
    else {
        return CLIENT_AUTHENTICATE_NONEED;
    }
}

int SmtpClientBase::authenticateWithMethodPlain() {
    addCommunicationLogItem("AUTH PLAIN ***************\r\n");
    stringstream ss_credentials;
    //Format : \0username\0password
    ss_credentials << '\0' << mCredential->getUsername() << '\0' << mCredential->getPassword();
    string str_credentials = ss_credentials.str();
    stringstream ss;
    ss << "AUTH PLAIN " 
    << Base64::Encode(reinterpret_cast<const unsigned char*>(str_credentials.c_str()),
            strlen(mCredential->getUsername()) + strlen(mCredential->getPassword()) + 2) // + 2 for the two null characters 
    << "\r\n";
    return sendCommandWithFeedback(ss.str().c_str(), CLIENT_AUTHENTICATE_ERROR, CLIENT_AUTHENTICATE_TIMEOUT);
}

int SmtpClientBase::authenticateWithMethodLogin()
{
    addCommunicationLogItem("AUTH LOGIN ***************\r\n");
    int login_return_code = sendCommandWithFeedback("AUTH LOGIN\r\n",  
        CLIENT_AUTHENTICATE_ERROR, 
        CLIENT_AUTHENTICATE_TIMEOUT);
    if (login_return_code != 334) {
        return CLIENT_AUTHENTICATE_ERROR;
    }
    
    string encoded_username { Base64::Encode(reinterpret_cast<const unsigned char*>(mCredential->getUsername()), 
        strlen(mCredential->getUsername())) };
    stringstream ss_username;
    ss_username << encoded_username << "\r\n";
    int username_return_code = sendCommandWithFeedback(ss_username.str().c_str(), 
        CLIENT_AUTHENTICATE_ERROR, 
        CLIENT_AUTHENTICATE_TIMEOUT);
    if (username_return_code != 334) {
        return CLIENT_AUTHENTICATE_ERROR;
    }
    string encoded_password { Base64::Encode(reinterpret_cast<const unsigned char*>(mCredential->getPassword()), 
        strlen(mCredential->getPassword())) };
    stringstream ss_password;
    ss_password << encoded_password << "\r\n";
    return sendCommandWithFeedback(ss_password.str().c_str(), CLIENT_AUTHENTICATE_ERROR, CLIENT_AUTHENTICATE_TIMEOUT);
}

int SmtpClientBase::setMailRecipients(const Message &pMsg) 
{
    const int INVALID_ADDRESS { 501 };
    const int SENDER_OK { 250 };
    const int RECIPIENT_OK { 250 };
    vector<string> mailFormats;
    stringstream ss_mail_from;
    //Method 1, 2 and 3
    mailFormats.push_back("MAIL FROM: <"s + pMsg.getFrom().getDisplayName() + " " + pMsg.getFrom().getEmailAddress() + ">\r\n"s);
    mailFormats.push_back("MAIL FROM: "s + pMsg.getFrom().getEmailAddress() + "\r\n"s);
    mailFormats.push_back("MAIL FROM: <"s + pMsg.getFrom().getEmailAddress() + ">\r\n"s);

    int mail_from_ret_code { 0 };
    for(const auto &format : mailFormats) {
        addCommunicationLogItem(format.c_str());
        mail_from_ret_code = sendCommandWithFeedback(format.c_str(), CLIENT_SENDMAIL_MAILFROM_ERROR, CLIENT_SENDMAIL_MAILFROM_TIMEOUT);
        if (mail_from_ret_code == SENDER_OK) {
            break;
        }
        else if (mail_from_ret_code != INVALID_ADDRESS) {
            return mail_from_ret_code;
        }
    }
    //if no compatible format were found
    if (mail_from_ret_code != SENDER_OK) {
        return mail_from_ret_code;
    }

    //Send command for the recipients
    vector<pair<MessageAddress **, size_t>> recipients {
        pair<MessageAddress **, size_t>(pMsg.getTo(), pMsg.getToCount()),
        pair<MessageAddress **, size_t>(pMsg.getCc(), pMsg.getCcCount()),
        pair<MessageAddress **, size_t>(pMsg.getBcc(), pMsg.getBccCount())
    };
    for(const auto &item : recipients) {
        if (item.first != nullptr) {
            int rcpt_to_ret_code = addMailRecipients(item.first, item.second, RECIPIENT_OK);
            if (rcpt_to_ret_code != RECIPIENT_OK) {
                return rcpt_to_ret_code;
            }
        }
    }
    return 0;
}

int SmtpClientBase::addMailRecipients(jed_utils::MessageAddress **list, size_t count, const int RECIPIENT_OK) 
{
    int rcpt_to_ret_code = RECIPIENT_OK;
    for_each(list, list + count, [this, &rcpt_to_ret_code, &RECIPIENT_OK](MessageAddress *address) {
        stringstream ss_rcpt_to;
        ss_rcpt_to << "RCPT TO: <"s << address->getEmailAddress() << ">\r\n"s;
        addCommunicationLogItem(ss_rcpt_to.str().c_str());
        int ret_code = sendCommandWithFeedback(ss_rcpt_to.str().c_str(), CLIENT_SENDMAIL_RCPTTO_ERROR, CLIENT_SENDMAIL_RCPTTO_TIMEOUT);
        if (ret_code != RECIPIENT_OK) {
            rcpt_to_ret_code = ret_code;
        }
    });
    return rcpt_to_ret_code;
}

int SmtpClientBase::setMailHeaders(const Message &pMsg)
{
    // Data section
    string data_cmd = "DATA\r\n";
    addCommunicationLogItem(data_cmd.c_str());
    int data_ret_code = sendCommandWithFeedback(data_cmd.c_str(), CLIENT_SENDMAIL_DATA_ERROR, CLIENT_SENDMAIL_DATA_TIMEOUT);
    if (data_ret_code != 354) {
        return data_ret_code;
    }

    // Mail headers
    // From
    int header_from_ret_code = addMailHeader("From", pMsg.getFrom().getEmailAddress(), CLIENT_SENDMAIL_HEADERFROM_ERROR);
    if (header_from_ret_code != 0) {
        return header_from_ret_code;
    }

    // To and Cc. 
    //Note : Bcc are not included in the header
    vector<tuple<MessageAddress **, size_t, const char *>> recipients {
        tuple<MessageAddress **, size_t, const char *>(pMsg.getTo(), pMsg.getToCount(), "To"),
        tuple<MessageAddress **, size_t, const char *>(pMsg.getCc(), pMsg.getCcCount(), "Cc")
    };
    for(const auto &item : recipients) {
        MessageAddress **list = get<0>(item);
        size_t count = get<1>(item);
        const char *field = get<2>(item);
        if (list != nullptr) {
            for_each(list, list + count, [this, &field](MessageAddress *address) {
                return addMailHeader(field, address->getEmailAddress(), CLIENT_SENDMAIL_HEADERTOANDCC_ERROR);
            });
        }
    }

    // Subject
    stringstream ss_header_subject;
    ss_header_subject << "Subject: " << pMsg.getSubject() << "\r\n";
    addCommunicationLogItem(ss_header_subject.str().c_str());
    int header_subject_ret_code = sendCommand(ss_header_subject.str().c_str(), CLIENT_SENDMAIL_HEADERSUBJECT_ERROR);
    if (header_subject_ret_code != 0) {
        return header_subject_ret_code;
    }

    //Content-Type
    string content_type { "Content-Type: multipart/mixed; boundary=sep\r\n\r\n" };
    addCommunicationLogItem(content_type.c_str());
    int header_content_type_ret_code = sendCommand(content_type.c_str(), CLIENT_SENDMAIL_HEADERCONTENTTYPE_ERROR);
    if (header_content_type_ret_code != 0) {
        return header_content_type_ret_code;
    }

    return 0;
}

int SmtpClientBase::addMailHeader(const char *field, const char *value, int pErrorCode)
{
    stringstream ss_header_item;
    ss_header_item << field << ": " << value << "\r\n";
    addCommunicationLogItem(ss_header_item.str().c_str());
    return sendCommand(ss_header_item.str().c_str(), pErrorCode);
}

int SmtpClientBase::setMailBody(const Message &pMsg)
{
    // Body part
    ostringstream body_ss;
    body_ss << "--sep\r\nContent-Type: " << pMsg.getMimeType() << "; charset=UTF-8\r\n\r\n" << pMsg.getBody() << "\r\n";
    string body_real = body_ss.str();
    addCommunicationLogItem(body_real.c_str());    

    //If there's attachments, prepare the attachments text content
    Attachment** arr_attachment = pMsg.getAttachments();

    vector<Attachment*> vect_attachment(arr_attachment, arr_attachment + pMsg.getAttachmentsCount());
    if (pMsg.getAttachmentsCount() > 0) {
        string attachments_text = createAttachmentsText(vect_attachment);
        body_real += attachments_text;
    }

    if (body_real.length() > 512) {
        //Split into chunk
        for (size_t index_start = 0; index_start < body_real.length(); index_start += 512) {
            size_t length = 512;
            if (index_start + 512 > body_real.length() - 1) {
                length = body_real.length() - index_start;
            }
            int body_part_ret_code = sendCommand(body_real.substr(index_start, length).c_str(), CLIENT_SENDMAIL_BODYPART_ERROR);
            if (body_part_ret_code != 0) {
                return body_part_ret_code;
            }
        }
    }
    else {
        int body_ret_code = sendCommand(body_real.c_str(), CLIENT_SENDMAIL_BODY_ERROR);
        if (body_ret_code != 0) {
            return body_ret_code;
        }
    }

    //End of data
    string end_data_command { "\r\n.\r\n" };
    addCommunicationLogItem(end_data_command.c_str());    
    int end_data_ret_code = sendCommandWithFeedback(end_data_command.c_str(), CLIENT_SENDMAIL_END_DATA_ERROR, CLIENT_SENDMAIL_END_DATA_TIMEOUT);
    if (end_data_ret_code != 250) {
        return end_data_ret_code;
    }

    string quit_command { "QUIT\r\n" };
    addCommunicationLogItem(quit_command.c_str());    
    int quit_ret_code = sendCommand(quit_command.c_str(), CLIENT_SENDMAIL_QUIT_ERROR);
    if (quit_ret_code != 0) {
        return quit_ret_code;
    }
    return 0;
}

void SmtpClientBase::addCommunicationLogItem(const char *pItem, const char *pPrefix)
{
    string item { pItem };
    if (strcmp(pPrefix, "c") == 0) {
        /* Replace the \ by \\ */
        string from { "\r\n" };
        string to { "\\r\\n" };
        size_t start_pos = 0;
        while((start_pos = item.find(from, start_pos)) != std::string::npos) {
            item.replace(start_pos, from.length(), to);
            start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
        }
    }
    string endOfLine { "\n" };
    string separator { ": " };
    strncat(mCommunicationLog, endOfLine.c_str(), strlen(endOfLine.c_str()));
    strncat(mCommunicationLog, pPrefix, strlen(pPrefix));
    strncat(mCommunicationLog, separator.c_str(), strlen(separator.c_str()));
    strncat(mCommunicationLog, item.c_str(), item.length());
}

string SmtpClientBase::createAttachmentsText(const vector<Attachment*> &pAttachments) const
{
    string retval;	
    for (auto &item : pAttachments)
    {
        retval += "\r\n--sep\r\n";
        retval += "Content-Type: " + string(item->getMimeType()) + "; file=\"" + string(item->getName()) + "\"\r\n";
        retval += "Content-Disposition: Inline; filename=\"" + string(item->getName()) + "\"\r\n";
        retval += "Content-Transfer-Encoding: base64\r\n\r\n";
        retval += string((item->getBase64EncodedFile() != nullptr ? item->getBase64EncodedFile() : ""));

    }
    retval += "\r\n--sep--";
    return retval;
}

int SmtpClientBase::extractReturnCode(const char *pOutput) const
{
    if (pOutput != nullptr && strlen(pOutput) >= 3) {
        string code_str { pOutput };
        try {
            return std::stoi(code_str.substr(0, 3));
        } 
        catch (std::exception const &e) {
            return -1;
        }
    }
    return -1;
}

ServerAuthOptions *SmtpClientBase::extractAuthenticationOptions(const char *pEhloOutput)
{
    ServerAuthOptions *retVal = nullptr;
    const string AUTH_LINE_PREFIX = "250-AUTH";
    if (pEhloOutput == nullptr) {
        return retVal;
    }
    const string DELIMITER { "\r\n" };
    string ehlo_output { pEhloOutput }; 
    size_t ehlo_character_index { 0 };
    while((ehlo_character_index = ehlo_output.find(DELIMITER)) != string::npos) {
        string line { ehlo_output.substr(0, ehlo_character_index)};
        //Find the line that begin with 250-AUTH
        if (line.substr(0, AUTH_LINE_PREFIX.length()) == AUTH_LINE_PREFIX) {
            retVal = new ServerAuthOptions();
            //Find each options 
            vector<string> options;
            size_t line_character_index { 0 };
            while((line_character_index = line.find(" ")) != string::npos) {
                string option { line.substr(0, line_character_index)};
                options.push_back(option);
                line.erase(0, line_character_index + 1);
            }
            options.push_back(line);
            //Try to match the string options with the ServerAuthOptions struct attributes
            for_each(options.begin(), options.end(), [&retVal](const string &option) {
                if (option == "PLAIN") {
                    retVal->Plain = true;
                }
                else if (option == "LOGIN") {
                    retVal->Login = true;
                }
                else if (option == "XOAUTH2") {
                    retVal->XOAuth2 = true;
                }                
                else if (option == "PLAIN-CLIENTTOKEN") {
                    retVal->Plain_ClientToken = true;
                }                
                else if (option == "OAUTHBEARER") {
                    retVal->OAuthBearer = true;
                }                
                else if (option == "XOAUTH") {
                    retVal->XOAuth = true;
                }
            });
            break;
        }
        ehlo_output.erase(0, ehlo_character_index + DELIMITER.length());
    }
    return retVal;
}