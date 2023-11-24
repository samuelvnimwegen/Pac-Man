//
// Created by Samuel on 18/11/2023.
//

#ifndef PAC_MAN_ABSTRACTFACTORY_H
#define PAC_MAN_ABSTRACTFACTORY_H

#include "iostream"
#include "Subject.h"

class Model::AbstractFactory {
    Model::World* world;
public:
    explicit AbstractFactory(Model::World *world);

    virtual Model::PacMan* createPacMan(const int &row, const int &col) = 0;

    virtual Model::Wall* createWall(const int&row, const int &col) = 0;

    virtual Model::Coin* createCoin(const int&row, const int &col) = 0;

    virtual Model::Ghost* createGhost(const int &row, const int &col) = 0;

    World *getWorld() const;

    void setWorld(World *newWorld);
};


#endif //PAC_MAN_ABSTRACTFACTORY_H
