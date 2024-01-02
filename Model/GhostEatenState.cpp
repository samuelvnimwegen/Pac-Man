//
// Created by Samuel on 29/12/2023.
//

#include "GhostEatenState.h"
#include "Stopwatch.h"
#include "GhostStateManager.h"
#include "GhostResetState.h"
Model::GhostEatenState::GhostEatenState(const std::weak_ptr<Model::GhostStateManager> &stateManager,
                                        const std::weak_ptr<Model::Ghost> &ghost) : GhostState(stateManager, ghost) {
    eatenTime = Model::Stopwatch::instance()->getLevelTime();
    tag = ghostStateTag::eaten;
    try{
        ghost.lock()->getWorld()->getScoreClass()->ghostConsumed();
    }
    catch (...){
        throw std::runtime_error("Ghost in GhostEatenState.cpp constructor didn't exist anymore");
    }
}

double Model::GhostEatenState::getEatenTime() const {
    return eatenTime;
}

void Model::GhostEatenState::update() {
    // Na 0.4 seconden naar reset state
    if (Model::Stopwatch::instance()->getLevelTime() - this->getEatenTime() > 0.4){
        if (this->getGhost().lock() and this->getStateManager().lock()){
            this->getStateManager().lock()->pop();
            this->getStateManager().lock()->push(std::make_unique<Model::GhostResetState>(this->getStateManager(), this->getGhost()));
        }
    }
}
