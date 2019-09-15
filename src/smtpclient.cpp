#include "smtpclient.h"

#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#ifdef _WIN32
	#include <WinSock2.h>
    #include <ws2tcpip.h>
#else
    #include <netdb.h>
    #include <netinet/in.h>
    #include <sys/socket.h>	
    #include <unistd.h>
#endif
#include <vector>

using namespace std;
using namespace jed_utils;

SmtpClient::SmtpClient(const char *pServerName, unsigned int pPort)
    : mServerName(nullptr),
      mPort(pPort),
      mServerReply(nullptr)
{
    size_t server_name_len = strlen(pServerName);
	mServerName = new char[server_name_len + 1];
	strncpy(mServerName, pServerName, server_name_len);
    mServerName[server_name_len] = '\0';
}

SmtpClient::~SmtpClient()
{
    delete[] mServerName;
    mServerName = nullptr;
    delete[] mServerReply;
    mServerReply = nullptr;
}

//Copy constructor
SmtpClient::SmtpClient(const SmtpClient &other)
    : mServerName(new char[strlen(other.mServerName) + 1]),
      mPort(other.mPort),
      mServerReply(nullptr)
{
    strncpy(mServerName, other.mServerName, strlen(other.mServerName) + 1);
	mServerName[strlen(other.mServerName)] = '\0';

    if (other.mServerReply != nullptr) {
        mServerReply = new char[strlen(other.mServerReply) + 1];
        strncpy(mServerReply, other.mServerReply, strlen(other.mServerReply) + 1);
	    mServerReply[strlen(other.mServerReply)] = '\0';
    }
}

//Copy assignment
SmtpClient& SmtpClient::operator=(const SmtpClient &other)
{
    if (this != &other)
	{
        //mServerName
        delete[] mServerName;
        mServerName = new char[strlen(other.mServerName) + 1];
        strncpy(mServerName, other.mServerName, strlen(other.mServerName) + 1);
        mServerName[strlen(other.mServerName)] = '\0';
        //mPort
        mPort = other.mPort;
        //mServerName
        delete[] mServerReply;
        mServerReply = nullptr;
        if (other.mServerReply != nullptr) {
            mServerReply = new char[strlen(other.mServerReply) + 1];
            strncpy(mServerReply, other.mServerReply, strlen(other.mServerReply) + 1);
            mServerReply[strlen(other.mServerReply)] = '\0';
        }

    }
    return *this;
}

//Move constructor
SmtpClient::SmtpClient(SmtpClient &&other) noexcept
    : mServerName(other.mServerName),
      mPort(other.mPort),
      mServerReply(other.mServerReply)
{
    other.mServerName = nullptr;
    other.mPort = 0;
    other.mServerReply = nullptr;
}

//Move assignement
SmtpClient& SmtpClient::operator=(SmtpClient &&other) noexcept
{
    if (this != &other)
	{
		delete[] mServerName;
		delete[] mServerReply;

        mServerName = other.mServerName;
        mPort = other.mPort;
        mServerReply = other.mServerReply;

        other.mServerName = nullptr;
        other.mPort = 0;
        other.mServerReply = nullptr;
    }
    return *this;
}


