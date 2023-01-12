#include "Network.h"

void Network::PacketProcess() {
	for (auto& packet : _recvPacketList) {
		Network::FnIter iter = _fnExecutor.find(packet._header._type);
		if (iter != _fnExecutor.end()) {
			Network::CallFunction call = iter->second;
			call(packet);
		}
	}
	_recvPacketList.clear();
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
	_sendPacketList.push_back(packet);
}

void Network::SendProcess() {
	for (auto& packet : _sendPacketList) {
		char* sendMsg = (char*)&packet;
		int sendBytes = send(_sock, sendMsg, packet._header._len, 0);

		if (sendBytes == SOCKET_ERROR) {
			if (WSAGetLastError() != WSAEWOULDBLOCK) {
				closesocket(_sock);
				break;
			}
		}
	}
	_sendPacketList.clear();
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

	int ret = WSAAsyncSelect(_sock, g_hWnd, NETWORK_MSG , FD_CONNECT | FD_READ | FD_WRITE | FD_CLOSE);
	if (ret == SOCKET_ERROR) {
		return false;
	}

	SOCKADDR_IN sa;
	sa.sin_family = AF_INET;
	sa.sin_addr.s_addr = inet_addr(ip.c_str());
	sa.sin_port = htons(port);
	ret = connect(_sock, (sockaddr*)&sa, sizeof(sa));
	//if (ret == SOCKET_ERROR) {
	//	int error = WSAGetLastError();
	//	printf("%d ", error);
	//	return false;
	//}
	//DWORD threadID;
	//_clientThread = CreateThread(0, 0, RecvThread, (LPVOID)this, 0, &threadID);

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