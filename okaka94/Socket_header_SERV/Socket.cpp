#define _WINSOCK_DEPRECATED_NO_WARNINGS										// Ignore inet_addr error

#include <WinSock2.h>
#include <iostream>
#include <list>
#include "protocol.h"

struct UserInfo {
	SOCKET		_sock;
	SOCKADDR_IN	_sa;
	char		_name[9] = { 0, };
	char		_recvMsg[255] = { 0, };
	int			_totalRecvBytes = 0;
};
std::list<UserInfo> UserList;

int SendMsg(SOCKET sock, char* msg, short type) {
	PACKET packet;
	ZeroMemory(&packet, sizeof(PACKET));
	if (msg != nullptr) {
		packet._header._len = strlen(msg) + PACKET_HEADER_SIZE;
		memcpy(packet._msg, msg, strlen(msg));
	}
	else {
		packet._header._len = PACKET_HEADER_SIZE;
	}
	packet._header._type = type;

	char* msgBuf = (char*)&packet;
	int sendBytes = send(sock, msgBuf, packet._header._len, 0);
	if (sendBytes == SOCKET_ERROR) {
		if (WSAGetLastError() != WSAEWOULDBLOCK) {
			closesocket(sock);
			return -1;
		}
	}
	return 1;
}

DWORD WINAPI ServerThread(LPVOID IpThreadParam) {

	while(1) {
		for (auto recvIter = UserList.begin(); UserList.end() != recvIter;) {
			int RecvPacketSize = PACKET_HEADER_SIZE;
			// 패킷헤더 단위로 recv하고 헤더 다 받은 뒤에 본문 다시 recv
			int RecvBytes = recv(recvIter->_sock, recvIter->_recvMsg, PACKET_HEADER_SIZE - recvIter->_totalRecvBytes, 0);			
			if (RecvBytes == 0) {
				printf("클라이언트 접속 종료 : IP : %s, PORT : %d\n",
					inet_ntoa(recvIter->_sa.sin_addr), ntohs(recvIter->_sa.sin_port));
				recvIter = UserList.erase(recvIter);
				continue;
			}
			DWORD error = WSAGetLastError();
			if (RecvBytes == SOCKET_ERROR) {
				if (error != WSAEWOULDBLOCK) {
					closesocket(recvIter->_sock);
					recvIter = UserList.erase(recvIter);
				}
				else {
					recvIter++;
				}
				continue;
			}

			PACKET packet;
			ZeroMemory(&packet, sizeof(PACKET));

			recvIter->_totalRecvBytes += RecvBytes;
			if (recvIter->_totalRecvBytes == PACKET_HEADER_SIZE) {
				memcpy(&packet._header, recvIter->_recvMsg, PACKET_HEADER_SIZE);

				char* msg = (char*)&packet;
				int numRecvBytes = 0;
				do {
					int recvBytes = recv(recvIter->_sock, &packet._msg[numRecvBytes], 
										 packet._header._len - PACKET_HEADER_SIZE - numRecvBytes, 0);
					if (recvBytes == 0) {
						printf("서버 정상 종료\n");
						break;
					}
					if (recvBytes == SOCKET_ERROR) {
						if (WSAGetLastError() != WSAEWOULDBLOCK) {
							closesocket(recvIter->_sock);
							printf("서버 비정상 종료\n");
							return 1;
						}
						continue;
					}
					numRecvBytes += recvBytes;
				} while ((packet._header._len - PACKET_HEADER_SIZE) > numRecvBytes);
			}

			if (RecvBytes > 0) {
				switch (packet._header._type) {
				case PACKET_CHAR_MSG: {
					printf("[%s]%s\n", recvIter->_name, packet._msg);
					packet._header._len += strlen(recvIter->_name) + 2;
					std::string msg = "[";
					msg += recvIter->_name;
					msg += "]";
					msg += packet._msg;
					ZeroMemory(packet._msg, 2048);
					memcpy(packet._msg, msg.c_str(), msg.size());
				}break;

				case PACKET_NAME_REQ: {
					memcpy(recvIter->_name, packet._msg, strlen(packet._msg));
					packet._header._type = PACKET_NEW_USER;
					SendMsg(recvIter->_sock, nullptr, PACKET_NAME_ACK);
				}break;
				}
				
				for (auto sendIter = UserList.begin(); UserList.end() != sendIter;) {
					if (packet._header._type == PACKET_NEW_USER) {
						if (recvIter == sendIter) {
							sendIter++;
							continue;
						}
					}
					int sendBytes = send(sendIter->_sock, (char*)&packet, packet._header._len, 0);
					if (sendBytes == SOCKET_ERROR) {
						if (WSAGetLastError() != WSAEWOULDBLOCK) {
							printf("클라이언트 접속 비정상 종료 : IP : %s, PORT : %d\n",
								inet_ntoa(sendIter->_sa.sin_addr), ntohs(sendIter->_sa.sin_port));
							closesocket(sendIter->_sock);
							sendIter = UserList.erase(sendIter);
							continue;
						}
					}
					sendIter++;
				}
				ZeroMemory(&packet, sizeof(PACKET));
				recvIter->_totalRecvBytes = 0;
			}
			recvIter++;
		}
	}
}

int main() {

	WSADATA wsa;

	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {							// STARTUP
		return 0;
	}

	SOCKET listenSock = socket(AF_INET, SOCK_STREAM, 0);					// Create Socket 

	SOCKADDR_IN sa;
	sa.sin_family = AF_INET;
	sa.sin_port = htons(10000);												
	sa.sin_addr.s_addr = htonl(INADDR_ANY);									// INADDR_ANY : to all available interfaces

	int ret = bind(listenSock, (sockaddr*)&sa, sizeof(sa));						// Bind socket
	if (ret == SOCKET_ERROR) {
		return 1;
	}

	ret = listen(listenSock, SOMAXCONN);										// Listen . SOMAXCONN(backlog argument) : Maximum Listen Queue 
	if (ret == SOCKET_ERROR) {
		return 1;
	}

	DWORD ThreadID;
	HANDLE ClientHandle = CreateThread(0, 0, ServerThread, 0, 0, &ThreadID);

	while (1) {

		SOCKADDR_IN client_sa;
		int length = sizeof(client_sa);
		SOCKET client_sock = accept(listenSock, 
							(sockaddr*)&client_sa, &length);					// Accept . return client socket
		if (client_sock == SOCKET_ERROR) {
			closesocket(listenSock);
			WSACleanup();
			return 1;
		}
		printf("클라이언트 접속 : IP : %s, PORT : %d\n",
			inet_ntoa(client_sa.sin_addr), ntohs(client_sa.sin_port));

		u_long Mode = TRUE;
		ioctlsocket(client_sock, FIONBIO, &Mode);

		UserInfo user;
		user._sock = client_sock;
		user._sa = client_sa;

		UserList.push_back(user);
	}

	closesocket(listenSock);													// Close

	WSACleanup();																//CLEANUP
}