//
// Created by Samuel on 26/12/2023.
//

#include "GhostFrightenedState.h"
#include "GhostResetState.h"
#include "GhostChasingState.h"
#include "GhostIdleState.h"

Model::GhostFrightenedState::GhostFrightenedState() {
    tag = ghostStateTag::frightened;
}

std::shared_ptr<Model::GhostState> Model::GhostFrightenedState::getNext() {
    return std::make_shared<Model::GhostResetState>();
}

std::shared_ptr<Model::GhostState> Model::GhostChasingState::getNext() {
    return std::make_shared<GhostFrightenedState>();
}

std::shared_ptr<Model::GhostState> Model::GhostIdleState::getNext() {
    return std::make_shared<Model::GhostChasingState>();
}

std::shared_ptr<Model::GhostState> Model::GhostResetState::getNext() {
    return std::make_shared<Model::GhostChasingState>();
}
