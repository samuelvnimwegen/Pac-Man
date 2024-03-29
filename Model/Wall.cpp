//
// Created by Samuel on 16/11/2023.
//

#include "Wall.h"




Model::Wall::Wall(int row, int col) : EntityModel(row, col) {
    this->setTag(wall);
}

void Model::Wall::update(const double &seconds) {
    for (const auto& observer: this->getObservers()){
        observer->update(seconds);
    }
}


