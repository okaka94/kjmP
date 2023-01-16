#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include "Std.h"
#include "protocol.h"

struct User {
	SOCKET		_sock;
	SOCKADDR_IN	_sa;
	char		_name[9] = { 0, };
	char		_msg[255] = { 0, };
	int			_totalRecvBytes = 0;
	bool		_hasLeft = false;
};

class Network
{
public:
	HANDLE			_eventArr[64];
	SOCKET			_socketArr[64];
	std::list<User> _userList;

public:
	User*			FindUser(SOCKET sock);

public:
	bool								_isConnected = false;
	SOCKET								_sock;
	std::list<PACKET>					_recvPacketList;
	std::list<std::pair<SOCKET,PACKET>>	_sendPacketList;
	std::list<PACKET>					_broadcastingPacketList;

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

