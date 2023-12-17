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
    std::shared_ptr<sf::RenderWindow> window;
public:
    explicit ConcreteFactory(const std::shared_ptr<Model::World>& world, const std::shared_ptr<sf::RenderWindow> &win);

    std::shared_ptr<Model::PacMan> createPacMan(const int &row, const int &col) override;

    std::shared_ptr <Model::Wall> createWall(const int &row, const int &col) override;

    std::shared_ptr <Model::Coin> createCoin(const int &row, const int &col) override;

    std::shared_ptr <Model::Ghost> createGhost(const int &row, const int &col) override;

    [[nodiscard]] const std::shared_ptr<sf::RenderWindow> &getWindow() const;

};


#endif //PAC_MAN_CONCRETEFACTORY_H
