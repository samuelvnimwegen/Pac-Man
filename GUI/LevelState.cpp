//
// Created by Samuel on 16/11/2023.
//

#include "LevelState.h"

#include <memory>

GUI::LevelState::LevelState(){
   this->setTag("LevelState");
}

shared_ptr<GUI::State> GUI::LevelState::getNext() {
    return std::make_shared<GUI::VictoryState>();
}

GUI::LevelState::~LevelState() = default;

GUI::VictoryState::~VictoryState() = default;
