#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "Std.h"
#include "protocol.h"

class Network
{
public:
	SOCKET				_sock;
	HANDLE				_clientThread;
	std::list<PACKET>	_packetList;

public:
	bool	StartNet(std::string ip, int port);
	int		SendMsg(SOCKET sock, const char* msg, short type);
	bool	Frame();
	bool	Render();
	bool	Release();

public:
	Network();
	virtual ~Network();
};

