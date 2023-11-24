//
// Created by Samuel on 16/11/2023.
//

#include "StateManager.h"

GUI::StateManager::StateManager() {
    stack.push_back(new MenuState());
}

GUI::State *GUI::StateManager::getCurrentState() {
    return stack.at(stack.size() - 1);
}

void GUI::StateManager::pop() {
    if (stack.size() != 1){
        delete stack.at(stack.size() - 1);
        stack.pop_back();
    }
}

void GUI::StateManager::push() {
    if (this->getCurrentState()->getNext() != nullptr){
        stack.push_back(this->getCurrentState()->getNext());
    }
}

void GUI::StateManager::pauze() {
    stack.push_back(new PausedState());
}
