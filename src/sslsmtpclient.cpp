#include <algorithm>
#include "base64.h"
#include "sslsmtpclient.h"
#include "socketerrors.h"
#include "sslerrors.h"
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#ifdef _WIN32
	#include <WinSock2.h>
    #include <ws2tcpip.h>
#else
    #include <fcntl.h>
    #include <openssl/bio.h> /* BasicInput/Output streams */
    #include <openssl/err.h>
    #include <netdb.h>
    #include <netinet/in.h>
    #include <sys/socket.h>	
    #include <unistd.h>
#endif
#include <vector>

using namespace std;
using namespace jed_utils;

SSLSmtpClient::SSLSmtpClient(const char *pServerName, unsigned int pPort)
    : mServerName(nullptr),
      mPort(pPort),
      mUsername(nullptr),
      mPassword(nullptr),
      mCommunicationLog(nullptr),
      mCommandTimeOut(3),
      mLastSocketErrNo(0),
      mSock(0),
      mBIO(nullptr),
      mCTX(nullptr),
      mSSL(nullptr)
{
    if (pServerName == nullptr || strcmp(pServerName, "") == 0) {
        throw invalid_argument("Server name cannot be null or empty");
    }
    size_t server_name_len = strlen(pServerName);
	mServerName = new char[server_name_len + 1];
	strncpy(mServerName, pServerName, server_name_len);
    mServerName[server_name_len] = '\0';
}

SSLSmtpClient::~SSLSmtpClient()
{    
    delete[] mServerName;
    mServerName = nullptr;
    delete[] mCommunicationLog;
    mCommunicationLog = nullptr;
}

void SSLSmtpClient::cleanup()
{
    SSL_CTX_free(mCTX);
    mCTX = nullptr;
    BIO_free_all(mBIO);
    mBIO = nullptr;
    close(mSock);
    mSock = 0;
}

