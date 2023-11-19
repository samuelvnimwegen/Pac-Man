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
using namespace std;

class World {
    EntityModel* world[11][20]{};
    int height;
    int width;
    AbstractFactory* factory;
    vector<EntityModel*> entities;
    PacMan* pacMan;
    Camera* camera;
public:
    explicit World();

    virtual ~World();

    void buildWorld();

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

    [[nodiscard]] const vector<EntityModel *> &getEntities() const;

    void setEntities(const vector<EntityModel *> &ent);

    [[nodiscard]] Camera *getCamera() const;

    void setCamera(Camera *cam);
};


#endif //PAC_MAN_WORLD_H
