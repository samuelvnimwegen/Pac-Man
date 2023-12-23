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

void Model::Collectable::update(const int &ticks) {
    for (const auto& observer: this->getObservers()){
        observer->update(ticks);
    }
}

bool Model::Collectable::isConsumed() const {
    return consumed;
}

void Model::Collectable::consume() {
    consumed = true;
}

