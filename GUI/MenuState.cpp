//
// Created by Samuel on 16/11/2023.
//

#include "MenuState.h"

MenuState::MenuState() {
    this->setTag("MenuState");
}

LevelState *MenuState::getNext() {
    return new LevelState();
}

MenuState::~MenuState() = default;

State *VictoryState::getNext() {
    return new MenuState();
}
