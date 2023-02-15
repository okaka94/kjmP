#pragma once
#include <WinSock2.h>
#include <windows.h>
#include <map>
#include <vector>
#include <list>
#include <set>
#include <string>
#include <queue>
#include "Vector.h"		 
#include <wrl.h> // windows runtime c++ templace library(wrl)
//문자열 변환 관련
#include <tchar.h>
#include <codecvt>
#include <atlconv.h> 
// lib
#include "TMath.h"

#define CORE
extern HWND g_hWnd;
extern RECT g_rtClient;
extern float g_fGameTimer;
extern float g_fSecPerFrame;

using namespace Microsoft::WRL;

enum SCENE_SWITCH {
	TITLE,
	SELECT,
	INGAME,
	RESULT,
	EXIT,
};


//#define GAME_START int APIENTRY wWinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPWSTR    lpCmdLine,int       nCmdShow){
//#define GAME_WINDOW(s,x,y) Sample demo;demo.SetWindow(hInstance,L#s,x,y);demo.Run();return 1;
//#define GAME_END    }
//#define GAME_RUN(s,x,y)  GAME_START  GAME_WINDOW(s,x,y)  GAME_END

#define randf(x) (x*rand()/(float)RAND_MAX)
#define randf2(x,off) (off+x*rand()/(float)RAND_MAX)
#define randstep(fMin,fMax) (fMin+((float)fMax-(float)fMin)*rand()/(float)RAND_MAX)
#define clamp(x,MinX,MaxX) if (x>MaxX) x=MaxX; else if (x<MinX) x=MinX;

typedef std::basic_string<TCHAR> T_STR;
typedef std::basic_string<wchar_t> W_STR;
typedef std::basic_string<char>  C_STR;
typedef std::vector<std::basic_string<TCHAR>>		TCHAR_STRING_VECTOR;
typedef std::vector<DWORD>					DWORD_VECTOR;

static std::wstring to_mw(const std::string & _src)
{
	if (_src.empty()) return std::wstring();
	int size_needed = MultiByteToWideChar(CP_UTF8, 0, &_src[0], (int)_src.size(), NULL, 0);
	std::wstring wstrTo(size_needed, 0);
	MultiByteToWideChar(CP_UTF8, 0, &_src[0], (int)_src.size(), &wstrTo[0], size_needed);
	return wstrTo;
};

static std::string to_wm(const std::wstring & _src)
{
	if (_src.empty()) return std::string();
	int size_needed = WideCharToMultiByte(CP_UTF8, 0, &_src[0], (int)_src.size(), NULL, 0, NULL, NULL);
	std::string strTo(size_needed, 0);
	WideCharToMultiByte(CP_UTF8, 0, &_src[0], (int)_src.size(), &strTo[0], size_needed, NULL, NULL);
	return strTo;

};
//static std::wstring mtw(std::string str)
//{
//	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> conv;
//	return conv.from_bytes(str);
//}
////#include <codecvt>
//static std::string wtm(std::wstring str)
//{
//	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> conv;
//	return conv.to_bytes(str);
//}
//static char* GetWtM(WCHAR * data)
//{
//	char retData[4096] = { 0 };
//	// 변형되는 문자열의 크기가 반환된다.
//	int iLength = WideCharToMultiByte(CP_ACP, 0,
//		data, -1, 0, 0, NULL, NULL);
//	int iRet = WideCharToMultiByte(CP_ACP, 0,
//		data, -1,  //  소스
//		retData, iLength, // 대상
//		NULL, NULL);
//	return retData;
//}
//static bool GetWtM(WCHAR * src, char* pDest)
//{
//	// 변형되는 문자열의 크기가 반환된다.
//	int iLength = WideCharToMultiByte(CP_ACP, 0,
//		src, -1, 0, 0, NULL, NULL);
//	int iRet = WideCharToMultiByte(CP_ACP, 0,
//		src, -1,  //  소스
//		pDest, iLength, // 대상
//		NULL, NULL);
//	if (iRet == 0) return false;
//	return true;
//}
//static WCHAR* GetMtW(char* data)
//{
//	WCHAR retData[4096] = { 0 };
//	// 변형되는 문자열의 크기가 반환된다.
//	int iLength = MultiByteToWideChar(CP_ACP, 0, data, -1, 0, 0);
//	int iRet = MultiByteToWideChar(CP_ACP, 0,
//		data, -1,  //  소스
//		retData, iLength); // 대상
//	return retData;
//}
//static bool GetMtW(char* pSrc, WCHAR * pDest)
//{
//	// 변형되는 문자열의 크기가 반환된다.
//	int iLength = MultiByteToWideChar(CP_ACP, 0,
//		pSrc, -1, 0, 0);
//	int iRet = MultiByteToWideChar(CP_ACP, 0,
//		pSrc, -1,  //  소스
//		pDest, iLength); // 대상		
//	if (iRet == 0) return false;
//	return true;
//}
static void PRINT(char* fmt, ...) // 나열연산자
{
	va_list arg;
	va_start(arg, fmt);
	char buf[256] = { 0, };
	vsprintf_s(buf, fmt, arg);
	printf("\n=====> %s", buf);
	va_end(arg);
}

template<class T> class Singleton {
public:
	static T& GetInstance() {
		static T SingleInstance;
		return SingleInstance;
	}
};