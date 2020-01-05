#pragma once

//Init Session error codes
#define SOCKET_INIT_SESSION_CREATION_ERROR              (-1)
#define SOCKET_INIT_SESSION_CONNECT_ERROR               (-2)
#define SOCKET_INIT_SESSION_CONNECT_TIMEOUT             (-3)
#define SOCKET_INIT_SESSION_WINSOCKET_STARTUP_ERROR     (-4)
#define SOCKET_INIT_SESSION_WINSOCKET_GETADDRINFO_ERROR (-5)

//Init Client error codes
#define SOCKET_INIT_CLIENT_SEND_EHLO_ERROR              (-6)
#define SOCKET_INIT_CLIENT_SEND_EHLO_TIMEOUT            (-7)

//Init TLS error codes
#define SOCKET_INIT_CLIENT_SEND_STARTTLS_ERROR          (-8)
#define SOCKET_INIT_CLIENT_SEND_STARTTLS_TIMEOUT        (-9)