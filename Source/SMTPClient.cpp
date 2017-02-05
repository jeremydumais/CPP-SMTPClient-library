#include "..\include\SMTPClient.h"
#include <WinSock2.h>
#include <ws2tcpip.h>
#include <stdexcept>
#include <iostream>
#include <sstream>

using namespace std;

namespace jed_utils
{
	smtp_client::smtp_client(const char *server_name, const unsigned int port)
	{
		this->server_name = new char[strlen(server_name) + 1];
		strcpy_s(this->server_name, strlen(server_name) + 1, server_name);

		this->port = port;
		server_reply = NULL;
	}

	smtp_client::~smtp_client()
	{
		delete server_name;
		if (server_reply != NULL)
			delete server_reply;
	}

	void smtp_client::send_mail(message *msg)
	{
		DWORD dwRetval;
		struct addrinfo *result = NULL;
		struct addrinfo hints; 
		unsigned int sock = 0;
		WSADATA wsaData;

		if (server_reply != NULL)
		{
			delete server_reply;
			server_reply = NULL;
		}

		ostringstream body_ss;
		body_ss << "--sep\r\nContent-Type: " << msg->get_mimetype() << "; charset=UTF-8\r\n\r\n" << msg->get_body() << "\r\n";
		string body_real = body_ss.str();

		//If there's attachments, prepare the attachments text content
		if (msg->get_attachments_ptr() && msg->get_attachments_count() > 0)
		{
			string attachments_text = create_attachments_text(msg->get_attachments_ptr(), msg->get_attachments_count());
			body_real += attachments_text;
		}

		/* Windows Sockets version */
		WORD wVersionRequested = MAKEWORD(2, 2);
		int wsa_retVal = WSAStartup(wVersionRequested, &wsaData);
		if (wsa_retVal != 0)
		{
			ostringstream error_stream;
			error_stream << "Windows Sockets startup error : " << wsa_retVal;
			throw communication_error(error_stream.str().c_str());
		}

		memset(&hints, 0, sizeof hints);
		hints.ai_family = AF_UNSPEC;  // use IPv4 or IPv6, whichever
		hints.ai_socktype = SOCK_STREAM;

		dwRetval = getaddrinfo(this->server_name, "25", &hints, &result);
		if (dwRetval != 0) 
		{
			WSACleanup();
			ostringstream error_stream;
			error_stream << "Windows Sockets getaddrinfo error : " << dwRetval;
			throw communication_error(error_stream.str().c_str());
		}

		sock = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
		wsa_retVal = connect(sock, result->ai_addr, result->ai_addrlen);
		if (wsa_retVal == SOCKET_ERROR) 
		{
			WSACleanup();
			ostringstream error_stream;
			error_stream << "Windows Sockets connect error : " << WSAGetLastError();
			throw communication_error(error_stream.str().c_str());
		}

		write_command(sock, "HELO %s\r\n", msg->get_from().get_email_address());    
		write_command(sock, "MAIL FROM: %s\r\n", msg->get_from().get_email_address());
		//Send command for the recepients
		for (unsigned int index=0; index < msg->get_to_count(); index++)
			write_command(sock, "RCPT TO: %s\r\n", (msg->get_to_ptr() + index)->get_email_address()); 
		// Data section
		write_command(sock, "DATA\r\n", "");
		// Mail headers
		write_command(sock, "From: %s\r\n", msg->get_from());
		for (unsigned int index = 0; index < msg->get_to_count(); index++)
			write_command(sock, "To: %s\r\n", *(msg->get_to_ptr() + index), false);
		write_command(sock, "Subject: %s\r\n", msg->get_subject(), false);
		write_command(sock, "MIME-Version: 1.0\r\n", "", false);
		write_command(sock, "Content-Type: multipart/mixed; boundary=sep\r\n", "", false);
		write_command(sock, "\r\n", "", false);
		// Body part
		if (body_real.length() > 512)
		{
			//Split into chunk
			for (unsigned int index_start = 0; index_start < body_real.length(); index_start += 512)
			{
				int length = 512;
				if (index_start + 512 > body_real.length() - 1)
					length = body_real.length() - index_start;
				write_command(sock, body_real.substr(index_start, length), "", false);
			}
		}
		else
			write_command(sock, "%s", body_real, false);
		write_command(sock, "\r\n", "", false);
		//End of data
		write_command(sock, ".\r\n", "", false); 
		write_command(sock, "QUIT\r\n", "", false);

		wsa_retVal = closesocket(sock);
		if (wsa_retVal == SOCKET_ERROR)
		{
			WSACleanup();
			ostringstream error_stream;
			error_stream << "Windows Sockets connect error : " << WSAGetLastError();
			throw communication_error(error_stream.str().c_str());
		}
		WSACleanup();
	}

	void smtp_client::write_command(const unsigned int sock, const string str, const string arg, const bool ask_for_reply)
	{
		char buf[4096];

		if (arg != "")
			snprintf(buf, sizeof(buf), str.c_str(), arg.c_str());
		else
			snprintf(buf, sizeof(buf), str.c_str());


		int wsa_retVal = send(sock, buf, strlen(buf), 0);
		if (wsa_retVal == SOCKET_ERROR) {
			cout << "send failed: " << WSAGetLastError() << endl;
			closesocket(sock);
			WSACleanup();
			ostringstream error_stream;
			error_stream << "send command failed : " << WSAGetLastError();
			throw communication_error(error_stream.str().c_str());
		}
		if (ask_for_reply)
		{
			// read a reply from server
			char outbuf[1024];
			int len = recv(sock, outbuf, 1024, 0);
			if (len > 0)
			{
				outbuf[len] = '\0';
				if (server_reply == NULL)
				{
					server_reply = new char[strlen(outbuf) + 1];
					strcpy_s(this->server_reply, strlen(outbuf) + 1, outbuf);
				}
				else
				{
					unsigned int size_new_buf = strlen(server_reply) + strlen(outbuf) + 1;
					char *server_reply_temp = new char[size_new_buf];
					strcpy_s(server_reply_temp, strlen(server_reply) + 1, server_reply);
					delete server_reply;
					server_reply = server_reply_temp;
					strcat_s(this->server_reply, size_new_buf, outbuf);
				}
				
			}
		}
	}

	const char *smtp_client::get_server_reply() const
	{
		return this->server_reply;
	}

	string smtp_client::create_attachments_text(const attachment *attachments, const unsigned int attachements_count)
	{
		string retval = "";	
		for (unsigned int index=0; index < attachements_count; index++)
		{
			retval += "\r\n--sep\r\n";
			retval += "Content-Type: " + string((*(attachments + index)).get_mime_type()) + "; file=\"" + string((*(attachments + index)).get_name()) + "\"\r\n";
			retval += "Content-Disposition: Inline; filename=\"" + string((*(attachments + index)).get_name()) + "\"\r\n";
			retval += "Content-Transfer-Encoding: base64\r\n\r\n";
			const char *base64_file = attachments[index].get_base64_encoded_file();
			retval += string(base64_file);
			delete base64_file;

		}
		retval += "\r\n--sep--";
		return retval;
	}
}