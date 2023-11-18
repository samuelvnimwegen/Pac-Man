//
// Created by Samuel on 16/11/2023.
//

#include "EntityModel.h"



int EntityModel::getRow() const {
    return row;
}

void EntityModel::setPosX(int x) {
    EntityModel::row = x;
}

int EntityModel::getCol() const {
    return col;
}

void EntityModel::setPosY(int y) {
    EntityModel::col = y;
}

const string &EntityModel::getTag() const {
    return tag;
}

void EntityModel::setTag(const string &tg) {
    EntityModel::tag = tg;
}

EntityModel::EntityModel(int row, int col) : Subject(row, col) {}
