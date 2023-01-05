#define _WINSOCK_DEPRECATED_NO_WARNINGS										// Ignore inet_addr error

#include <WinSock2.h>
#include <iostream>

#define SERVER_CODE
#ifndef SERVER_CODE

DWORD WINAPI SendThread(LPVOID IpThreadParam) {								// Thread Start Routine

	SOCKET sock = (SOCKET)IpThreadParam;
	while (1) {
		char SendMsgBuf[256] = { 0, };
		fgets(SendMsgBuf, 256, stdin);

		int MsgBytes = send(sock, SendMsgBuf, strlen(SendMsgBuf), 0);			
		if (MsgBytes == SOCKET_ERROR) {
			if (WSAGetLastError() != WSAEWOULDBLOCK) {							
				closesocket(sock);
				return 1;
			}								
		}
	}
}

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
		int error = WSAGetLastError();
		printf("%d\n", error);
		return 1;
	}

	DWORD ThreadID;
	HANDLE ClientHandle = CreateThread(0, 0, SendThread,					// Handle
							(LPVOID)sock, 0, &ThreadID);					// Create Thread
	
	u_long mode = TRUE;														// True : Non-block , False : Block
	ioctlsocket(sock, FIONBIO, &mode);										// Control Socket. set non-block mode
	int count = 0;
	while (1) {

		Sleep(100);															// Idle time
		char RecvMsgBuf[256] = { 0, };
		int RecvBytes = recv(sock, RecvMsgBuf, 256, 0);						// Receive
		if (RecvBytes == SOCKET_ERROR) {
			if (WSAGetLastError() != WSAEWOULDBLOCK) {
				closesocket(sock);
				return 1;
			}
			printf("Recv-->%d\n", count++);
			continue;
		}
		printf("Recv-->%s\n", RecvMsgBuf);
	}
	
	CloseHandle(ClientHandle);												// Close Handle
	closesocket(sock);														// Close Socket

	WSACleanup();															//CLEANUP
}
#else

DWORD WINAPI ServerThread(LPVOID IpThreadParam) {
	SOCKET sock = (SOCKET)IpThreadParam;

	while(1) {
		char RecvMsgBuf[256] = { 0, };
		int RecvBytes = recv(sock, RecvMsgBuf, 256, 0);								// Receive
		if (RecvBytes == 0) {														// recv() returns 0 : Client disconnects
			closesocket(sock);
			break;
		}
		if (RecvBytes == SOCKET_ERROR) {
			if (WSAGetLastError() != WSAEWOULDBLOCK) {
				closesocket(sock);
				return 1;
			}
		}
		else {
			printf("%d\n", RecvMsgBuf);
		}

		
		if (RecvBytes > 0) {
			int SendBytes = send(sock, RecvMsgBuf, strlen(RecvMsgBuf), 0);			// Send
			if (SendBytes == SOCKET_ERROR) {
				if (WSAGetLastError() != WSAEWOULDBLOCK) {
					closesocket(sock);
					break;
				}
			}
		}
	}
}

int main() {

	WSADATA wsa;

	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {								// STARTUP
		return 0;
	}

	SOCKET ListenSock = socket(AF_INET, SOCK_STREAM, 0);						// Create Socket 

	SOCKADDR_IN sa;
	sa.sin_family = AF_INET;
	sa.sin_port = htons(10000);												
	sa.sin_addr.s_addr = htonl(INADDR_ANY);										// INADDR_ANY : to all available interfaces

	int ret = bind(ListenSock, (sockaddr*)&sa, sizeof(sa));						// Bind socket
	if (ret == SOCKET_ERROR) {
		return 1;
	}

	ret = listen(ListenSock, SOMAXCONN);										// Listen . SOMAXCONN(backlog argument) : Maximum Listen Queue 
	if (ret == SOCKET_ERROR) {
		return 1;
	}

	while (1) {

		SOCKADDR_IN client_sa;
		int length = sizeof(client_sa);
		SOCKET client_sock = accept(ListenSock, 
							(sockaddr*)&client_sa, &length);					// Accept . return client socket
		if (client_sock == SOCKET_ERROR) {
			closesocket(ListenSock);
			WSACleanup();
			return 1;
		}
		printf("클라이언트 접속 : IP : %s , PORT %d\n",
			inet_ntoa(client_sa.sin_addr),										// inet_ntoa() : ip address to string(ASCII)
			ntohs(client_sa.sin_port));											// ntohs() : big-endian to little-endian
		DWORD ThreadID;
		HANDLE ClientHandle = CreateThread(0, 0, ServerThread, 
											(LPVOID)client_sock, 0, &ThreadID);
	}

	closesocket(ListenSock);													// Close

	WSACleanup();																//CLEANUP
}
#endif