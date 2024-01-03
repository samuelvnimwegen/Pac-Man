//
// Created by Samuel on 03/01/2024.
//

#include "EscapeWall.h"
#include "Observer.h"


Model::EscapeWall::EscapeWall(int row, int col) : Wall(row, col) {
    this->setTag(entityTag::escapeWall);
}

void Model::EscapeWall::update(const double &seconds) {
    for (const auto& observers: this->getObservers()){
        observers->update(seconds);
    }
}


