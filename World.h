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


class Model::World {
    vector<vector<Model::EntityModel*>> world;
    int height;
    int width;
    Model::AbstractFactory* factory;
    Model::PacMan* pacMan;
    Camera* camera;
    int coinsLeft;
    vector<Coin*> coins;
    vector<Ghost*> ghosts;
public:
    explicit World();

    virtual ~World();

    void buildWorld();

    void die();

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

    [[nodiscard]] Camera *getCamera() const;

    void setCamera(Camera *cam);

    [[nodiscard]] int getCoinsLeft() const;

    void setCoinsLeft(int coins);

    void addGhost(Ghost* ghost);

    [[nodiscard]] const vector<Ghost *> &getGhosts() const;

    void setGhosts(const vector<Ghost *> &ghostVector);
};


#endif //PAC_MAN_WORLD_H
