//
// Created by Samuel on 26/12/2023.
//

#include "GhostFrightenedState.h"
#include "cmath"
void Model::GhostFrightenedState::update() {
    if (this->getGhost().lock() and this->getStateManager().lock()){
        // Op het moment dat het fruit gepakt wordt, van richting veranderen.
        if (!this->isFirstDirectionChange()){
            this->getGhost().lock()->initialFearMove();
            this->setFirstDirectionChange(true);
        }
        // Als hij opnieuw frightened is in de timing, timer aanpassen met wachttijd
        if (this->getGhost().lock()->isFrightened()){
            frightenedTime = Model::Stopwatch::instance()->getLevelTime();
            this->getGhost().lock()->setFrightened(false);
        }
        // Als hij langer dan de nodige tijdsduur feared is, terug naar vorige state
        // De fear-time begint op 7 seconden en wordt voor elk level 10% korter
        else if (Model::Stopwatch::instance()->getLevelTime() - this->getFrightenedTime() > 7 * pow(0.9, this->getGhost().lock()->getWorld()->getLevelNr())){
            this->getStateManager().lock()->pop();
        }
        // Als hij opgegeten is door pacman, feared state clearen en naar eaten state:
        else if (toTile(this->getGhost().lock()->getWorld()->getPacMan()->getX()) == toTile(this->getGhost().lock()->getX())
        and toTile(this->getGhost().lock()->getWorld()->getPacMan()->getY()) == toTile(this->getGhost().lock()->getY())){
            for (const auto& observer: this->getGhost().lock()->getObservers()){
                observer->ghostEaten();
            }
            this->getStateManager().lock()->push(std::make_unique<Model::GhostEatenState>(this->getStateManager(), this->getGhost()));
        }
    }
}

Model::GhostFrightenedState::GhostFrightenedState(const std::weak_ptr<Model::GhostStateManager> &stateManager,
                                                  const std::weak_ptr<Model::Ghost> &ghost) : GhostState(stateManager,
                                                                                                         ghost) {
    firstDirectionChange = false;
    frightenedTime = Model::Stopwatch::instance()->getLevelTime();
    tag = ghostStateTag::frightened;
    if (this->getGhost().lock()){
        this->getGhost().lock()->setFrightened(false);
        // Maak de ghosts half zo snel als normaal
        this->getGhost().lock()->setSpeed(this->getGhost().lock()->getDefaultSpeed() / 2);
    }

}

double Model::GhostFrightenedState::getFrightenedTime() const {
    return frightenedTime;
}

Model::GhostFrightenedState::GhostFrightenedState(const std::weak_ptr<Model::GhostStateManager> &stateManager,
                                                  const std::weak_ptr<Model::Ghost> &ghost, double frightenedTime)
        : GhostState(stateManager, ghost), frightenedTime(frightenedTime) {
    firstDirectionChange = false;
    tag = ghostStateTag::frightened;
    if (this->getGhost().lock()){
        this->getGhost().lock()->changeDirection();
        // Maak de ghosts half zo snel als normaal
        this->getGhost().lock()->setSpeed(this->getGhost().lock()->getDefaultSpeed() / 2);
    }
}

bool Model::GhostFrightenedState::isFirstDirectionChange() const {
    return firstDirectionChange;
}

void Model::GhostFrightenedState::setFirstDirectionChange(bool change) {
    GhostFrightenedState::firstDirectionChange = change;
}
