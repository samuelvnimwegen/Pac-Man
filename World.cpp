//
// Created by Samuel on 16/11/2023.
//

#include "World.h"

World::World() {
    width = 15;
    height = 15;
    // Muren om level heen
    for (int i = 0; i < 15; ++i){
        world[0][i] = new Wall();
        world[14][i] = new Wall();
        world[i][0] = new Wall();
        world[i][14] = new Wall();
    }

    // Custom muren:
    world[2][2] = new Wall;
    world[2][3] = new Wall;
    world[2][4] = new Wall;
    world[3][2] = new Wall;



}

int World::getHeight() const {
    return height;
}

void World::setHeight(int height) {
    World::height = height;
}

int World::getWidth() const {
    return width;
}

void World::setWidth(int width) {
    World::width = width;
}

EntityModel *World::getItem(const int &row, const int &col) {
    return world[row][col];
}