#ifdef _WIN32
//Windows version of sendMail method
void SmtpClient::sendMail(const Message &pMsg)
{
    DWORD dwRetval;
    struct addrinfo *result = nullptr;
    struct addrinfo hints; 
    unsigned int sock = 0;
    WSADATA wsaData;

	delete[] mServerReply;
	mServerReply = new char[2048];
	mServerReply[0] = '\0';

    ostringstream body_ss;
    body_ss << "--sep\r\nContent-Type: " << pMsg.getMimeType() << "; charset=UTF-8\r\n\r\n" << pMsg.getBody() << "\r\n";
    string body_real = body_ss.str();

    //If there's attachments, prepare the attachments text content
	Attachment** arr_attachment = pMsg.getAttachments();

	vector<Attachment*> vect_attachment(arr_attachment, arr_attachment + pMsg.getAttachmentsCount());
	if (pMsg.getAttachmentsCount() > 0) {
		string attachments_text = createAttachmentsText(vect_attachment);
		body_real += attachments_text;
	}

    /* Windows Sockets version */
    WORD wVersionRequested = MAKEWORD(2, 2);
    int wsa_retVal = WSAStartup(wVersionRequested, &wsaData);
    if (wsa_retVal != 0) {
        ostringstream error_stream;
        error_stream << "Windows Sockets startup error : " << wsa_retVal;
        throw CommunicationError(error_stream.str().c_str());
    }

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;  // use IPv4 or IPv6, whichever
    hints.ai_socktype = SOCK_STREAM;

    dwRetval = getaddrinfo(mServerName, "25", &hints, &result);
    if (dwRetval != 0) 
    {
        WSACleanup();
        ostringstream error_stream;
        error_stream << "Windows Sockets getaddrinfo error : " << dwRetval;
        throw CommunicationError(error_stream.str().c_str());
    }

    sock = static_cast<unsigned int>(socket(result->ai_family, result->ai_socktype, result->ai_protocol));
    wsa_retVal = connect(sock, result->ai_addr, static_cast<int>(result->ai_addrlen));
    if (wsa_retVal == SOCKET_ERROR) 
    {
        WSACleanup();
        ostringstream error_stream;
        error_stream << "Windows Sockets connect error : " << WSAGetLastError();
        throw CommunicationError(error_stream.str().c_str());
    }

    writeCommand(sock, "HELO %s\r\n", pMsg.getFrom().getEmailAddress());    
    writeCommand(sock, "MAIL FROM: %s\r\n", pMsg.getFrom().getEmailAddress());
    //Send command for the recipients
	for (size_t i = 0; i < pMsg.getToCount(); i++) {
		MessageAddress* to_addr = pMsg.getTo()[i];
		writeCommand(sock, "RCPT TO: %s\r\n", to_addr->getEmailAddress());
	}
    // Data section
    writeCommand(sock, "DATA\r\n", "");
    // Mail headers
    writeCommand(sock, "From: %s\r\n", pMsg.getFrom().getEmailAddress());
	for (size_t i = 0; i < pMsg.getToCount(); i++) {
		MessageAddress* to_addr = pMsg.getTo()[i];
		writeCommand(sock, "To: %s\r\n", to_addr->getEmailAddress(), false);
	}
    writeCommand(sock, "Subject: %s\r\n", pMsg.getSubject(), false);
    writeCommand(sock, "MIME-Version: 1.0\r\n", "", false);
    writeCommand(sock, "Content-Type: multipart/mixed; boundary=sep\r\n", "", false);
    writeCommand(sock, "\r\n", "", false);
    // Body part
    if (body_real.length() > 512)
    {
        //Split into chunk
        for (size_t index_start = 0; index_start < body_real.length(); index_start += 512)
        {
            size_t length = 512;
            if (index_start + 512 > body_real.length() - 1)
                length = body_real.length() - index_start;
            writeCommand(sock, body_real.substr(index_start, length).c_str(), "", false);
        }
    }
    else
        writeCommand(sock, "%s", body_real.c_str(), false);
    writeCommand(sock, "\r\n", "", false);
    //End of data
    writeCommand(sock, ".\r\n", "", false); 
    writeCommand(sock, "QUIT\r\n", "", false);

	// winsock requires a special function for sockets
	shutdown(sock, SD_BOTH);
    wsa_retVal = closesocket(sock); 
    if (wsa_retVal == SOCKET_ERROR)
    {
		WSACleanup();
		ostringstream error_stream;
        error_stream << "Windows Sockets connect error : " << WSAGetLastError();
        throw CommunicationError(error_stream.str().c_str());
    }

	WSACleanup();
}

//Windows version of writeCommand method
void SmtpClient::writeCommand(unsigned int pSock, const char *pStr, const char *pArg, bool pAskForReply)
{
    char buf[4096];

    if (pArg != "")
        snprintf(buf, sizeof(buf), pStr, pArg);
    else
        snprintf(buf, sizeof(buf), pStr);


	int wsa_retVal = send(pSock, buf, static_cast<int>(strlen(buf)), 0);
    if (wsa_retVal == SOCKET_ERROR) {
        cout << "send failed: " << WSAGetLastError() << endl;
        closesocket(pSock);
        WSACleanup();
        ostringstream error_stream;
        error_stream << "send command failed : " << WSAGetLastError();
        throw CommunicationError(error_stream.str().c_str());
    }
    if (pAskForReply)
    {
        // read a reply from server
        char outbuf[1024];
		int len = recv(pSock, outbuf, 1024, 0);
        if (len > 0)
        {
            outbuf[len] = '\0';
			strcat(mServerReply, outbuf);
        }
    }
}

#else

