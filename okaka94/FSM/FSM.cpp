#include <iostream>
#include "CharFSM.h"
#include "NPC.h"


int main()
{
    CharFSM FSM;
    FSM.AddTransition(STATE_STAND, EVENT_POINTMOVE, STATE_MOVE);
    FSM.AddTransition(STATE_STAND, EVENT_FINDTARGET, STATE_ATTACK);
    FSM.AddTransition(STATE_MOVE, EVENT_STOP, STATE_STAND);
    FSM.AddTransition(STATE_ATTACK, EVENT_LOSTTARGET, STATE_STAND);
    
    Player player;
    NPC npc(&FSM);
    while (1) {
        npc.Process(&player);
        Sleep(1000);
    }
}
