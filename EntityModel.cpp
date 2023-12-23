//
// Created by Samuel on 16/11/2023.
//


#include "EntityModel.h"
#include <cmath>
using namespace std;

const string &Model::EntityModel::getTag() const {
    return tag;
}

void Model::EntityModel::setTag(const string &tg) {
    EntityModel::tag = tg;
}

Model::EntityModel::EntityModel(int r, int c) : Subject() {
    row = double(r);
    col = double(c);
}

double Model::EntityModel::getY() const {
    return row;
}

double Model::EntityModel::getX() const {
    return col;
}

void Model::EntityModel::setY(double r) {
    EntityModel::row = r;
}

void Model::EntityModel::setX(double c) {
    EntityModel::col = c;
}

int toTile(double db) {
    db += 0.5;
    double integer;
    modf(db, &integer);
    return int(integer);
}



