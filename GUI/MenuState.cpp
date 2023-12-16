//
// Created by Samuel on 16/11/2023.
//

#include "MenuState.h"

GUI::MenuState::MenuState() {
    this->setTag("MenuState");
}

shared_ptr<GUI::State> GUI::MenuState::getNext() {
    return make_shared<LevelState>();
}

GUI::MenuState::~MenuState() = default;

shared_ptr<GUI::State> GUI::VictoryState::getNext() {
    return make_shared<LevelState>();
}
