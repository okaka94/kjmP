#define _WINSOCK_DEPRECATED_NO_WARNINGS										// Ignore inet_addr error

#include <WinSock2.h>
#include <iostream>


DWORD WINAPI SendThread(LPVOID IpThreadParam) {								// Thread Start Routine

	SOCKET sock = (SOCKET)IpThreadParam;
	while (1) {
		char SendMsgBuf[256] = { 0, };
		fgets(SendMsgBuf, 256, stdin);
		SendMsgBuf[strlen(SendMsgBuf) - 1] = 0;
		if (strcmp(SendMsgBuf, "exit") == 0) {
			break;
		}
		int MsgBytes = send(sock, SendMsgBuf, strlen(SendMsgBuf), 0);			
		if (MsgBytes == SOCKET_ERROR) {
			if (WSAGetLastError() != WSAEWOULDBLOCK) {							
				closesocket(sock);
				return 1;
			}								
		}
	}
	closesocket(sock);
}

int main() {

	WSADATA wsa;

	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {							// STARTUP
		return 0;
	}

	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);							// Create Socket 
	
	SOCKADDR_IN sa;															// Dest + Port Struct
	sa.sin_family = AF_INET;
	sa.sin_port = htons(10002);												// little-endian to big-endian

	//error C4996: 'inet_addr': Use inet_pton() or InetPton() instead or define _WINSOCK_DEPRECATED_NO_WARNINGS to disable deprecated API warnings
	sa.sin_addr.s_addr = inet_addr("192.168.0.121");	//("127.0.0.1"); 루프백

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
	
	while (1) {

		Sleep(100);															// Idle time
		char RecvMsgBuf[256] = { 0, };
		int RecvBytes = recv(sock, RecvMsgBuf, 256, 0);						// Receive
		if (RecvBytes == 0) {
			printf("서버 정상 종료\n");
			break;
		}
		if (RecvBytes == SOCKET_ERROR) {
			if (WSAGetLastError() != WSAEWOULDBLOCK) {
				closesocket(sock);
				printf("서버 비정상 종료\n");
				return 1;
			}
			
			continue;
		}
		printf("Recv-->%s\n", RecvMsgBuf);
	}
	
	CloseHandle(ClientHandle);												// Close Handle
	closesocket(sock);														// Close Socket

	WSACleanup();															//CLEANUP
}