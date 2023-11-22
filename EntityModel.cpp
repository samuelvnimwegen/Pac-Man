//
// Created by Samuel on 16/11/2023.
//

#include "EntityModel.h"

const string &EntityModel::getTag() const {
    return tag;
}

void EntityModel::setTag(const string &tg) {
    EntityModel::tag = tg;
}

EntityModel::EntityModel(int row, int col) : Subject(row, col) {
    consumed = false;
}

bool EntityModel::isConsumed() const {
    return consumed;
}

void EntityModel::consume() {
    consumed = true;
}