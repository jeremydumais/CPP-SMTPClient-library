#include "..\include\SMTPClient.h"
#include <WinSock2.h>
#include <ws2tcpip.h>
#include <stdexcept>
#include <iostream>
#include <sstream>

using namespace std;

namespace jed_utils
{
	SmtpClient::SmtpClient(const string &pServerName, const unsigned int pPort)
	{
		this->mServerName = new string(pServerName);
		this->mPort = pPort;
		mServerReply = nullptr;
	}

	SmtpClient::~SmtpClient()
	{
		if (mServerName)
			delete mServerName;
		if (mServerReply)
			delete mServerReply;
	}

	void SmtpClient::sendMail(const Message &pMsg)
	{
		DWORD dwRetval;
		struct addrinfo *result = nullptr;
		struct addrinfo hints; 
		unsigned int sock = 0;
		WSADATA wsaData;

		if (mServerReply)
		{
			delete mServerReply;
			mServerReply = nullptr;
		}

		ostringstream body_ss;
		body_ss << "--sep\r\nContent-Type: " << pMsg.getMimeType() << "; charset=UTF-8\r\n\r\n" << pMsg.getBody() << "\r\n";
		string body_real = body_ss.str();

		//If there's attachments, prepare the attachments text content
		if (pMsg.getAttachmentsCount() > 0)
		{
			string attachments_text = createAttachmentsText(pMsg.getAttachments());
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

		dwRetval = getaddrinfo((*mServerName).c_str(), "25", &hints, &result);
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
		//Send command for the recepients
		for(auto &item : pMsg.getTo())
			writeCommand(sock, "RCPT TO: %s\r\n", item.getEmailAddress());
		// Data section
		writeCommand(sock, "DATA\r\n", "");
		// Mail headers
		writeCommand(sock, "From: %s\r\n", pMsg.getFrom());
		for(auto &item : pMsg.getTo())
			writeCommand(sock, "To: %s\r\n", item, false);
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

	void SmtpClient::writeCommand(const unsigned int pSock, const string &pStr, const string &pArg, const bool pAskForReply)
	{
		char buf[4096];

		if (pArg != "")
			snprintf(buf, sizeof(buf), pStr.c_str(), pArg.c_str());
		else
			snprintf(buf, sizeof(buf), pStr.c_str());


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
				if (mServerReply == nullptr)
				{
					mServerReply = new string(outbuf);
				}
				else
				{
					(*mServerReply) += string(outbuf);
				}
				
			}
		}
	}

	const string &SmtpClient::getServerReply() const
	{
		return *mServerReply;
	}

	string SmtpClient::createAttachmentsText(const vector<Attachment> &pAttachments)
	{
		string retval = "";	
		for (auto &item : pAttachments)
		{
			retval += "\r\n--sep\r\n";
			retval += "Content-Type: " + item.getMimeType() + "; file=\"" + item.getName() + "\"\r\n";
			retval += "Content-Disposition: Inline; filename=\"" + item.getName() + "\"\r\n";
			retval += "Content-Transfer-Encoding: base64\r\n\r\n";
			retval += item.getBase64EncodedFile();;

		}
		retval += "\r\n--sep--";
		return retval;
	}
}