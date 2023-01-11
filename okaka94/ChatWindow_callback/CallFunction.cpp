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