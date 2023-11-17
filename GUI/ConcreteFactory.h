//
// Created by Samuel on 17/11/2023.
//

#ifndef PAC_MAN_CONCRETEFACTORY_H
#define PAC_MAN_CONCRETEFACTORY_H
#include "EntityView.h"
#include "GUIWall.h"

class ConcreteFactory {
    Observer* observer;
    World* world;
public:
    ConcreteFactory(Observer *observer, World *world);

    EntityView* makeViewEntity(const int &row, const int &col, const string &tag);
};


#endif //PAC_MAN_CONCRETEFACTORY_H
