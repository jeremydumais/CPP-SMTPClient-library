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
    : SmtpClientBase(pServerName, pPort)
{
}

SmtpClient::~SmtpClient()
{
    cleanup();
}

//Copy constructor
SmtpClient::SmtpClient(const SmtpClient &other)
    : SmtpClientBase(other)
{
}

//Assignment operator
SmtpClient& SmtpClient::operator=(const SmtpClient &other)
{
    if (this != &other) {
        SmtpClientBase::operator=(other);
    }
    return *this;
}

//Move constructor
SmtpClient::SmtpClient(SmtpClient &&other) noexcept
    : SmtpClientBase(move(other))
{
}

//Move assignement
SmtpClient& SmtpClient::operator=(SmtpClient &&other) noexcept
{
    if (this != &other) {
        SmtpClientBase::operator=(move(other));
    }
    return *this;
}

void SmtpClient::cleanup()
{
    if (mSock != 0) {
        #ifdef _WIN32
            shutdown(mSock, SD_BOTH);
            closesocket(mSock);
        #else
            close(mSock);
        #endif 
    }
    mSock = 0;
    #ifdef _WIN32
        WSACleanup();
    #endif
} 

int SmtpClient::establishConnectionWithServer() 
{
    int session_init_return_code = initializeSession();
    if (session_init_return_code != 0) {
        return session_init_return_code;
    }

    int server_greetings_return_code = checkServerGreetings();
    if (server_greetings_return_code != 220) {
        return server_greetings_return_code;
    }

    int client_init_return_code = sendServerIdentification();
    if (client_init_return_code != 250) {
        return client_init_return_code;
    }

    return 0;
}

int SmtpClient::sendCommand(const char *pCommand, int pErrorCode) 
{
    return sendRawCommand(pCommand, pErrorCode);
}

int SmtpClient::sendCommandWithFeedback(const char *pCommand, int pErrorCode, int pTimeoutCode) 
{
    return sendRawCommand(pCommand, pErrorCode, pTimeoutCode);
}
