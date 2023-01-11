#include "Sample.h"

void Sample::Print(const WCHAR* fmt, ...) {													// variable argument
	
	va_list arg;																			// void�� ������ ���� , va_start ���� ����
	va_start(arg, fmt);																		// va_start(�����μ�, �����μ�) , fmt : �����μ� (���� �ּҰ� �����μ�)
		WCHAR msg[256] = L"";
		_vsntprintf_s(msg, 256, fmt, arg);													// arg�� �ִ� fmt �ڷ��� ���� �μ����� 256 ũ�⸸ŭ msg ���ۿ� ä��
		SendMessage(_listBox, LB_ADDSTRING, 0, (LPARAM)msg);								// listbox �ڵ鿡 msg �߰�
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
			Print(fmt.c_str(), L"��ȭ ����");
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
		Print(fmt.c_str(), to_mw(ip).c_str(), port, L"���� ����");
	}
	else {
		Print(fmt.c_str(), to_mw(ip).c_str(), port, L"���� ����");
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
				Print(fmt.c_str(), L"��ȭ���� �Է����ּ���.");
			}break;

			case PACKET_NEW_USER: {
				std::wstring fmt = L"%s%s";
				Print(fmt.c_str(), to_mw(packet._msg).c_str(), L" ���� �����ϼ̽��ϴ�.");
			}break;

			case PACKET_NAME_ACK: {
				std::wstring fmt = L"%s%s";
				Print(fmt.c_str(), L"��ȭ�� ���� : ", to_mw(packet._msg).c_str());
			}break;
		}
	}
	_net._packetList.clear();																		// Packet List Clear�ϴ� ����?
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