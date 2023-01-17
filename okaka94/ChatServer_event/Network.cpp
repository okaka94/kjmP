#include "Network.h"

User* Network::FindUser(SOCKET sock) {

	for (auto recvIter = _userList.begin(); _userList.end() != recvIter; recvIter++) {
		if (sock == recvIter->_sock) {
			return &*(recvIter);
		}
	}
	return nullptr;
}

void Network::PacketProcess() {

	DWORD idx = WSAWaitForMultipleEvents(_userList.size() + 1, _eventArr, FALSE, 0, FALSE);
	if (idx == WSA_WAIT_FAILED) return;		// 실패시 리턴 - WSAGetLasError로 확인 가능
	if (idx == WSA_WAIT_TIMEOUT) return;	// 시간 초과, I/O 완료 루틴 실행 X
	
	idx -= WSA_WAIT_EVENT_0;
	if (idx == 0) {
		WSANETWORKEVENTS netEvent;
		int ret = WSAEnumNetworkEvents(_sock, _eventArr[idx], &netEvent);
		if (ret != SOCKET_ERROR) {
			if (netEvent.lNetworkEvents & FD_ACCEPT) {										// ACCEPT EVENT
				SOCKADDR_IN clientSa;
				int length = sizeof(clientSa);
				SOCKET clientSock = accept(_sock, (sockaddr*)&clientSa, &length);
				if (clientSock == SOCKET_ERROR) {
					closesocket(_sock);
					WSACleanup();
					return;
				}
				printf("클라이언트 접속 : IP : %s, PORT : %d\n",
					inet_ntoa(clientSa.sin_addr), ntohs(clientSa.sin_port));

				u_long mode = TRUE;
				ioctlsocket(clientSock, FIONBIO, &mode);

				User user;
				user._sock = clientSock;
				user._sa = clientSa;
				_userList.push_back(user);

				HANDLE listenEvent = WSACreateEvent();										// Manual Reset Event
				_eventArr[_userList.size()] = listenEvent;
				_socketArr[_userList.size()] = clientSock;
				WSAEventSelect(clientSock, listenEvent, FD_READ | FD_WRITE | FD_CLOSE);
				SendMsg(clientSock, nullptr, 0, PACKET_CHATNAME_REQ);
			}
		}
		return;

	}

	
	for (int event = idx; event < _userList.size() + 1; event++) {
		User* user = FindUser(_socketArr[event]);
		if (user->_hasLeft) continue;
		DWORD signal = WSAWaitForMultipleEvents(1, &_eventArr[event], TRUE, 0, FALSE);

		if (signal == WSA_WAIT_FAILED) continue;
		if (signal == WSA_WAIT_TIMEOUT) continue;

		WSANETWORKEVENTS netEvent;
		int ret = WSAEnumNetworkEvents(user->_sock, _eventArr[idx], &netEvent);
		if (ret != SOCKET_ERROR) {
			PACKET packet;
			ZeroMemory(&packet, sizeof(PACKET));
			if (netEvent.lNetworkEvents & FD_READ) {
				int recvPacketSize = PACKET_HEADER_SIZE;
				int recvBytes = recv(user->_sock, user->_msg, PACKET_HEADER_SIZE - user->_totalRecvBytes, 0);
				if (recvBytes == 0) {
					user->_hasLeft = true;
					continue;
				}
				DWORD error = WSAGetLastError();
				if (recvBytes == SOCKET_ERROR) {
					if (error != WSAEWOULDBLOCK) {
						user->_hasLeft = true;
					}
					continue;
				}

				user->_totalRecvBytes += recvBytes;
				if (user->_totalRecvBytes == PACKET_HEADER_SIZE) {
					memcpy(&packet._header, user->_msg, PACKET_HEADER_SIZE);
					char* msg = (char*)&packet;
					int numRecvBytes = 0;
					do {
						int recvBytes = recv(user->_sock, &packet._msg[numRecvBytes], packet._header._len - PACKET_HEADER_SIZE - numRecvBytes, 0);

						if (recvBytes == 0) {
							user->_hasLeft = true;
							break;
						}
						if (recvBytes == SOCKET_ERROR) {
							if (WSAGetLastError() != WSAEWOULDBLOCK) {
								user->_hasLeft = true;
							}
							continue;
						}
						numRecvBytes += recvBytes;
					} while ((packet._header._len - PACKET_HEADER_SIZE) > numRecvBytes);
				}

				if (recvBytes > 0) {
					if (packet._header._type == PACKET_NAME_REQ) {
						SendMsg(user->_sock, nullptr, 0, PACKET_NAME_ACK);
					}
					else {
						_recvPacketList.push_back(packet);
					}
				}
				user->_totalRecvBytes = 0;
			}
			if (netEvent.lNetworkEvents & FD_WRITE) {

			}
			if (netEvent.lNetworkEvents & FD_CLOSE) {
				user->_hasLeft = true;
			}
		}
	}
	
	for (auto& packet : _recvPacketList) {
		Network::FnIter iter = _fnExecutor.find(packet._header._type);
		if (iter != _fnExecutor.end()) {
			Network::CallFunction call = iter->second;
			call(packet);
		}
	}
	_recvPacketList.clear();

	for (auto userIter = _userList.begin(); _userList.end() != userIter; ) {
		if (userIter->_hasLeft) {
			closesocket(userIter->_sock);
			printf("클라이언트 접속 종료 : IP : %s, PORT : %d\n",
				inet_ntoa(userIter->_sa.sin_addr), ntohs(userIter->_sa.sin_port));
			userIter = _userList.erase(userIter);
		}
		else {
			userIter++;
		}
	}
}

