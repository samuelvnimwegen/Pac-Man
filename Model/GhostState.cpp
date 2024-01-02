//
// Created by Samuel on 26/12/2023.
//

#include "GhostState.h"

ghostStateTag Model::GhostState::getTag() const {
    return tag;
}

Model::GhostState::GhostState(const std::weak_ptr<Model::GhostStateManager> &stateManager,
                              const std::weak_ptr<Model::Ghost> &ghost) : stateManager(stateManager), ghost(ghost) {
    tag = ghostStateTag::idle;
}

const std::weak_ptr<Model::GhostStateManager> &Model::GhostState::getStateManager() const {
    return stateManager;
}

const std::weak_ptr<Model::Ghost> &Model::GhostState::getGhost() const {
    return ghost;
}

Model::GhostState::~GhostState() = default;
