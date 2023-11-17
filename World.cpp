//
// Created by Samuel on 16/11/2023.
//

#include "World.h"

World::World() {
    width = 20;
    height = 11;

    // Lege map met null-pointers maken:
    for (auto & i : world){
        for (auto & j : i){
            j = nullptr;
        }
    }
    // Muren om level heen
    for (int i = 0; i < width; ++i){
        auto wall = new Wall(0, i);
        addItem(wall);
        addItem(new Wall(height - 1, i));
    }
    for (int i = 0; i < height; ++i){
        addItem(new Wall(i, 0));
        addItem(new Wall(i, width - 1));
    }

    // Custom muren:
    addItem(new Wall(2, 2));
    addItem(new Wall(2, 3));
    addItem(new Wall(3, 2));
    addItem(new Wall(4, 2));

    addItem(new Wall(6, 2));
    addItem(new Wall(7, 2));
    addItem(new Wall(8, 2));
    addItem(new Wall(8, 3));

    addItem(new Wall(4, 4));
    addItem(new Wall(4, 5));

    addItem(new Wall(6, 4));
    addItem(new Wall(6, 5));

    addItem(new Wall(1, 5));
    addItem(new Wall(2, 5));

    addItem(new Wall(8, 5));
    addItem(new Wall(9, 5));

    for (int i = 7; i < 13; ++i){
        addItem(new Wall(2, i));
        addItem(new Wall(6, i));
        addItem(new Wall(8, i));
    }
    addItem(new Wall(5, 7));
    addItem(new Wall(5, 12));

    addItem(new Wall(4, 7));
    addItem(new Wall(4, 8));
    addItem(new Wall(4, 11));
    addItem(new Wall(4, 12));

    // Rechts
    addItem(new Wall(2, this->getWidth() - 1 - 2));
    addItem(new Wall(2, this->getWidth() - 1 - 3));
    addItem(new Wall(3, this->getWidth() - 1 - 2));
    addItem(new Wall(4, this->getWidth() - 1 - 2));

    addItem(new Wall(6, this->getWidth() - 1 - 2));
    addItem(new Wall(7, this->getWidth() - 1 - 2));
    addItem(new Wall(8, this->getWidth() - 1 - 2));
    addItem(new Wall(8, this->getWidth() - 1 - 3));

    addItem(new Wall(4, this->getWidth() - 1 - 4));
    addItem(new Wall(4, this->getWidth() - 1 - 5));

    addItem(new Wall(6, this->getWidth() - 1 - 4));
    addItem(new Wall(6, this->getWidth() - 1 - 5));

    addItem(new Wall(1, this->getWidth() - 1 - 5));
    addItem(new Wall(2, this->getWidth() - 1 - 5));

    addItem(new Wall(8, this->getWidth() - 1 - 5));
    addItem(new Wall(9, this->getWidth() - 1 - 5));


}

int World::getHeight() const {
    return height;
}

void World::setHeight(int hg) {
    World::height = hg;
}

int World::getWidth() const {
    return width;
}

void World::setWidth(int wd) {
    World::width = wd;
}

EntityModel *World::getItem(const int &row, const int &col) {
    return world[row][col];
}

void World::addItem(EntityModel *item) {
    world[item->getRow()][item->getCol()] = item;
}
