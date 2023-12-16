//
// Created by Samuel on 16/11/2023.
//

#include "PausedState.h"

GUI::PausedState::PausedState() {
    this->setTag("PausedState");
}

shared_ptr<GUI::State> GUI::PausedState::getNext() {
    return make_shared<GUI::MenuState>();
}

GUI::PausedState::~PausedState() = default;
