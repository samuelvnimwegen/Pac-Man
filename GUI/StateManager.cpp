//
// Created by Samuel on 16/11/2023.
//

#include "StateManager.h"

#include <memory>

GUI::StateManager::StateManager() = default;

void GUI::StateManager::pop() {
    stack.pop();
}

void GUI::StateManager::update(const key &key) {
    stack.top()->update(key);
}

void GUI::StateManager::push(std::unique_ptr<State> state) {
    stack.push(std::move(state));
}

int GUI::StateManager::getSize() {
    return int(stack.size());
}

stateTag GUI::StateManager::getCurrentTag() {
    return stack.top()->getTag();
}

