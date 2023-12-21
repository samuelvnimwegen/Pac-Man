//
// Created by Samuel on 16/11/2023.
//

#include "Coin.h"

Model::Coin::Coin(int row, int col) : Collectable(row, col) {
    this->setTag("Coin");
    this->setValue(10);
    consumed = false;
}

bool Model::Coin::isConsumed1() const {
    return consumed;
}

void Model::Coin::setConsumed(bool cons) {
    Coin::consumed = cons;
}

void Model::Coin::update(const int &ticks) {
    for (const auto& observer: this->getObservers()){
        observer->update(ticks);
    }
}
