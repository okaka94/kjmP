#include "Sample.h"

void Sample::Print(const WCHAR* fmt, ...) {													// variable argument
	
	va_list arg;																			// void형 포인터 변수 , va_start 전에 선언
	va_start(arg, fmt);																		// va_start(가변인수, 고정인수) , fmt : 고정인수 (다음 주소가 가변인수)
		WCHAR msg[256] = L"";
		_vsntprintf_s(msg, 256, fmt, arg);													// arg에 있는 fmt 자료형 가변 인수들을 256 크기만큼 msg 버퍼에 채움
		SendMessage(_listBox, LB_ADDSTRING, 0, (LPARAM)msg);								// listbox 핸들에 msg 추가
	va_end(arg);																			// va_end
}
	


LRESULT Sample::MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
		case WM_CREATE: {
			_edit = CreateWindow(L"edit", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER,
				500, 569, 250, 25, hWnd, (HMENU)1000, m_hInstance, NULL);
			_sendBtn = CreateWindow(L"button", L"Send", WS_CHILD | WS_VISIBLE | WS_BORDER | BS_PUSHBUTTON,
				750, 569, 50, 25, hWnd, (HMENU)1001, m_hInstance, NULL);
			_listBox = CreateWindow(L"listbox", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | WS_HSCROLL | WS_VSCROLL,
				0, 0, 500, 609, hWnd, (HMENU)1002, m_hInstance, NULL);
			std::wstring fmt = L"%s";
			Print(fmt.c_str(), L"대화 시작");
		}break;

		case WM_COMMAND: {
			switch (LOWORD(wParam)) {
				case 1001: {																	// send btn
					WCHAR buffer[255] = L"";
					GetWindowText(_edit, buffer, 255);
					OutputDebugString(buffer);
					if (_isEntered == false) {
						_net.SendMsg(_net._sock, to_wm(buffer).c_str(), PACKET_NAME_REQ);
						_isEntered = true;
					}
					else {
						_net.SendMsg(_net._sock, to_wm(buffer).c_str(), PACKET_CHAR_MSG);
					}
				}break;
			}
		}break;
		case WM_DESTROY: {
			PostQuitMessage(0);
			break;
		}
	 
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}

bool Sample::Run() {
	Init();
	while (m_game_run) {
		if (Window::Run() == true) {
			Frame();
			Render();
		}
		else {
			m_game_run = false;
		}
	}
	Release();
	return true;
}

bool Sample::Init() {

	std::wstring fmt = L"IP[%s] : PORT[%d] %s";

	std::string ip = "127.0.0.1";
	short port = 10000;
	
	if (_net.StartNet(ip, port)) { //192.168.0.45", 10000)) {
		Print(fmt.c_str(), to_mw(ip).c_str(), port, L"접속 성공");
	}
	else {
		Print(fmt.c_str(), to_mw(ip).c_str(), port, L"접속 실패");
	}

	return true;
}

void Sample::NetProcess() {
	for (auto& packet : _net._packetList) {
		switch (packet._header._type) {
			case PACKET_CHAR_MSG: {
				std::wstring fmt = L"%s";
				Print(fmt.c_str(), to_mw(packet._msg).c_str());
			}break;

			case PACKET_CHATNAME_REQ: {
				std::wstring fmt = L"%s";
				Print(fmt.c_str(), L"대화명을 입력해주세요.");
			}break;

			case PACKET_NEW_USER: {
				std::wstring fmt = L"%s%s";
				Print(fmt.c_str(), to_mw(packet._msg).c_str(), L" 님이 입장하셨습니다.");
			}break;

			case PACKET_NAME_ACK: {
				std::wstring fmt = L"%s%s";
				Print(fmt.c_str(), L"대화방 입장 : ", to_mw(packet._msg).c_str());
			}break;
		}
	}
	_net._packetList.clear();																		// Packet List Clear하는 이유?
}

bool Sample::Frame() {

	_net.Frame();
	NetProcess();
	return true;
}

bool Sample::Render() {

	_net.Render();
	return true;
}

bool Sample::Release() {

	_net.Release();
	return true;
}

int APIENTRY wWinMain(HINSTANCE hinstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow) {

	Sample demo;
	demo.SetWindow(hinstance, L"SocketWin", 800, 600);

	demo.Run();

	return 1;
}