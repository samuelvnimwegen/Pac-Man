//
// Created by Samuel on 16/11/2023.
//

#include "Collectable.h"

Collectable::Collectable(int row, int col) : EntityModel(row, col) {
    value = 0;
}

int Collectable::getValue() const {
    return value;
}

void Collectable::setValue(int value) {
    Collectable::value = value;
}


