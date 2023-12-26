//
// Created by Samuel on 26/12/2023.
//

#include "GhostStateManager.h"

Model::GhostStateManager::GhostStateManager() = default;

std::shared_ptr<Model::GhostState> Model::GhostStateManager::getCurrentState() {
    return stack.top();
}

void Model::GhostStateManager::pop() {
    stack.pop();
}

void Model::GhostStateManager::push() {
    stack.push()
}

