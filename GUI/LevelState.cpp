//
// Created by Samuel on 16/11/2023.
//

#include "LevelState.h"

LevelState::LevelState(){
   this->setTag("LevelState");
}

VictoryState *LevelState::getNext() {
    return new VictoryState();
}

LevelState::~LevelState() = default;

VictoryState::~VictoryState() = default;