//Linux version of sendMail method	
void SmtpClient::sendMail(const Message &pMsg)
{
    delete[] mServerReply;
    mServerReply = new char[2048];

    ostringstream body_ss;
    body_ss << "--sep\r\nContent-Type: " << pMsg.getMimeType() << "; charset=UTF-8\r\n\r\n" << pMsg.getBody() << "\r\n";
    string body_real = body_ss.str();

    //If there's attachments, prepare the attachments text content
    Attachment** arr_attachment = pMsg.getAttachments();

    vector<Attachment*> vect_attachment(arr_attachment, arr_attachment + pMsg.getAttachmentsCount());
    if (pMsg.getAttachmentsCount() > 0) {
        string attachments_text = createAttachmentsText(vect_attachment);
        body_real += attachments_text;
    }

    int sock = socket(AF_INET, SOCK_STREAM, 0);
    struct hostent *host = gethostbyname(mServerName);
    struct sockaddr_in saddr_in {};
    saddr_in.sin_family = AF_INET;
    saddr_in.sin_port = htons(static_cast<u_short>(mPort));
    saddr_in.sin_addr.s_addr = 0;

    memcpy(reinterpret_cast<char*>(&(saddr_in.sin_addr)), host->h_addr, host->h_length);

    if (connect(sock, reinterpret_cast<struct sockaddr*>(&saddr_in), sizeof(saddr_in)) == -1) {
        throw CommunicationError("Unable to connect. Error -1;");
    }

    writeCommand(sock, "HELO %s\r\n", pMsg.getFrom().getEmailAddress());    
    writeCommand(sock, "MAIL FROM: %s\r\n", pMsg.getFrom().getEmailAddress());
    //Send command for the recipients
    for(size_t i=0; i<pMsg.getToCount(); i++) {
        MessageAddress* to_addr = pMsg.getTo()[i];
        writeCommand(sock, "RCPT TO: %s\r\n", to_addr->getEmailAddress());
    }
    // Data section
    writeCommand(sock, "DATA\r\n", "");
    // Mail headers
    writeCommand(sock, "From: %s\r\n", pMsg.getFrom().getEmailAddress());
    for(size_t i=0; i<pMsg.getToCount(); i++) {
        MessageAddress* to_addr = pMsg.getTo()[i];
        writeCommand(sock, "To: %s\r\n", to_addr->getEmailAddress(), false);
    }
    writeCommand(sock, "Subject: %s\r\n", pMsg.getSubject(), false);
    writeCommand(sock, "MIME-Version: 1.0\r\n", "", false);
    writeCommand(sock, "Content-Type: multipart/mixed; boundary=sep\r\n", "", false);
    writeCommand(sock, "\r\n", "", false);
    // Body part
    if (body_real.length() > 512)
    {
        //Split into chunk
        for (size_t index_start = 0; index_start < body_real.length(); index_start += 512)
        {
            size_t length = 512;
            if (index_start + 512 > body_real.length() - 1) {
                length = body_real.length() - index_start;
            }
            writeCommand(sock, body_real.substr(index_start, length).c_str(), "", false);
        }
    }
    else {
        writeCommand(sock, "%s", body_real.c_str(), false);
    }
    writeCommand(sock, "\r\n", "", false);
    //End of data
    writeCommand(sock, ".\r\n", "", false); 
    writeCommand(sock, "QUIT\r\n", "", false);

    close(sock);
}

//Linux version of writeCommand method
void SmtpClient::writeCommand(const unsigned int pSock, const char *pStr, const char *pArg, const bool pAskForReply)
{
     char buf[4096];

    if (pArg != nullptr) {
        snprintf(buf, sizeof(buf), pStr, pArg);
    }        
    else {
        snprintf(buf, sizeof(buf), pStr);
    }
    
    send(pSock, buf, strlen(buf), 0);
    if (pAskForReply) {
        // read a reply from server
        char outbuf[1024];
        int len = recv(pSock, outbuf, 1024, 0);
        if (len > 0) {
            outbuf[len] = '\0';
            strcat(mServerReply,outbuf);
        }
    }
}

#endif

const char *SmtpClient::getServerReply() const
{
    return mServerReply;
}

string SmtpClient::createAttachmentsText(const vector<Attachment*> &pAttachments)
{
    string retval;	
    for (auto &item : pAttachments)
    {
        retval += "\r\n--sep\r\n";
        retval += "Content-Type: " + string(item->getMimeType()) + "; file=\"" + string(item->getName()) + "\"\r\n";
        retval += "Content-Disposition: Inline; filename=\"" + string(item->getName()) + "\"\r\n";
        retval += "Content-Transfer-Encoding: base64\r\n\r\n";
        retval += string(item->getBase64EncodedFile());

    }
    retval += "\r\n--sep--";
    return retval;
}
