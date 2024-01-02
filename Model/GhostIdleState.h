//
// Created by Samuel on 26/12/2023.
//

#ifndef PAC_MAN_GHOSTIDLESTATE_H
#define PAC_MAN_GHOSTIDLESTATE_H
#include "GhostState.h"
#include "Ghost.h"
#include "Stopwatch.h"
#include "GhostChasingState.h"
#include "GhostFrightenedState.h"

class Model::GhostIdleState: public Model::GhostState{
public:
    GhostIdleState(const std::weak_ptr<Model::GhostStateManager> &stateManager,
                   const std::weak_ptr<Model::Ghost> &ghost);

    void update() override;
};


#endif //PAC_MAN_GHOSTIDLESTATE_H
