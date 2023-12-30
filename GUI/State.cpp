//
// Created by Samuel on 16/11/2023.
//

#include "State.h"


stateTag GUI::State::getTag() const {
    return tag;
}

void GUI::State::setTag(const stateTag &stateTag) {
    State::tag = stateTag;
}

GUI::State::State(const std::weak_ptr<StateManager> &stateManager, const std::weak_ptr<Model::World> &world)
        : stateManager(stateManager), world(world) {
    tag = menu;
}

const std::weak_ptr<GUI::StateManager> &GUI::State::getStateManager() const {
    return stateManager;
}

const std::weak_ptr<Model::World> &GUI::State::getWorld() const {
    return world;
}

GUI::State::~State() = default;