int SSLSmtpClient::initSession() 
{
    delete[] mCommunicationLog;
    mCommunicationLog = new char[4096];
    mCommunicationLog[0] = '\0';

    mSock = socket(AF_INET, SOCK_STREAM, 0);
    if (mSock < 0) {
        mLastSocketErrNo = errno;
        return SOCKET_INIT_SESSION_CREATION_ERROR;
    }

    char outbuf[1024];
    struct hostent *host = gethostbyname(mServerName);
    struct sockaddr_in saddr_in {};
    saddr_in.sin_family = AF_INET;
    saddr_in.sin_port = htons(static_cast<u_short>(mPort));
    saddr_in.sin_addr.s_addr = 0;
    memcpy(reinterpret_cast<char*>(&(saddr_in.sin_addr)), host->h_addr, host->h_length);
    stringstream ss;
    ss << "Trying to connect to " << mServerName << " on port " << mPort;
    addCommunicationLogItem(ss.str().c_str());
    if (connect(mSock, reinterpret_cast<struct sockaddr*>(&saddr_in), sizeof(saddr_in)) == -1) {
        mLastSocketErrNo = errno;
        return SOCKET_INIT_SESSION_CONNECT_ERROR;
    } 

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

int SSLSmtpClient::initClient() 
{
    string ehlo { "ehlo localhost\r\n" };
    addCommunicationLogItem(ehlo.c_str());
    return sendCommand(ehlo.c_str(), 
        SOCKET_INIT_CLIENT_SEND_EHLO_ERROR, 
        SOCKET_INIT_CLIENT_SEND_EHLO_TIMEOUT);
}

int SSLSmtpClient::initTLS()
{
    string start_tls_cmd { "STARTTLS\r\n" };
    addCommunicationLogItem(start_tls_cmd.c_str());
    return sendCommand(start_tls_cmd.c_str(), 
        SOCKET_INIT_CLIENT_SEND_STARTTLS_ERROR, 
        SOCKET_INIT_CLIENT_SEND_STARTTLS_TIMEOUT);
}

void SSLSmtpClient::InitSSL_CTX()
{
    SSL_library_init();

    OpenSSL_add_all_algorithms();
    SSL_load_error_strings();
    const SSL_METHOD *method = TLSv1_2_client_method();
    mCTX = SSL_CTX_new(method);

    if (mCTX == nullptr) {
        mLastSocketErrNo = ERR_get_error();
    }
}

int SSLSmtpClient::startTLSNegotiation()
{
    addCommunicationLogItem("<Start TLS negotiation>");    
    InitSSL_CTX();
    if (mCTX == nullptr) {
        return SSL_CLIENT_STARTTLS_INITSSLCTX_ERROR;
    }

    mBIO = BIO_new_ssl_connect(mCTX);
    if (mBIO == nullptr) {
        return SSL_CLIENT_STARTTLS_BIONEWSSLCONNECT_ERROR;
    }

    /* Link bio channel, SSL session, and server endpoint */
    char name[1024];
    sprintf(name, "%s:%i", mServerName, mPort);
    BIO_get_ssl(mBIO, &mSSL); /* session */
    SSL_set_fd(mSSL, mSock);
    SSL_set_mode(mSSL, SSL_MODE_AUTO_RETRY); /* robustness */
    BIO_set_conn_hostname(mBIO, name); /* prepare to connect */

    /* Specifies the locations for ctx, at which CA certificates 
       for verification purposes are located */
    if (!SSL_CTX_load_verify_locations(mCTX,
            "/etc/ssl/certs/ca-certificates.crt", 
            "/etc/ssl/certs/")) {
        mLastSocketErrNo = ERR_get_error();
        return SSL_CLIENT_STARTTLS_CTX_LOAD_VERIFY_LOCATIONS_ERROR;
    }

    long verify_flag = SSL_get_verify_result(mSSL);
    if (verify_flag != X509_V_OK) {
        fprintf(stderr,
            "##### Certificate verification error (%i) but continuing...\n",
            (int)verify_flag);
    }

    /* Try to connect */
    if (BIO_do_connect(mBIO) <= 0) {
        cleanup();
        mLastSocketErrNo = ERR_get_error();
        return SSL_CLIENT_STARTTLS_BIO_CONNECT_ERROR;
    }

    /* Try to do the handshake */
    addCommunicationLogItem("<Negotiate a TLS session>", "c & s");    
    if (BIO_do_handshake(mBIO) <= 0) {
        cleanup();
        mLastSocketErrNo = ERR_get_error();
        return SSL_CLIENT_STARTTLS_BIO_HANDSHAKE_ERROR;
    }

    addCommunicationLogItem("<Check result of negotiation>", "c & s");    
    /* Step 1: Verify a server certificate was presented 
       during the negotiation */
    X509* cert = SSL_get_peer_certificate(mSSL);
    if(cert != nullptr) { 
        X509_free(cert); /* Free immediately */
    } 
    if(cert == nullptr) {
        cleanup();
        return SSL_CLIENT_STARTTLS_GET_CERTIFICATE_ERROR;
    }

    /* Step 2: verify the result of chain verification */
    /* Verification performed according to RFC 4158    */
    int res = SSL_get_verify_result(mSSL);
    if(!(X509_V_OK == res)) {
        cleanup();
        return SSL_CLIENT_STARTTLS_VERIFY_RESULT_ERROR;
    }

    addCommunicationLogItem("TLS session ready!");    

    return 0;
}

int SSLSmtpClient::initSecureClient()
{
    addCommunicationLogItem("Contacting the server again but via the secure channel...");
    string ehlo { "ehlo localhost\r\n"s };
    addCommunicationLogItem(ehlo.c_str());
    return sendTLSCommandWithFeedback(ehlo.c_str(), SSL_CLIENT_INITSECURECLIENT_ERROR, SSL_CLIENT_INITSECURECLIENT_TIMEOUT);
}

int SSLSmtpClient::authenticate(const char* pUsername, const char* pPassword)
{
    addCommunicationLogItem("AUTH PLAIN ***************\r\n");
    stringstream ss_credentials;
    //Format : \0username\0password
    ss_credentials << '\0' << pUsername << '\0' << pPassword;
    string str_credentials = ss_credentials.str();
    stringstream ss;
    ss << "AUTH PLAIN " 
       << Base64::Encode(reinterpret_cast<const unsigned char*>(str_credentials.c_str()),
             strlen(pUsername) + strlen(pPassword) + 2) // + 2 for the two null characters 
       << "\r\n";
    return sendTLSCommandWithFeedback(ss.str().c_str(), SSL_CLIENT_AUTHENTICATE_ERROR, SSL_CLIENT_AUTHENTICATE_TIMEOUT);
}

int SSLSmtpClient::connectToServer()
{
    int session_init_return_code = initSession();
    if (session_init_return_code != 220) {
        return session_init_return_code;
    }

    int client_init_return_code = initClient();
    if (client_init_return_code != 250) {
        return client_init_return_code;
    }

    int tls_init_return_code = initTLS();
    if (tls_init_return_code != 220) {
        return tls_init_return_code;
    }

    int tls_start_return_code = startTLSNegotiation();
    if (tls_start_return_code != 0) {
        return tls_start_return_code;
    }

    int client_initSecure_return_code = initSecureClient();
    if (client_initSecure_return_code != 250) {
        return client_initSecure_return_code;
    }

    if (mUsername!=nullptr) {
        int client_auth_return_code = authenticate(mUsername, mPassword);
        if (client_auth_return_code != 235) {
            return client_auth_return_code;
        }
    }
    return 0;
}

int SSLSmtpClient::setMailRecipients(const Message &pMsg) 
{
    stringstream ss_mail_from;
    ss_mail_from << "MAIL FROM: <"s << pMsg.getFrom().getDisplayName() << " "s << pMsg.getFrom().getEmailAddress() << ">\r\n"s;
    addCommunicationLogItem(ss_mail_from.str().c_str());
    int mail_from_ret_code = sendTLSCommandWithFeedback(ss_mail_from.str().c_str(), SSL_CLIENT_SENDMAIL_MAILFROM_ERROR, SSL_CLIENT_SENDMAIL_MAILFROM_TIMEOUT);
    if (mail_from_ret_code != 250) {
        return mail_from_ret_code;
    }

    //Send command for the recipients
    int rcpt_to_ret_code = 250;
    for_each(pMsg.getTo(), pMsg.getTo() + pMsg.getToCount(), [this, &rcpt_to_ret_code](MessageAddress *address) {
        stringstream ss_rcpt_to;
        ss_rcpt_to << "RCPT TO: <"s << address->getEmailAddress() << ">\r\n"s;
        addCommunicationLogItem(ss_rcpt_to.str().c_str());
        int ret_code = sendTLSCommandWithFeedback(ss_rcpt_to.str().c_str(), SSL_CLIENT_SENDMAIL_RCPTTO_ERROR, SSL_CLIENT_SENDMAIL_RCPTTO_TIMEOUT);
        if (ret_code != 250) {
            rcpt_to_ret_code = ret_code;
        }
    });
    if (rcpt_to_ret_code != 250) {
        return rcpt_to_ret_code;
    }
    return 0;
}

int SSLSmtpClient::setMailHeaders(const Message &pMsg)
{
    // Data section
    string data_cmd = "DATA\r\n";
    addCommunicationLogItem(data_cmd.c_str());
    int data_ret_code = sendTLSCommandWithFeedback(data_cmd.c_str(), SSL_CLIENT_SENDMAIL_DATA_ERROR, SSL_CLIENT_SENDMAIL_DATA_TIMEOUT);
    if (data_ret_code != 354) {
        return data_ret_code;
    }

    // Mail headers
    // From
    stringstream ss_header_from;
    ss_header_from << "From: " << pMsg.getFrom().getEmailAddress() << "\r\n";
    addCommunicationLogItem(ss_header_from.str().c_str());
    int header_from_ret_code = sendTLSCommand(ss_header_from.str().c_str(), SSL_CLIENT_SENDMAIL_HEADERFROM_ERROR);
    if (header_from_ret_code != 0) {
        return header_from_ret_code;
    }

    // To
    int header_to_ret_code { 0 };
    for_each(pMsg.getTo(), pMsg.getTo() + pMsg.getToCount(), [this, &header_to_ret_code](MessageAddress *address) {
        stringstream ss_header_to;
        ss_header_to << "To: " << address->getEmailAddress() << "\r\n";
        addCommunicationLogItem(ss_header_to.str().c_str());
        int ret_code = sendTLSCommand(ss_header_to.str().c_str(), SSL_CLIENT_SENDMAIL_HEADERTO_ERROR);
        if (ret_code != 0) {
            header_to_ret_code = ret_code;
        }
    });
    if (header_to_ret_code != 0) {
        return header_to_ret_code;
    }

    // Subject
    stringstream ss_header_subject;
    ss_header_subject << "Subject: " << pMsg.getSubject() << "\r\n";
    addCommunicationLogItem(ss_header_subject.str().c_str());
    int header_subject_ret_code = sendTLSCommand(ss_header_subject.str().c_str(), SSL_CLIENT_SENDMAIL_HEADERSUBJECT_ERROR);
    if (header_subject_ret_code != 0) {
        return header_subject_ret_code;
    }

    //Content-Type
    string content_type { "Content-Type: multipart/mixed; boundary=sep\r\n\r\n" };
    addCommunicationLogItem(content_type.c_str());
    int header_content_type_ret_code = sendTLSCommand(content_type.c_str(), SSL_CLIENT_SENDMAIL_HEADERCONTENTTYPE_ERROR);
    if (header_content_type_ret_code != 0) {
        return header_content_type_ret_code;
    }

    return 0;
}

int SSLSmtpClient::setMailBody(const Message &pMsg)
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
            int body_part_ret_code = sendTLSCommand(body_real.substr(index_start, length).c_str(), SSL_CLIENT_SENDMAIL_BODYPART_ERROR);
            if (body_part_ret_code != 0) {
                return body_part_ret_code;
            }
        }
    }
    else {
        int body_ret_code = sendTLSCommand(body_real.c_str(), SSL_CLIENT_SENDMAIL_BODY_ERROR);
        if (body_ret_code != 0) {
            return body_ret_code;
        }
    }

    //End of data
    string end_command { "\r\n.\r\nQUIT\r\n" };
    addCommunicationLogItem(end_command.c_str());    
    int quit_ret_code = sendTLSCommand(end_command.c_str(), SSL_CLIENT_SENDMAIL_QUIT_ERROR);
    if (quit_ret_code != 0) {
        return quit_ret_code;
    }
    return 0;
}

