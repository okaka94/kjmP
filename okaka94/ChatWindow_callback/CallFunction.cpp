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