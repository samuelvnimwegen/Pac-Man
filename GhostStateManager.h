//
// Created by Samuel on 26/12/2023.
//

#ifndef PAC_MAN_GHOSTSTATEMANAGER_H
#define PAC_MAN_GHOSTSTATEMANAGER_H
#include "Subject.h"
#include "stack"
#include "GhostState.h"

class Model::GhostStateManager{
    std::stack<std::shared_ptr<Model::GhostState>> stack;

public:
    GhostStateManager();

    std::shared_ptr<Model::GhostState> getCurrentState();

    void pop();

    void push();
};


#endif //PAC_MAN_GHOSTSTATEMANAGER_H
