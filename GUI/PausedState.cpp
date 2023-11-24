//
// Created by Samuel on 16/11/2023.
//

#include "PausedState.h"

GUI::PausedState::PausedState() {
    this->setTag("PausedState");
}

GUI::State *GUI::PausedState::getNext() {
    return new MenuState();
}

GUI::PausedState::~PausedState() = default;
