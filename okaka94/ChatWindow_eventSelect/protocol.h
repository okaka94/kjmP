#pragma once
#define PACKET_HEADER_SIZE 4

#pragma pack(push,1)
typedef struct {
	short _len;
	short _type;
}PACKET_HEADER;

typedef struct {
	PACKET_HEADER _header;
	char		  _msg[2048];
}PACKET;

typedef struct {
	char _name[9];
}USERNAME_REQ;

typedef struct {
	int _result;					// 1 : 성공 , 0 : 중복 , < 0 : 실패
}USERNAME_ACK;
#pragma pack(pop)

#define PACKET_CHAR_MSG		1000
#define PACKET_CHATNAME_REQ	1001
#define PACKET_NAME_REQ		2000
#define PACKET_NAME_ACK		3000
#define PACKET_NEW_USER		4000