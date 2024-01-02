//
// Created by Samuel on 26/12/2023.
//

#ifndef PAC_MAN_GHOSTSTATEMANAGER_H
#define PAC_MAN_GHOSTSTATEMANAGER_H
#include "Subject.h"
#include "stack"
#include "GhostState.h"

class Model::GhostStateManager{
    std::stack<std::unique_ptr<Model::GhostState>> stack;
public:
    GhostStateManager();

    void update();

    void pop();

    void push(std::unique_ptr<Model::GhostState>);
    /*
     * Maakt stack weer size 1 met alleen idle state er op
     */
    void reset();

    ghostStateTag getCurrentTag();
};


#endif //PAC_MAN_GHOSTSTATEMANAGER_H
