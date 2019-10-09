#include "sslsmtpclient.h"

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

SSLSmtpClient::SSLSmtpClient(const char *pServerName, unsigned int pPort)
    : mServerName(nullptr),
      mPort(pPort),
      mServerReply(nullptr)
{
    size_t server_name_len = strlen(pServerName);
	mServerName = new char[server_name_len + 1];
	strncpy(mServerName, pServerName, server_name_len);
    mServerName[server_name_len] = '\0';
}

SSLSmtpClient::~SSLSmtpClient()
{    
    delete[] mServerName;
    mServerName = nullptr;
    delete[] mServerReply;
    mServerReply = nullptr;
}

int SSLSmtpClient::initSession(const unsigned int pSock) 
{
    delete[] mServerReply;
    mServerReply = new char[4096];
    mServerReply[0] = '\0';

    const int TIME_OUT = 2;
    char outbuf[1024];
    struct hostent *host = gethostbyname(mServerName);
    struct sockaddr_in saddr_in {};
    saddr_in.sin_family = AF_INET;
    saddr_in.sin_port = htons(static_cast<u_short>(mPort));
    saddr_in.sin_addr.s_addr = 0;

    memcpy(reinterpret_cast<char*>(&(saddr_in.sin_addr)), host->h_addr, host->h_length);
    if (connect(pSock, reinterpret_cast<struct sockaddr*>(&saddr_in), sizeof(saddr_in)) == -1) {
        return -1;
    } 

    int waitTime = 0;
    while (recv(pSock, outbuf, 1024, 0) < 0 && waitTime < TIME_OUT)
    {
        sleep(1);
        waitTime += 1;
    }
    if (waitTime < TIME_OUT) {
        strcat(mServerReply, outbuf);
        return extractReturnCode(outbuf);
    }
    return -1;
}

int SSLSmtpClient::initClient(const unsigned int pSock) 
{
    const int TIME_OUT = 2;
    char outbuf[1024];

    string ehlo { "ehlo localhost\r\n" };
    if (send(pSock, ehlo.c_str(), ehlo.length(), 0) == -1) {
        cerr << "send command failed : " << errno << endl; //<< errno << endl;
        return 1;
    }
    int waitTime = 0;
    while (recv(pSock, outbuf, 1024, 0) < 0 && waitTime < TIME_OUT)
    {
        sleep(1);
        waitTime += 1;
    }
    if (waitTime < TIME_OUT) {
        strcat(mServerReply, outbuf);
        return extractReturnCode(outbuf);
    }
    
    return -1;
}

const char *SSLSmtpClient::getServerReply() const
{
    return mServerReply;
}

int SSLSmtpClient::extractReturnCode(const char *output) const
{
    if (output != nullptr && strlen(output) >= 3) {
        string code_str { output };
        try {
            return std::stoi(code_str.substr(0, 3));
        } 
        catch (std::exception const &e) {
            return -1;
        }
    }
    return -1;
}
