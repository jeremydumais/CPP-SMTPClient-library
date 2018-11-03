#include "..\include\SMTPClient.h"
#include <WinSock2.h>
#include <ws2tcpip.h>
#include <stdexcept>
#include <iostream>
#include <sstream>

using namespace std;

namespace jed_utils
{
	SmtpClient::SmtpClient(const char *pServerName, const unsigned int pPort)
	{
		this->mServerName = new char[strlen(pServerName) + 1];
		strcpy_s(this->mServerName, strlen(pServerName) + 1, pServerName);

		this->mPort = pPort;
		mServerReply = NULL;
	}

	SmtpClient::~SmtpClient()
	{
		delete mServerName;
		if (mServerReply != NULL)
			delete mServerReply;
	}

	void SmtpClient::sendMail(Message *pMsg)
	{
		DWORD dwRetval;
		struct addrinfo *result = NULL;
		struct addrinfo hints; 
		unsigned int sock = 0;
		WSADATA wsaData;

		if (mServerReply != NULL)
		{
			delete mServerReply;
			mServerReply = NULL;
		}

		ostringstream body_ss;
		body_ss << "--sep\r\nContent-Type: " << pMsg->getMimeType() << "; charset=UTF-8\r\n\r\n" << pMsg->getBody() << "\r\n";
		string body_real = body_ss.str();

		//If there's attachments, prepare the attachments text content
		if (pMsg->getAttachmentsPtr() && pMsg->getAttachmentsCount() > 0)
		{
			string attachments_text = createAttachmentsText(pMsg->getAttachmentsPtr(), pMsg->getAttachmentsCount());
			body_real += attachments_text;
		}

		/* Windows Sockets version */
		WORD wVersionRequested = MAKEWORD(2, 2);
		int wsa_retVal = WSAStartup(wVersionRequested, &wsaData);
		if (wsa_retVal != 0)
		{
			ostringstream error_stream;
			error_stream << "Windows Sockets startup error : " << wsa_retVal;
			throw CommunicationError(error_stream.str().c_str());
		}

		memset(&hints, 0, sizeof hints);
		hints.ai_family = AF_UNSPEC;  // use IPv4 or IPv6, whichever
		hints.ai_socktype = SOCK_STREAM;

		dwRetval = getaddrinfo(this->mServerName, "25", &hints, &result);
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

		writeCommand(sock, "HELO %s\r\n", pMsg->getFrom().getEmailAddress());    
		writeCommand(sock, "MAIL FROM: %s\r\n", pMsg->getFrom().getEmailAddress());
		//Send command for the recepients
		for (unsigned int index=0; index < pMsg->getToCount(); index++)
			writeCommand(sock, "RCPT TO: %s\r\n", (pMsg->getToPtr() + index)->getEmailAddress()); 
		// Data section
		writeCommand(sock, "DATA\r\n", "");
		// Mail headers
		writeCommand(sock, "From: %s\r\n", pMsg->getFrom());
		for (size_t index = 0; index < pMsg->getToCount(); index++)
			writeCommand(sock, "To: %s\r\n", *(pMsg->getToPtr() + index), false);
		writeCommand(sock, "Subject: %s\r\n", pMsg->getSubject(), false);
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
				writeCommand(sock, body_real.substr(index_start, length), "", false);
			}
		}
		else
			writeCommand(sock, "%s", body_real, false);
		writeCommand(sock, "\r\n", "", false);
		//End of data
		writeCommand(sock, ".\r\n", "", false); 
		writeCommand(sock, "QUIT\r\n", "", false);

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

	void SmtpClient::writeCommand(const unsigned int sock, const string str, const string arg, const bool ask_for_reply)
	{
		char buf[4096];

		if (arg != "")
			snprintf(buf, sizeof(buf), str.c_str(), arg.c_str());
		else
			snprintf(buf, sizeof(buf), str.c_str());


		int wsa_retVal = send(sock, buf, static_cast<int>(strlen(buf)), 0);
		if (wsa_retVal == SOCKET_ERROR) {
			cout << "send failed: " << WSAGetLastError() << endl;
			closesocket(sock);
			WSACleanup();
			ostringstream error_stream;
			error_stream << "send command failed : " << WSAGetLastError();
			throw CommunicationError(error_stream.str().c_str());
		}
		if (ask_for_reply)
		{
			// read a reply from server
			char outbuf[1024];
			int len = recv(sock, outbuf, 1024, 0);
			if (len > 0)
			{
				outbuf[len] = '\0';
				if (mServerReply == NULL)
				{
					mServerReply = new char[strlen(outbuf) + 1];
					strcpy_s(this->mServerReply, strlen(outbuf) + 1, outbuf);
				}
				else
				{
					size_t size_new_buf = strlen(mServerReply) + strlen(outbuf) + 1;
					char *server_reply_temp = new char[size_new_buf];
					strcpy_s(server_reply_temp, strlen(mServerReply) + 1, mServerReply);
					delete mServerReply;
					mServerReply = server_reply_temp;
					strcat_s(this->mServerReply, size_new_buf, outbuf);
				}
				
			}
		}
	}

	const char *SmtpClient::getServerReply() const
	{
		return this->mServerReply;
	}

	string SmtpClient::createAttachmentsText(const Attachment *pAttachments, const unsigned int pAttachementsCount)
	{
		string retval = "";	
		for (unsigned int index=0; index < pAttachementsCount; index++)
		{
			retval += "\r\n--sep\r\n";
			retval += "Content-Type: " + string((*(pAttachments + index)).getMimeType()) + "; file=\"" + string((*(pAttachments + index)).getName()) + "\"\r\n";
			retval += "Content-Disposition: Inline; filename=\"" + string((*(pAttachments + index)).getName()) + "\"\r\n";
			retval += "Content-Transfer-Encoding: base64\r\n\r\n";
			string base64_file = pAttachments[index].getBase64EncodedFile();
			retval += base64_file;

		}
		retval += "\r\n--sep--";
		return retval;
	}
}