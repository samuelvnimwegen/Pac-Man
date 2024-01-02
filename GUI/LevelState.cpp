//
// Created by Samuel on 16/11/2023.
//

#include "LevelState.h"
#include "../Model/World.h"
#include <memory>
#include "StateManager.h"
#include "VictoryState.h"
#include "PausedState.h"
#include "GameOverState.h"

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
        if (this->getWorld().lock()->getScoreClass()->getLivesLeft() == 0 and
                !this->getWorld().lock()->getPacMan()->isDead()){
            this->getStateManager().lock()->push(std::make_unique<GameOverState>(this->getStateManager(), this->getWorld()));
        }
        else if (int(this->getWorld().lock()->getCoins().size()) + int(this->getWorld().lock()->getFruits().size()) ==
        this->getWorld().lock()->getScoreClass()->getCoinsCollected())
        {
            this->getStateManager().lock()->push(std::make_unique<VictoryState>(this->getStateManager(), this->getWorld()));
        }
        else if (key == escape){
            this->getStateManager().lock()->push(std::make_unique<PausedState>(this->getStateManager(), this->getWorld()));
        }
    }
}


GUI::LevelState::~LevelState() = default;
