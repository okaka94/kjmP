#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS


#include "Std.h"
#include "protocol.h"



class Network
{
public:
	bool				_isConnected = false;
	SOCKET				_sock;
	HANDLE				_clientThread;
	std::list<PACKET>	_recvPacketList;
	std::list<PACKET>	_sendPacketList;

public:
	typedef std::function<void(PACKET& p)> CallFunction;
	typedef std::map<DWORD, CallFunction>::iterator FnIter;
	std::map<DWORD, CallFunction> _fnExecutor;

public:
	void	PacketProcess();
	void	MakePacket(PACKET& packet, const char* msg, int size , short type);
	void	AddSend(SOCKET sock, const char* msg, int size, short type);
	void	SendProcess();
	void	RecvProcess();

	bool	StartNet(std::string ip, int port);
	int		SendMsg(SOCKET sock, const char* data, int size, short type);
	bool	Frame();
	bool	Render();
	bool	Release();

public:
	Network();
	virtual ~Network();
};

