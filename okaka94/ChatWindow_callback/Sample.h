#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "Game_core.h"
#include "Network.h"

class Sample : public Game_core
{
	Network _net;
	HWND	_edit;
	HWND	_listBox;
	HWND	_sendBtn;
	bool	_isEntered = false;

public:
	void	ChatMsg(PACKET& p);
	void	ChatNameReq(PACKET& p);
	void	NewUser(PACKET& p);
	void	NameAck(PACKET& p);

public:
	// preprocess , postprocess , preframe, postrender »Æ¿Œ
	void	Print(const WCHAR* msg, ...);
	void	NetProcess();
	bool	Run() override;
	LRESULT	MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override;
	bool	Init() override;
	bool	Frame() override;
	bool	Render() override;
	bool	Release() override;
	void	ClearD3D11DeviceContext(ID3D11DeviceContext* pd3dDeviceContext);
};

