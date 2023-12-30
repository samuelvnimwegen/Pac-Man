//
// Created by Samuel on 16/11/2023.
//

#include "VictoryState.h"
#include "../Stopwatch.h"
#include "StateManager.h"
#include "../World.h"

GUI::VictoryState::VictoryState(const std::weak_ptr<StateManager> &stateManager,
                                const std::weak_ptr<Model::World> &world) : State(stateManager, world) {
    victoryTime = Model::Stopwatch::instance()->getLevelTime();
    this->setTag(victory);
    if (world.lock()){
        world.lock().reset();
    }
}

void GUI::VictoryState::update(const key &key) {
    if (this->getStateManager().lock() and this->getWorld().lock()){
        // Als er op escape geduwd wordt terug naar menu:
        if (key == escape){
            while (this->getStateManager().lock()->getSize() > 1){
                this->getStateManager().lock()->pop();
            }
        }
        // Na 1 seconde victory screen of bij een spatie naar volgende level, dit door de victoryState te poppen
        else if (Model::Stopwatch::instance()->getLevelTime() - this->getVictoryTime() > 1 or key == space){
            this->getWorld().lock()->restartWorld();
            this->getStateManager().lock()->pop();
        }
    }
}

double GUI::VictoryState::getVictoryTime() const {
    return victoryTime;
}

GUI::VictoryState::~VictoryState() = default;





