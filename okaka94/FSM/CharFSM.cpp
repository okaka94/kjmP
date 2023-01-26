#include "CharFSM.h"

void CharFSM::AddTransition(DWORD inState, DWORD event, DWORD outState) {
	CharState* state = nullptr;
	auto ret = _state.find(inState);
	if (ret != _state.end()) {
		state = ret->second;
	}
	else {
		state = new CharState();
		_state[inState] = state;
	}
	state->AddTransition(event, outState);
}

DWORD CharFSM::GetTransition(DWORD state, DWORD event) {
	return _state[state]->GetState(event);
}

CharFSM::~CharFSM() {
	for (auto list : _state) {
		delete list.second;
	}
	_state.clear();
}