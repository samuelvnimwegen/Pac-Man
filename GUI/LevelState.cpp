//
// Created by Samuel on 16/11/2023.
//

#include "LevelState.h"
#include "../World.h"
#include <memory>
#include "StateManager.h"
#include "VictoryState.h"
#include "PausedState.h"

GUI::LevelState::LevelState(const std::weak_ptr<StateManager> &stateManager, const std::weak_ptr<Model::World> &world)
        : State(stateManager, world) {
    this->setTag(level);
    if (this->getWorld().lock()){
        this->getWorld().lock()->restartWorld();
    }
    Model::Stopwatch::instance()->startLevel();
}

void GUI::LevelState::update(const key &key){
    if (this->getWorld().lock() and this->getStateManager().lock()){
        if (this->getWorld().lock()->getCoinsLeft() == 0){
            this->getStateManager().lock()->push(std::make_unique<VictoryState>(this->getStateManager(), this->getWorld()));
        }
        else if (key == escape){
            this->getStateManager().lock()->push(std::make_unique<PausedState>(this->getStateManager(), this->getWorld()));
        }
    }
}


GUI::LevelState::~LevelState() = default;
