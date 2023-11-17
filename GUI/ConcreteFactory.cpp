//
// Created by Samuel on 17/11/2023.
//

#include "ConcreteFactory.h"

EntityView *ConcreteFactory::makeViewEntity(const int &row, const int &col, const string &tag) {
    if (tag == "Wall"){
        return new GUIWall(world, col, row);
    }
    return nullptr;
}

ConcreteFactory::ConcreteFactory(Observer *observer, World *world) : observer(observer), world(world) {}
