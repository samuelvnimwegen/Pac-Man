//
// Created by Samuel on 16/11/2023.
//

#ifndef PAC_MAN_WORLD_H
#define PAC_MAN_WORLD_H
#include "EntityModel.h"
#include "vector"
#include "Wall.h"
#include "iostream"
using namespace std;

class World {
    EntityModel* world[11][20];
    int height;
    int width;
public:
    World();

    [[nodiscard]] int getHeight() const;

    void setHeight(int hg);

    [[nodiscard]] int getWidth() const;

    void setWidth(int wd);

    EntityModel* getItem(const int &row, const int &col);

    void addItem(EntityModel* item);
};


#endif //PAC_MAN_WORLD_H
