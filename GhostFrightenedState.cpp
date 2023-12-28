//
// Created by Samuel on 26/12/2023.
//

#include "GhostFrightenedState.h"

void Model::GhostFrightenedState::update() {
    if (this->getGhost().lock() and this->getStateManager().lock()){
        // Als hij langer dan 5 seconden feared is, teruggaan naar vorige state
        if (Model::Stopwatch::instance()->getLevelTime() - this->getFrightenedTime() > 5){
            this->getStateManager().lock()->pop();
        }
        // Als hij opgegeten is door pacman, feared state clearen en naar reset state:
        else if (toTile(this->getGhost().lock()->getWorld()->getPacMan()->getX()) == toTile(this->getGhost().lock()->getX())
        and toTile(this->getGhost().lock()->getWorld()->getPacMan()->getY()) == toTile(this->getGhost().lock()->getY())){
            this->getStateManager().lock()->pop();
            this->getStateManager().lock()->push(std::make_unique<Model::GhostResetState>(this->getStateManager(), this->getGhost()));
        }
    }
}

Model::GhostFrightenedState::GhostFrightenedState(const std::weak_ptr<Model::GhostStateManager> &stateManager,
                                                  const std::weak_ptr<Model::Ghost> &ghost) : GhostState(stateManager,
                                                                                                         ghost) {
    frightenedTime = Model::Stopwatch::instance()->getLevelTime();
    tag = ghostStateTag::frightened;
}

double Model::GhostFrightenedState::getFrightenedTime() const {
    return frightenedTime;
}
