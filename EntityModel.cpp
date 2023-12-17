//
// Created by Samuel on 16/11/2023.
//

#include "EntityModel.h"
using namespace std;

const string &Model::EntityModel::getTag() const {
    return tag;
}

void Model::EntityModel::setTag(const string &tg) {
    EntityModel::tag = tg;
}

Model::EntityModel::EntityModel(int r, int c) : Subject() {
    row = r;
    col = c;
    consumed = false;
}

bool Model::EntityModel::isConsumed() const {
    return consumed;
}

void Model::EntityModel::consume() {
    consumed = true;
}

int Model::EntityModel::getRow() const {
    return row;
}

int Model::EntityModel::getCol() const {
    return col;
}

void Model::EntityModel::setConsumed(bool cons) {
    EntityModel::consumed = cons;
}

void Model::EntityModel::setRow(int r) {
    EntityModel::row = r;
}

void Model::EntityModel::setCol(int c) {
    EntityModel::col = c;
}



