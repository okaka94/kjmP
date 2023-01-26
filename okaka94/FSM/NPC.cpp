#include "NPC.h"

void StandState::Process(Player* player) {
	std::cout << "Stand State\n";
	if (rand() % 2 == 0) {
		_owner->SetTransition(EVENT_POINTMOVE);
	}
	if (rand() % 2 == 1) {
		_owner->SetTransition(EVENT_FINDTARGET);
	}
}

void MoveState::Process(Player* player) {
	std::cout << "Move State\n";
	if (rand() % 100 < 5) {
		_owner->SetTransition(EVENT_STOP);
	}
}

void AttackState::Process(Player* player) {
	std::cout << "Attack State\n";
	if (rand() % 100 < 5) {
		_owner->SetTransition(EVENT_LOSTTARGET);
	}
}

NPC::NPC(CharFSM* FSM) {
	_FSM = FSM;
	_actionList.push_back(new StandState(this));
	_actionList.push_back(new MoveState(this));
	_actionList.push_back(new AttackState(this));
	_currentState = _actionList[0];
	_charState = STATE_STAND;
}

void NPC::Process(Player* player) {
	_currentState->Process(player);
}

void NPC::SetTransition(DWORD event) {
	DWORD outState = _FSM->GetTransition(_charState, event);
	_currentState = _actionList[outState];
}

NPC::~NPC() {
	for (auto list : _actionList) {
		delete list;
	}
	_actionList.clear();
}