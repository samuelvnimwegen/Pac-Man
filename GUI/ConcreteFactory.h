//
// Created by Samuel on 17/11/2023.
//

#ifndef PAC_MAN_CONCRETEFACTORY_H
#define PAC_MAN_CONCRETEFACTORY_H
#include "EntityView.h"
#include "GUIWall.h"
#include "../AbstractFactory.h"

class GUI::ConcreteFactory: public Model::AbstractFactory{
    GUI::Game* game;
    Camera* camera;
public:
    ConcreteFactory(Model::World *world, Game *game);

    Model::PacMan * createPacMan(const int &row, const int &col) override;

    Model::Wall * createWall(const int &row, const int &col) override;

    Model::Coin * createCoin(const int &row, const int &col) override;

    Model::Ghost * createGhost(const int &row, const int &col) override;
};


#endif //PAC_MAN_CONCRETEFACTORY_H
