//
// Created by Samuel on 17/11/2023.
//

#ifndef PAC_MAN_CONCRETEFACTORY_H
#define PAC_MAN_CONCRETEFACTORY_H
#include "EntityView.h"
#include "GUIWall.h"
#include "../AbstractFactory.h"
class Game;
class ConcreteFactory: public AbstractFactory{
    Game* game;
public:
    ConcreteFactory(World *world, Game *game);

    PacMan * createPacMan(const int &row, const int &col) override;

    Wall * createWall(const int &row, const int &col) override;

    Coin * createCoin(const int &row, const int &col) override;
};


#endif //PAC_MAN_CONCRETEFACTORY_H
