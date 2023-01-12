#include "Sample.h"

void Sample::ChatMsg(PACKET& p) {
	std::wstring fmt = L"%s";
	Print(fmt.c_str(), to_mw(p._msg).c_str());
}

void Sample::ChatNameReq(PACKET& p) {
	std::wstring fmt = L"%s";
	Print(fmt.c_str(), L"��ȭ���� �Է����ּ���.");
}

void Sample::NewUser(PACKET& p) {
	std::wstring fmt = L"%s%s";
	Print(fmt.c_str(), to_mw(p._msg).c_str(), L" ���� �����ϼ̽��ϴ�.");
}

void Sample::NameAck(PACKET& p) {
	std::wstring fmt = L"%s%s";
	Print(fmt.c_str(), L"��ȭ�� ���� : ", to_mw(p._msg).c_str());
}