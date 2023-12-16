//
// Created by Samuel on 16/11/2023.
//

#include "StateManager.h"

#include <memory>

GUI::StateManager::StateManager() {
    stack.push(std::make_shared<GUI::MenuState>());
}

std::shared_ptr<GUI::State> GUI::StateManager::getCurrentState() {
    return stack.top();
}

void GUI::StateManager::pop() {
    stack.pop();
}

void GUI::StateManager::push() {
    stack.push(this->getCurrentState()->getNext());
}

void GUI::StateManager::pauze() {
    stack.push(std::make_shared<GUI::PausedState>());
}
