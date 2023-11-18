//
// Created by Samuel on 18/11/2023.
//

#ifndef PAC_MAN_ABSTRACTFACTORY_H
#define PAC_MAN_ABSTRACTFACTORY_H
#include "EntityModel.h"
#include "Wall.h"
class World;
class AbstractFactory {
    World* world;
public:
    explicit AbstractFactory(World *world);

    virtual EntityModel* createEntity(const string &tag, const int &row, const int &col);
};


#endif //PAC_MAN_ABSTRACTFACTORY_H
