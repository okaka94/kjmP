#pragma once
#include <Windows.h>
#include <map>

enum CHAR_STATE {
	STATE_STAND = 0,
	STATE_MOVE,
	STATE_ATTACK,
	STATE_COUNT,				// state의 수 counter
};

enum CHAR_EVENT {
	EVENT_STOP = 0,
	EVENT_POINTMOVE,
	EVENT_FINDTARGET,
	EVENT_LOSTTARGET,
	EVENT_COUNT,				// event의 수 counter
};

class CharState
{
public:
	//		 event, state
	std::map<DWORD, DWORD> _eventStateMap;

public:
	void	AddTransition(DWORD event, DWORD state) {
		_eventStateMap[event] = state;
	}
	DWORD	GetState(DWORD event) {
		return _eventStateMap[event];
	}
};

