//
// Created by Samuel on 26/12/2023.
//

#include "GhostStateManager.h"

#include <memory>
Model::GhostStateManager::GhostStateManager()= default;

void Model::GhostStateManager::pop() {
    stack.pop();
}

void Model::GhostStateManager::update() {
    stack.top()->update();
}

void Model::GhostStateManager::push(std::unique_ptr<Model::GhostState> uniqueState) {
    stack.push(std::move(uniqueState));
}

void Model::GhostStateManager::reset() {
    while (stack.size() > 1){
        stack.pop();
    }
}

ghostStateTag Model::GhostStateManager::getCurrentTag() {
    return stack.top()->getTag();
}

