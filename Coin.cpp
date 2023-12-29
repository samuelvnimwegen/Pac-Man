//
// Created by Samuel on 16/11/2023.
//

#include "Coin.h"

Model::Coin::Coin(int row, int col) : Collectable(row, col) {
    this->setTag(coin);
    this->setValue(10);
}

void Model::Coin::update(const double &seconds) {
    for (const auto& observer: this->getObservers()){
        observer->update(seconds);
    }
}
