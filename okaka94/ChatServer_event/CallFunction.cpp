#include "Sample.h"

void Sample::ChatMsg(PACKET& p) {
	std::wstring fmt = L"%s";
	Print(fmt.c_str(), to_mw(p._msg).c_str());

	_net._broadcastingPacketList.push_back(p);
}

void Sample::ChatNameReq(PACKET& p) {
	std::wstring fmt = L"%s";
	Print(fmt.c_str(), L"대화명을 입력해주세요.");

	PACKET packet;
	_net.MakePacket(packet, nullptr, 0, PACKET_NEW_USER);
	_net._broadcastingPacketList.push_back(packet);
}

//void Sample::NewUser(PACKET& p) {
//	std::wstring fmt = L"%s%s";
//	Print(fmt.c_str(), to_mw(p._msg).c_str(), L" 님이 입장하셨습니다.");
//}
//
//void Sample::NameAck(PACKET& p) {
//	std::wstring fmt = L"%s%s";
//	Print(fmt.c_str(), L"대화방 입장 : ", to_mw(p._msg).c_str());
//}