//
// Created by Samuel on 16/11/2023.
//

#ifndef PAC_MAN_STATEMANAGER_H
#define PAC_MAN_STATEMANAGER_H
#include "State.h"
#include "MenuState.h"
#include "PausedState.h"
#include "stack"
class GUI::StateManager {
    std::stack<shared_ptr<State>> stack;
public:
    StateManager();

    std::shared_ptr<GUI::State> getCurrentState();

    void pop();

    void push();

    void pauze();
};


#endif //PAC_MAN_STATEMANAGER_H
