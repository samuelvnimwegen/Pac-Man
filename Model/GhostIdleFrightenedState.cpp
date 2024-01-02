//
// Created by Samuel on 02/01/2024.
//

#include "GhostIdleFrightenedState.h"
#include "Stopwatch.h"
#include "Ghost.h"
#include "cmath"

void Model::GhostIdleFrightenedState::update() {
    // Als hij opnieuw frightened is in de timing, timer aanpassen met wachttijd
    if (this->getGhost().lock()->isFrightened()){
        frightenedTime = Model::Stopwatch::instance()->getLevelTime();
        this->getGhost().lock()->setFrightened(false);
    }
    // Als hij langer dan de nodige tijdsduur feared is, terug naar vorige state
    // De fear-time begint op 5 seconden en wordt voor elk level 10% korter
    else if (Model::Stopwatch::instance()->getLevelTime() - this->getFrightenedTime() > 5 * pow(0.9, this->getGhost().lock()->getWorld()->getLevelNr())){
        this->getStateManager().lock()->pop();
    }
    // Als hij opgegeten is door pacman, fearedIdle en Idle state clearen en naar eaten state:
    else if (toTile(this->getGhost().lock()->getWorld()->getPacMan()->getX()) == toTile(this->getGhost().lock()->getX())
             and toTile(this->getGhost().lock()->getWorld()->getPacMan()->getY()) == toTile(this->getGhost().lock()->getY())){
        this->getStateManager().lock()->pop();
        this->getStateManager().lock()->pop();
        this->getStateManager().lock()->push(std::make_unique<Model::GhostEatenState>(this->getStateManager(), this->getGhost()));
    }
    // Als ghost voorbij zijn wachttijd is, in gewone frightened-mode gaan
    else if (Model::Stopwatch::instance()->getLevelTime() > this->getGhost().lock()->getWaitTime() and this->getGhost().lock()->getWorld()->isGameStarted()){
        this->getStateManager().lock()->pop();
        this->getStateManager().lock()->push(std::make_unique<GhostFrightenedState>(this->getStateManager(), this->getGhost(), this->getFrightenedTime()));
    }
}

double Model::GhostIdleFrightenedState::getFrightenedTime() const {
    return frightenedTime;
}

Model::GhostIdleFrightenedState::GhostIdleFrightenedState(const std::weak_ptr<Model::GhostStateManager> &stateManager,
                                                          const std::weak_ptr<Model::Ghost> &ghost) : GhostState(
        stateManager, ghost) {
    frightenedTime = Model::Stopwatch::instance()->getLevelTime();
    tag = ghostStateTag::idleFrightened;
    this->getGhost().lock()->setFrightened(false);
}
