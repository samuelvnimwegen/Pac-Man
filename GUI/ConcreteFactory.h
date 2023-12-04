//
// Created by Samuel on 17/11/2023.
//

#ifndef PAC_MAN_CONCRETEFACTORY_H
#define PAC_MAN_CONCRETEFACTORY_H
#include "EntityView.h"
#include "GUIWall.h"
#include "GUIPacMan.h"
#include "GUICoin.h"
#include "GUIGhost.h"
#include "../AbstractFactory.h"
#include "memory"


class GUI::ConcreteFactory: public Model::AbstractFactory{
public:
    explicit ConcreteFactory(Model::World *world);

    std::unique_ptr<Model::PacMan> createPacMan(const int &row, const int &col) override;

    std::unique_ptr<Model::Wall>  createWall(const int &row, const int &col) override;

    std::unique_ptr<Model::Coin>  createCoin(const int &row, const int &col) override;

    std::unique_ptr<Model::Ghost> createGhost(const int &row, const int &col) override;

};


#endif //PAC_MAN_CONCRETEFACTORY_H
