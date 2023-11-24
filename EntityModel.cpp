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

Model::EntityModel::EntityModel(int row, int col) : Subject(row, col) {
    consumed = false;
}

bool Model::EntityModel::isConsumed() const {
    return consumed;
}

void Model::EntityModel::consume() {
    consumed = true;
}

void Model::EntityModel::addObserver(Model::Observer *observer) {
    observers.push_back(observer);
}

const vector<Model::Observer *> &Model::EntityModel::getObservers() const {
    return observers;
}
