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
    std::vector<std::vector<std::shared_ptr<Model::EntityModel>>> world;
    std::vector<std::vector<std::shared_ptr<Model::Coin>>> collectableWorld;
    int height;
    int width;
    std::shared_ptr<Model::AbstractFactory> factory;
    std::shared_ptr<Model::PacMan> pacMan;
    std::vector<std::shared_ptr<Coin>> coins;
    std::vector<std::shared_ptr<Ghost>> ghosts;
    std::vector<std::shared_ptr<Wall>> walls;
    int coinsLeft;
    bool gameStarted;
public:
    explicit World();

    virtual ~World();

    void buildWorld();

    void restart();

    void update(const int &ticks);

    [[nodiscard]] int getHeight() const;

    [[nodiscard]] int getWidth() const;

    std::shared_ptr<Model::EntityModel> getItem(const int &row, const int &col);

    void setItem(const std::shared_ptr<Model::EntityModel>& item, const int &row, const int &col);

    void addItem(const std::shared_ptr<Model::EntityModel>& item);

    [[nodiscard]] std::shared_ptr<AbstractFactory> getFactory() const;

    void setFactory(std::shared_ptr<AbstractFactory> fac);

    [[nodiscard]] int getCoinsLeft() const;

    void setCoinsLeft(int coinsAmount);

    void addGhost(const std::shared_ptr<Model::Ghost>& ghost);

    void addWall(const std::shared_ptr<Model::Wall> &wall);

    void addCoin(const std::shared_ptr<Model::Coin> &coin);

    [[nodiscard]] std::shared_ptr<Model::Collectable> getCollectable(const int &row, const int &col);

    [[nodiscard]] const std::shared_ptr<Model::PacMan> &getPacMan() const;

    void setPacMan(const std::shared_ptr<Model::PacMan> &newPacMan);

    [[nodiscard]] const std::vector<std::shared_ptr<Coin>> &getCoins() const;

    void setCoins(const std::vector<std::shared_ptr<Coin>> &newCoins);

    [[nodiscard]] const std::vector<std::shared_ptr<Ghost>> &getGhosts() const;

    void setGhosts(const std::vector<std::shared_ptr<Ghost>> &newGhosts);

    [[nodiscard]] const std::vector<std::shared_ptr<Wall>> &getWalls() const;

    void setWalls(const std::vector<std::shared_ptr<Wall>> &newWalls);

    [[nodiscard]] bool isGameStarted() const;

    void setGameStarted(bool gameStarted);

};


#endif //PAC_MAN_WORLD_H
