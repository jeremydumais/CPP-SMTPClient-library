#include "..\include\SMTPClient.h"
#include <WinSock2.h>
#include <ws2tcpip.h>
#include <stdexcept>
#include <iostream>

namespace jed_utils
{
	smtp_client::smtp_client(const std::string server_name, const unsigned int port)
	{
		this->server_name = server_name;
		this->port = port;
	}

	void smtp_client::send_mail(const std::string from,
		const std::string to,
		const std::string subject,
		const std::string body)
	{
		DWORD dwRetval;
		struct addrinfo *result = NULL;
		struct addrinfo hints; 
		unsigned int sock = 0;
		WSADATA wsaData;

		this->server_reply = "";
		/* Windows Sockets version */
		WORD wVersionRequested = MAKEWORD(2, 2);
		int wsa_retVal = WSAStartup(wVersionRequested, &wsaData);
		if (wsa_retVal != 0)
			throw communication_error(std::string("Windows Sockets startup error : ") + std::to_string(wsa_retVal));

		memset(&hints, 0, sizeof hints);
		hints.ai_family = AF_UNSPEC;  // use IPv4 or IPv6, whichever
		hints.ai_socktype = SOCK_STREAM;

		dwRetval = getaddrinfo(this->server_name.c_str(), "25", &hints, &result);
		if (dwRetval != 0) 
		{
			WSACleanup();
			throw communication_error(std::string("Windows Sockets getaddrinfo error : ") + std::to_string(dwRetval));
		}

		sock = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
		wsa_retVal = connect(sock, result->ai_addr, result->ai_addrlen);
		if (wsa_retVal == SOCKET_ERROR) 
		{
			WSACleanup();
			throw communication_error(std::string("Windows Sockets connect error : ") + std::to_string(WSAGetLastError()));
		}

		write_command(sock, "HELO %s\r\n", from);    
		write_command(sock, "MAIL FROM: %s\r\n", from);   
		write_command(sock, "RCPT TO: %s\r\n", to);     
		// Data section
		write_command(sock, "DATA\r\n", "");
		// Mail headers
		write_command(sock, "From: %s\r\n", from);
		write_command(sock, "To: %s\r\n", to, false);
		write_command(sock, "Subject: %s\r\n", subject, false);
		write_command(sock, "\r\n", "", false);
		// Body part
		write_command(sock, "%s\r\n", body, false);   
		//End of data
		write_command(sock, ".\r\n", "", false); 
		write_command(sock, "QUIT\r\n", "");    

		wsa_retVal = closesocket(sock);
		if (wsa_retVal == SOCKET_ERROR)
		{
			WSACleanup();
			throw communication_error(std::string("Windows Sockets connect error : " + std::to_string(WSAGetLastError())));
		}
		WSACleanup();
	}

	void smtp_client::write_command(const unsigned int sock, const std::string str, const std::string arg, const bool ask_for_reply)
	{
		char buf[4096];

		if (arg != "")
			snprintf(buf, sizeof(buf), str.c_str(), arg.c_str());
		else
			snprintf(buf, sizeof(buf), str.c_str());

		int wsa_retVal = send(sock, buf, strlen(buf), 0);
		if (wsa_retVal == SOCKET_ERROR) {
			std::cout << "send failed: " << WSAGetLastError() << std::endl;
			closesocket(sock);
			WSACleanup();
			throw communication_error(std::string("send command failed : " + std::to_string(WSAGetLastError())));
		}
		if (ask_for_reply)
		{
			// read a reply from server
			char outbuf[1024];
			int len = recv(sock, outbuf, 1024, 0);
			if (len > 0)
			{
				outbuf[len] = '\0';
				this->server_reply += std::string(outbuf);
			}
		}
	}

	const std::string smtp_client::get_server_reply()
	{
		return this->server_reply;
	}
}