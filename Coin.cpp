//
// Created by Samuel on 16/11/2023.
//

#include "Coin.h"

Model::Coin::Coin(int row, int col) : Collectable(row, col) {
    this->setTag("Coin");
    this->setValue(10);
}