void Network::MakePacket(PACKET& packet, const char* msg, int size, short type) {

	ZeroMemory(&packet, sizeof(PACKET));
	packet._header._len = size + PACKET_HEADER_SIZE;
	packet._header._type = type;
	memcpy(packet._msg, msg, size);
}

void Network::RecvProcess() {
	
	int recvPacketSize = PACKET_HEADER_SIZE;
	int totalRecvBytes = 0;
	while (1) {
		char recvMsg[256] = { 0, };
		int recvBytes = recv(_sock, recvMsg, PACKET_HEADER_SIZE - totalRecvBytes, 0);
		if (recvBytes == 0) {
			printf("서버 정상 종료\n");
			return;
		}
		if (recvBytes == SOCKET_ERROR) {
			DWORD error = WSAGetLastError();
			if (error != WSAEWOULDBLOCK) {
				closesocket(_sock);
			}
			return;
		}
		totalRecvBytes += recvBytes;
		if (totalRecvBytes == PACKET_HEADER_SIZE) {
			PACKET packet;
			ZeroMemory(&packet, sizeof(PACKET));
			memcpy(&packet._header, recvMsg, PACKET_HEADER_SIZE);
			
			char* msg = (char*)&packet;
			int numRecvBytes = 0;
			do {
				if (packet._header._len == 4) {
					break;
				}
				int recvBytes = recv(_sock, &packet._msg[numRecvBytes], packet._header._len - PACKET_HEADER_SIZE - numRecvBytes, 0);

				if (recvBytes == 0) {
					printf("서버 정상 종료\n");
					break;
				}
				if (recvBytes == SOCKET_ERROR) {
					if (WSAGetLastError() != WSAEWOULDBLOCK) {
						closesocket(_sock);
						printf("서버 비정상 종료\n");
						return;
					}
					continue;
				}
				numRecvBytes += recvBytes;
			} while ((packet._header._len - PACKET_HEADER_SIZE) > numRecvBytes);
			_recvPacketList.push_back(packet);
			totalRecvBytes = 0;
			return;
		}
	}
}

void Network::AddSend(SOCKET sock, const char* data, int size, short type) {
	PACKET packet;
	MakePacket(packet, data, size, type);
	_broadcastingPacketList.push_back(packet);
}

