//
// Created by Samuel on 26/12/2023.
//

#include "GhostStateManager.h"

#include <memory>
#include "Stopwatch.h"
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
    Model::Stopwatch::instance()->startLevel();
}

ghostStateTag Model::GhostStateManager::getCurrentTag() {
    return stack.top()->getTag();
}

