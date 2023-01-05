#define _WINSOCK_DEPRECATED_NO_WARNINGS										// Ignore inet_addr error

#include <WinSock2.h>
#include <iostream>
#include <list>

struct UserInfo {
	SOCKET _sock;
	SOCKADDR_IN _sa;
};
std::list<UserInfo> UserList;

DWORD WINAPI ServerThread(LPVOID IpThreadParam) {
	SOCKET sock = (SOCKET)IpThreadParam;

	while(1) {
		for (auto RecvIter = UserList.begin(); UserList.end() != RecvIter;) {
			char RecvMsgBuf[256] = { 0, }; 
			int RecvBytes = recv(RecvIter->_sock, RecvMsgBuf, 256, 0);
			if (RecvBytes == 0) {
				printf("클라이언트 접속 종료 : IP : %s, PORT : %d\n",
					inet_ntoa(RecvIter->_sa.sin_addr), ntohs(RecvIter->_sa.sin_port));
				RecvIter = UserList.erase(RecvIter);
				continue;
			}
			if (RecvBytes == SOCKET_ERROR) {
				if (WSAGetLastError() != WSAEWOULDBLOCK) {
					closesocket(RecvIter->_sock);
					RecvIter = UserList.erase(RecvIter);
					continue;
				}
			}
			if (RecvBytes > 0) {
				printf("%s\n", RecvMsgBuf);
				for (auto SendIter = UserList.begin(); UserList.end() != SendIter;) {
					//////////// 여기서부터 다시
				}

				//int SendBytes = send(sock, RecvMsgBuf, strlen(RecvMsgBuf), 0);			// Send
				//if (SendBytes == SOCKET_ERROR) {
				//if (WSAGetLastError() != WSAEWOULDBLOCK) {
				//	closesocket(sock);
				//	break;
				}
			}

		}
		//
		//
		//		
		//	printf("클라이언트 접속 종료 : IP : %s , PORT %d\n",
					
		//	closesocket(sock);
		//	
		//	break;
		//}
		//
		//	if (WSAGetLastError() != WSAEWOULDBLOCK) {
		//		closesocket(sock);
		//		return 1;
		//	}
		//}
		//else {
		//	printf("%d\n", RecvMsgBuf);
		//}

		//
		//if (RecvBytes > 0) {
		//	
		//	}
		//}
	}
}

int main() {

	WSADATA wsa;

	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {							// STARTUP
		return 0;
	}

	SOCKET ListenSock = socket(AF_INET, SOCK_STREAM, 0);					// Create Socket 

	SOCKADDR_IN sa;
	sa.sin_family = AF_INET;
	sa.sin_port = htons(10000);												
	sa.sin_addr.s_addr = htonl(INADDR_ANY);									// INADDR_ANY : to all available interfaces

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
		
		DWORD ThreadID;
		HANDLE ClientHandle = CreateThread(0, 0, ServerThread, 
											(LPVOID)client_sock, 0, &ThreadID);
	}

	closesocket(ListenSock);													// Close

	WSACleanup();																//CLEANUP
}