//
// Created by Samuel on 16/11/2023.
//

#include "LevelState.h"

GUI::LevelState::LevelState(){
   this->setTag("LevelState");
}

GUI::VictoryState *GUI::LevelState::getNext() {
    return new VictoryState();
}

GUI::LevelState::~LevelState() = default;

GUI::VictoryState::~VictoryState() = default;
