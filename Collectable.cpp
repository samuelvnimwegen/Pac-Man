//
// Created by Samuel on 16/11/2023.
//

#include "Collectable.h"

Model::Collectable::Collectable(int row, int col) : EntityModel(row, col) {
    value = 0;
}

int Model::Collectable::getValue() const {
    return value;
}

void Model::Collectable::setValue(int val) {
    Collectable::value = val;
}


