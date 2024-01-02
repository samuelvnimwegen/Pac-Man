//
// Created by Samuel on 26/12/2023.
//

#include "GhostIdleState.h"
#include "GhostIdleFrightenedState.h"

Model::GhostIdleState::GhostIdleState(const std::weak_ptr<Model::GhostStateManager> &stateManager,
                                      const std::weak_ptr<Model::Ghost> &ghost) : GhostState(stateManager, ghost) {
    tag = ghostStateTag::idle;
}


void Model::GhostIdleState::update() {
    if (this->getStateManager().lock() and this->getGhost().lock()){
        if (this->getGhost().lock()->isFrightened()){
            this->getStateManager().lock()->push(std::make_unique<GhostIdleFrightenedState>(this->getStateManager(), this->getGhost()));
        }
        else if (Model::Stopwatch::instance()->getLevelTime() > this->getGhost().lock()->getWaitTime() and this->getGhost().lock()->getWorld()->isGameStarted()){
            this->getStateManager().lock()->push(std::make_unique<GhostChasingState>(this->getStateManager(), this->getGhost()));
        }
    }

}