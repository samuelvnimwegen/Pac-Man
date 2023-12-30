//
// Created by Samuel on 16/11/2023.
//

#ifndef PAC_MAN_STATEMANAGER_H
#define PAC_MAN_STATEMANAGER_H
#include "State.h"
#include "stack"


class GUI::StateManager {
    std::stack<std::unique_ptr<State>> stack;
public:
    StateManager();

    void update(const key &key);

    void pop();

    stateTag getCurrentTag();

    void push(std::unique_ptr<State> state);

    int getSize();
};


#endif //PAC_MAN_STATEMANAGER_H
