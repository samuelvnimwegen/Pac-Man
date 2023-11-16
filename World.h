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
    EntityModel* world[15][15];
    int height;
    int width;
public:
    World();

    [[nodiscard]] int getHeight() const;

    void setHeight(int height);

    [[nodiscard]] int getWidth() const;

    void setWidth(int width);

    EntityModel* getItem(const int &row, const int &col);
};


#endif //PAC_MAN_WORLD_H
