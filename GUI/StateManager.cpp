//
// Created by Samuel on 16/11/2023.
//

#include "StateManager.h"

StateManager::StateManager() {
    stack.push_back(new MenuState());
}

State *StateManager::getCurrentState() {
    return stack.at(stack.size() - 1);
}

void StateManager::pop() {
    if (stack.size() != 1){
        delete stack.at(stack.size() - 1);
        stack.pop_back();
    }
}

void StateManager::push() {
    if (this->getCurrentState()->getNext() != nullptr){
        stack.push_back(this->getCurrentState()->getNext());
    }
}

void StateManager::pauze() {
    stack.push_back(new PausedState());
}
