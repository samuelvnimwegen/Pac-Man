//
// Created by Samuel on 16/11/2023.
//

#ifndef PAC_MAN_STATEMANAGER_H
#define PAC_MAN_STATEMANAGER_H
#include "State.h"
#include "MenuState.h"
#include "PausedState.h"
class StateManager {
    vector<State*> stack;
public:
    StateManager();

    State* getCurrentState();

    void pop();

    void push();

    void pauze();
};


#endif //PAC_MAN_STATEMANAGER_H
