#define _WINSOCK_DEPRECATED_NO_WARNINGS										// Ignore inet_addr error

#include <WinSock2.h>
#include <iostream>

#define SERVER_CODE
#ifndef SERVER_CODE
int main() {

	WSADATA wsa;

	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {							// STARTUP
		return 0;
	}

	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);							// Create Socket 
	
	SOCKADDR_IN sa;															// Dest + Port Struct
	sa.sin_family = AF_INET;
	sa.sin_port = htons(10000);												// little-endian to big-endian

	//error C4996: 'inet_addr': Use inet_pton() or InetPton() instead or define _WINSOCK_DEPRECATED_NO_WARNINGS to disable deprecated API warnings
	sa.sin_addr.s_addr = inet_addr("192.168.0.107");	//("127.0.0.1"); 루프백

	int ret = connect(sock, (sockaddr*)&sa, sizeof(sa));					// Connect socket
	if (ret == SOCKET_ERROR) {
		return 1;
	}
	while (1) {
	char SendMsgBuf[256] = { 0, };
	fgets(SendMsgBuf, 256, stdin);

	int MsgBytes = send(sock, SendMsgBuf, strlen(SendMsgBuf), 0);			// Send

	char RecvMsgBuf[256] = { 0, };
	int RecvBytes = recv(sock, RecvMsgBuf, 256, 0);							// Receive
	printf("%s\n", RecvMsgBuf);
	}

	closesocket(sock);														// Close

	WSACleanup();			//CLEANUP
}
#else
int main() {

	WSADATA wsa;

	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {							// STARTUP
		return 0;
	}

	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);							// Create Socket 

	SOCKADDR_IN sa;
	sa.sin_family = AF_INET;
	sa.sin_port = htons(10000);												
	sa.sin_addr.s_addr = htonl(INADDR_ANY);									// INADDR_ANY : to all available interfaces

	int ret = bind(sock, (sockaddr*)&sa, sizeof(sa));						// Bind socket
	if (ret == SOCKET_ERROR) {
		return 1;
	}

	ret = listen(sock, SOMAXCONN);											// Listen . SOMAXCONN(backlog argument) : Maximum Listen Queue 
	if (ret == SOCKET_ERROR) {
		return 1;
	}

	SOCKADDR_IN client_sa;
	int length = sizeof(client_sa);
	SOCKET client_sock = accept(sock, (sockaddr*)&client_sa, &length);		// Accept . return client socket

	printf("클라이언트 접속 : IP : %s , PORT %d\n", 
		inet_ntoa(client_sa.sin_addr),										// inet_ntoa() : ip address to string(ASCII)
		ntohs(client_sa.sin_port));											// ntohs() : big-endian to little-endian
		
	while (1) {

	char RecvMsgBuf[256] = { 0, };
	int RecvBytes = recv(client_sock, RecvMsgBuf, 256, 0);							// Receive
	printf("%s\n", RecvMsgBuf);

	char SendMsgBuf[256] = { 0, };
	fgets(SendMsgBuf, 256, stdin);

	int MsgBytes = send(client_sock, SendMsgBuf, strlen(SendMsgBuf), 0);			// Send

	}
	closesocket(sock);														// Close

	WSACleanup();			//CLEANUP
}
#endif