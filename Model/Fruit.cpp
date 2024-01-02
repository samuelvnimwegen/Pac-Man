//
// Created by Samuel on 16/11/2023.
//

#include "Fruit.h"

Model::Fruit::Fruit(int row, int col) : Collectable(row, col) {
    this->setTag(fruit);
    this->setValue(50);
}