void Network::SendProcess() {
	for (auto& packet : _broadcastingPacketList) {
		for (auto sendIter = _userList.begin(); _userList.end() != sendIter; ) {
			int sendBytes = send(sendIter->_sock, (char*)&packet, packet._header._len, 0);

			if (sendBytes == SOCKET_ERROR) {
				if (WSAGetLastError() != WSAEWOULDBLOCK) {
					printf("클라이언트 비정상 종료 : IP : %s , PORT : %d\n",
						inet_ntoa(sendIter->_sa.sin_addr), ntohs(sendIter->_sa.sin_port));
					closesocket(sendIter->_sock);
					sendIter = _userList.erase(sendIter);
					continue;
				}
			}
			sendIter++;
		}		
	}
	_broadcastingPacketList.clear();
}

//DWORD WINAPI RecvThread(LPVOID ThreadParam) {
//	Network* net = (Network*)ThreadParam;
//	SOCKET sock = net->_sock;
//	int recvPacketSize = PACKET_HEADER_SIZE;
//	int totalRecvBytes = 0;
//	while (1) {
//		char recvMsg[256] = { 0, };
//		int recvBytes = recv(net->_sock, recvMsg, PACKET_HEADER_SIZE - totalRecvBytes, 0);
//		if (recvBytes == 0) {
//			printf("서버 정상 종료\n");
//			return true;
//		}
//		totalRecvBytes += recvBytes;
//		if (totalRecvBytes == PACKET_HEADER_SIZE) {
//			PACKET packet;
//			ZeroMemory(&packet, sizeof(PACKET));
//			memcpy(&packet._header, recvMsg, PACKET_HEADER_SIZE);
//
//			char* msg = (char*)&packet;
//			int numRecvBytes = 0;
//			do {
//				if (packet._header._len == PACKET_HEADER_SIZE) {
//					break;
//				}
//				int recvBytes = recv(net->_sock, &packet._msg[numRecvBytes], 
//									 packet._header._len - PACKET_HEADER_SIZE - numRecvBytes, 0);
//
//				if (recvBytes == 0) {
//					printf("서버 정상 종료\n");
//					break;
//				}
//				if (recvBytes == SOCKET_ERROR) {
//					if (WSAGetLastError() != WSAEWOULDBLOCK) {
//						closesocket(net->_sock);
//						printf("서버 비정상 종료\n");
//						return 1;
//					}
//					continue;
//				}
//				numRecvBytes += recvBytes;
//			} while ((packet._header._len - PACKET_HEADER_SIZE) > numRecvBytes);
//
//			net->_packetList.push_back(packet);
//			totalRecvBytes = 0;
//		}
//	}
//	closesocket(sock);
//}

int Network::SendMsg(SOCKET sock, const char* data, int size ,short type) {
	
	PACKET packet;
	MakePacket(packet, data, size, type);

	char* msgSend = (char*)&packet;
	int sendBytes = send(sock, msgSend, packet._header._len, 0);

	if (sendBytes == SOCKET_ERROR) {
		if (WSAGetLastError() != WSAEWOULDBLOCK) {
			closesocket(sock);
			return -1;
		}
	}
	return 1;
}

bool Network::StartNet(std::string ip, int port) {
	_sock = socket(AF_INET, SOCK_STREAM, 0);

	SOCKADDR_IN sa;
	sa.sin_family = AF_INET;
	sa.sin_addr.s_addr = inet_addr(ip.c_str());
	sa.sin_port = htons(port);

	int ret = bind(_sock, (sockaddr*)&sa, sizeof(sa));
	if (ret == SOCKET_ERROR) {
		return 1;
	}
	
	ret = listen(_sock, SOMAXCONN);
	if (ret == SOCKET_ERROR) {
		return 1;
	}
	
	HANDLE listenEvent = WSACreateEvent();
	_eventArr[0] = listenEvent;
	WSAEventSelect(_sock, _eventArr[0], FD_ACCEPT);

	return true;
}

bool Network::Frame()
{
	return true;
}
bool Network::Render()
{
	return true;
}
bool Network::Release()
{
	closesocket(_sock);
	return true;
}
Network::Network()
{
	WSADATA ws;
	WSAStartup(MAKEWORD(2, 2), &ws);
}

Network::~Network()
{
	WSACleanup();
}