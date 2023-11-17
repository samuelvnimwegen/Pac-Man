//
// Created by Samuel on 16/11/2023.
//

#include "Wall.h"



Wall::Wall(int row, int col) : EntityModel(row, col) {
    this->setTag("Wall");
}
