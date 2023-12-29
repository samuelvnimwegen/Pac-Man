//
// Created by Samuel on 26/12/2023.
//

#include "GhostResetState.h"


Model::GhostResetState::GhostResetState(const std::weak_ptr<Model::GhostStateManager> &stateManager,
                                        const std::weak_ptr<Model::Ghost> &ghost) : GhostState(stateManager, ghost) {
    tag = ghostStateTag::reset;
    if (this->getGhost().lock()){
        // Maak de ghost 5 keer zo snel als normaal
        this->getGhost().lock()->setSpeed(this->getGhost().lock()->getDefaultSpeed() * 5);
    }
}

void Model::GhostResetState::update() {
    if (this->getGhost().lock() and this->getStateManager().lock()){
        // Als hij weer op zijn startpunt is, weer in chase modus en dus de bovenste state poppen
        auto ghost = this->getGhost().lock();
        if (toTile(ghost->getX()) == ghost->getStartCol() and toTile(ghost->getY() == ghost->getStartRow())){
            this->getStateManager().lock()->pop();
        }
    }
}
