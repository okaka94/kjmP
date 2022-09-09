#pragma once
#include <Windows.h>
#include <map>
#include <vector>
#include <set>
#include <list>
#include <string>
#include <d3d11.h>
#include <d3dcompiler.h>
#include "WICTextureLoader.h"
#include "DDSTextureLoader.h"

#pragma	comment(lib,"DirectXTK.lib")
#pragma	comment(lib,"d3d11.lib")
#pragma	comment(lib,"dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib,"winmm.lib")		 // time

extern HWND g_hWnd;
extern RECT g_rtClient;
extern float g_fGameTimer;
extern float g_fSecPerFrame;

template<class T> class Singleton {
public:
	static T& GetInstance() {
		static T SingleInstance;
		return SingleInstance;
	}
};