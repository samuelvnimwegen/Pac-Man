//
// Created by Samuel on 26/12/2023.
//

#include "GhostChasingState.h"
#include "GhostFrightenedState.h"

Model::GhostChasingState::GhostChasingState(const std::weak_ptr<Model::GhostStateManager> &stateManager,
                                            const std::weak_ptr<Model::Ghost> &ghost) : GhostState(stateManager,
                                                                                                   ghost) {
    tag = ghostStateTag::chasing;
}

void Model::GhostChasingState::update() {
    if (this->getGhost().lock() and this->getStateManager().lock()){
        this->getGhost().lock()->setSpeed(this->getGhost().lock()->getDefaultSpeed());
        if (this->getGhost().lock()->isFrightened()){
            this->getStateManager().lock()->push(std::make_unique<GhostFrightenedState>(this->getStateManager(), this->getGhost()));
            this->getGhost().lock()->setFrightened(false);
        }
    }
}


