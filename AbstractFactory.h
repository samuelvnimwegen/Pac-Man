//
// Created by Samuel on 18/11/2023.
//

#ifndef PAC_MAN_ABSTRACTFACTORY_H
#define PAC_MAN_ABSTRACTFACTORY_H

#include "Subject.h"

class Model::AbstractFactory {
    std::weak_ptr<Model::World> world;
public:
    explicit AbstractFactory(const std::shared_ptr<Model::World>& world);

    virtual std::shared_ptr <PacMan> createPacMan(const int &row, const int &col) = 0;

    virtual std::shared_ptr <Wall> createWall(const int&row, const int &col) = 0;

    virtual std::shared_ptr <Coin> createCoin(const int&row, const int &col) = 0;

    virtual std::shared_ptr <Ghost> createGhost(const int &row, const int &col) = 0;

    [[nodiscard]] std::shared_ptr<Model::World> getWorld() const;

};


#endif //PAC_MAN_ABSTRACTFACTORY_H