int SSLSmtpClient::sendMail(const Message &pMsg)
{
    int client_connect_ret_code = connectToServer();
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

int SSLSmtpClient::sendCommand(const char *pCommand, int pErrorCode, int pTimeoutCode)
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
        addCommunicationLogItem(outbuf, "s");
        return extractReturnCode(outbuf);
    }
    
    return pTimeoutCode;
}

int SSLSmtpClient::sendTLSCommand(const char *pCommand, int pErrorCode)
{
    if (const int status = BIO_puts(mBIO, pCommand) < 0) {
        mLastSocketErrNo = ERR_get_error();
        cleanup();
        return pErrorCode;
    }
    return 0;
}

int SSLSmtpClient::sendTLSCommandWithFeedback(const char *pCommand, int pErrorCode, int pTimeoutCode)
{
    unsigned int waitTime {0};
    int bytes_received {0};
    char outbuf[1024];

    if (const int status = BIO_puts(mBIO, pCommand) < 0) {
        mLastSocketErrNo = ERR_get_error();
        cleanup();
        return pErrorCode;
    }
    
    while ((bytes_received = BIO_read(mBIO, outbuf, 1024)) <= 0 && waitTime < mCommandTimeOut) {
        sleep(1);
        waitTime += 1;
    }
    if (waitTime < mCommandTimeOut) {
        outbuf[bytes_received-1] = '\0';
        addCommunicationLogItem(outbuf, "s");
        return extractReturnCode(outbuf);
    }
    else {
        cleanup();
        return pTimeoutCode;
    }  
}


const char *SSLSmtpClient::getCommunicationLog() const
{
    return mCommunicationLog;
}

int SSLSmtpClient::extractReturnCode(const char *pOutput) const
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

void SSLSmtpClient::addCommunicationLogItem(const char *pItem, const char *pPrefix)
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
    strcat(mCommunicationLog, "\n");
    strcat(mCommunicationLog, pPrefix);
    strcat(mCommunicationLog, ": ");
    strcat(mCommunicationLog, item.c_str());
}

string SSLSmtpClient::createAttachmentsText(const vector<Attachment*> &pAttachments) const
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

void SSLSmtpClient::setCredentials(const char *pUsername, const char *pPassword)
{
    delete []mUsername;
    delete []mPassword;

    size_t username_len = strlen(pUsername);
	mUsername = new char[username_len + 1];
	strncpy(mUsername, pUsername, username_len);
    mUsername[username_len] = '\0';

    size_t password_len = strlen(pPassword);
	mPassword = new char[password_len + 1];
	strncpy(mPassword, pPassword, password_len);
    mUsername[password_len] = '\0';
}
