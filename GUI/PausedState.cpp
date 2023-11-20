//
// Created by Samuel on 16/11/2023.
//

#include "PausedState.h"

PausedState::PausedState() {
    this->setTag("PausedState");
}

State *PausedState::getNext() {
    return new MenuState();
}

PausedState::~PausedState() = default;
