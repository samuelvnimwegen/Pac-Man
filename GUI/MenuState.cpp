//
// Created by Samuel on 16/11/2023.
//

#include "MenuState.h"

GUI::MenuState::MenuState() {
    this->setTag("MenuState");
}

GUI::LevelState *GUI::MenuState::getNext() {
    return new LevelState();
}

GUI::MenuState::~MenuState() = default;

GUI::State *GUI::VictoryState::getNext() {
    return new MenuState();
}
