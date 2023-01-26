#pragma once
#include <Windows.h>
#include <vector>
#include <iostream>
#include "CharFSM.h"

class Player{
public:
	float m_Pos[2];
	Player() {
		m_Pos[0] = 100;
		m_Pos[1] = 100;
	}
};



class NPC;

class NPCState {
public:
	NPC* _owner = nullptr;
public:
	virtual void Process(Player* player) = 0;
	NPCState() = delete;
	NPCState(NPC* npc) {
		_owner = npc;
	}
};

class StandState : public NPCState {
public:
	virtual void Process(Player* player);
	StandState() = delete;
	StandState(NPC* npc) : NPCState(npc) {
	}
};

class MoveState : public NPCState {
public:
	virtual void Process(Player* player);
	MoveState() = delete;
	MoveState(NPC* npc) : NPCState(npc) {
	}
};

class AttackState : public NPCState {
public:
	virtual void Process(Player* player);
	AttackState() = delete;
	AttackState(NPC* npc) : NPCState(npc) {
	}
};

class NPC {
	DWORD	 _charState;
	CharFSM* _FSM = nullptr;
public:
	NPCState* _currentState = nullptr;
	std::vector<NPCState*> _actionList;
	void Process(Player* player);
	void SetTransition(DWORD event);
public:
	NPC(CharFSM* FSM);
	virtual ~NPC();
};