#pragma once
#include "Game_core.h"

class Sample : public Game_core
{
public:
	bool	Run() override;
	LRESULT	MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override;
	bool	Init() override;
	bool	Frame() override;
	bool	Render() override;
	bool	Release() override;
	void	ClearD3D11DeviceContext(ID3D11DeviceContext* pd3dDeviceContext);
};

