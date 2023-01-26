#pragma once
#include "CharState.h"

class CharFSM
{
private:
	std::map<DWORD, CharState*> _state;
public:
	void	AddTransition(DWORD inState, DWORD event, DWORD outState);
	DWORD	GetTransition(DWORD state, DWORD event);

	~CharFSM();
};

