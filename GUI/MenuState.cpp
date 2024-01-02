//
// Created by Samuel on 16/11/2023.
//

#include "MenuState.h"
#include "StateManager.h"
#include "LevelState.h"

void GUI::MenuState::update(const key &key) {
    if (key == space){
        this->getStateManager().lock()->push(std::make_unique<LevelState>(this->getStateManager(), this->getWorld()));
        Model::Stopwatch::instance()->startLevel();
    }
}

GUI::MenuState::MenuState(const std::weak_ptr<StateManager> &stateManager, const std::weak_ptr<Model::World> &world)
        : State(stateManager, world) {
    this->setTag(menu);
}

GUI::MenuState::~MenuState() = default;

