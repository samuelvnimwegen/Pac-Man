//
// Created by Samuel on 16/11/2023.
//

#include "VictoryState.h"
#include "StateManager.h"
#include "../Model/World.h"

GUI::VictoryState::VictoryState(const std::weak_ptr<StateManager> &stateManager,
                                const std::weak_ptr<Model::World> &world) : State(stateManager, world) {
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
        else if (key == space){
            this->getWorld().lock()->nextLevel();
            this->getStateManager().lock()->pop();
        }
    }
}


GUI::VictoryState::~VictoryState() = default;





