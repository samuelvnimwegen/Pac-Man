//
// Created by Samuel on 16/11/2023.
//

#ifndef PAC_MAN_WORLD_H
#define PAC_MAN_WORLD_H
#include "EntityModel.h"
#include "vector"
#include "iostream"
#include "AbstractFactory.h"
#include "cassert"
#include "PacMan.h"
#include "Wall.h"
#include "Camera.h"
#include "Coin.h"
#include "Ghost.h"
#include "Observer.h"
#include "memory"

class Model::World {
    std::vector<std::vector<Model::EntityModel*>> world;
    int height;
    int width;
    Model::AbstractFactory* factory;
    Model::PacMan* pacMan;
    int coinsLeft;
    std::vector<Coin*> coins;
    std::vector<Ghost*> ghosts;
    std::vector<Wall*> walls;
public:
    explicit World();

    virtual ~World();

    void buildWorld();

    void die() const;

    [[nodiscard]] int getHeight() const;

    void setHeight(int hg);

    [[nodiscard]] int getWidth() const;

    void setWidth(int wd);

    EntityModel* getItem(const int &row, const int &col);

    void setItem(EntityModel* item, const int &row, const int &col);

    void addItem(EntityModel* item);

    [[nodiscard]] AbstractFactory *getFactory() const;

    void setFactory(AbstractFactory *fac);

    [[nodiscard]] PacMan *getPacMan() const;

    void setPacMan(PacMan *pMan);

    [[nodiscard]] int getCoinsLeft() const;

    void setCoinsLeft(int coins);

    void addGhost(Ghost* ghost);

    [[nodiscard]] const std::vector<Ghost *> &getGhosts() const;

    void setGhosts(const std::vector<Ghost *> &ghostVector);

    [[nodiscard]] const std::vector<std::vector<Model::EntityModel *>> &getWorld() const;

    [[nodiscard]] const std::vector<Coin *> &getCoins() const;

    [[nodiscard]] const std::vector<Wall *> &getWalls() const;

    void setWorld(const std::vector<std::vector<Model::EntityModel *>> &newWorld);

    void setCoins(const std::vector<Coin *> &coinVector);

    void setWalls(const std::vector<Wall *> &wallVector);

    void addWall(Model::Wall* &wall);

    void addCoin(Model::Coin* &coin);

};


#endif //PAC_MAN_WORLD_H
