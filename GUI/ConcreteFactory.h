//
// Created by Samuel on 17/11/2023.
//

#ifndef PAC_MAN_CONCRETEFACTORY_H
#define PAC_MAN_CONCRETEFACTORY_H
#include "EntityView.h"
#include "GUIWall.h"
#include "GUIPacMan.h"
#include "../AbstractFactory.h"


class GUI::ConcreteFactory: public Model::AbstractFactory{
    Camera* camera;
public:
    explicit ConcreteFactory(Model::World *world);

    Model::PacMan * createPacMan(const int &row, const int &col) override;

    Model::Wall * createWall(const int &row, const int &col) override;

    Model::Coin * createCoin(const int &row, const int &col) override;

    Model::Ghost * createGhost(const int &row, const int &col) override;

    [[nodiscard]] Camera *getCamera() const;
};


#endif //PAC_MAN_CONCRETEFACTORY_H
