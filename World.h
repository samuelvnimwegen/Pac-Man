//
// Created by Samuel on 16/11/2023.
//

#ifndef PAC_MAN_WORLD_H
#define PAC_MAN_WORLD_H
#include "EntityModel.h"
#include "vector"
#include "Wall.h"
#include "iostream"
#include "AbstractFactory.h"
#include "cassert"
using namespace std;

class World {
    EntityModel* world[11][20]{};
    int height;
    int width;
    AbstractFactory* factory;
    vector<EntityModel*> entities;
public:
    explicit World();

    void buildWorld();

    [[nodiscard]] int getHeight() const;

    void setHeight(int hg);

    [[nodiscard]] int getWidth() const;

    void setWidth(int wd);

    EntityModel* getItem(const int &row, const int &col);

    void addItem(EntityModel* item);

    AbstractFactory *getFactory() const;

    void setFactory(AbstractFactory *fac);
};


#endif //PAC_MAN_WORLD_H
