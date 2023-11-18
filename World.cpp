//
// Created by Samuel on 16/11/2023.
//

#include "World.h"

World::World() {
    width = 20;
    height = 11;
    factory = nullptr;
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
    entities.push_back(item);
}

AbstractFactory *World::getFactory() const {
    return factory;
}

void World::setFactory(AbstractFactory *fac) {
    World::factory = fac;
}

void World::buildWorld() {
    assert(this->getFactory() != nullptr);
    // Lege map met null-pointers maken:
    for (auto & i : world){
        for (auto & j : i){
            j = nullptr;
        }
    }
    // Muren om level heen
    for (int i = 0; i < width; ++i){
        this->getFactory()->createEntity("Wall", 0, i);
        this->getFactory()->createEntity("Wall", height - 1, i);
    }
    for (int i = 0; i < height; ++i){
        this->getFactory()->createEntity("Wall", i, 0);
        this->getFactory()->createEntity("Wall", i, width - 1);
    }

    // Links muren:
    this->getFactory()->createEntity("Wall", 2, 2);
    this->getFactory()->createEntity("Wall", 2, 3);
    this->getFactory()->createEntity("Wall", 3, 2);
    this->getFactory()->createEntity("Wall", 4, 2);

    this->getFactory()->createEntity("Wall", 6, 2);
    this->getFactory()->createEntity("Wall", 7, 2);
    this->getFactory()->createEntity("Wall", 8, 2);
    this->getFactory()->createEntity("Wall", 8, 3);

    this->getFactory()->createEntity("Wall", 4, 4);
    this->getFactory()->createEntity("Wall", 4, 5);

    this->getFactory()->createEntity("Wall", 6, 4);
    this->getFactory()->createEntity("Wall", 6, 5);

    this->getFactory()->createEntity("Wall", 1, 5);
    this->getFactory()->createEntity("Wall", 2, 5);

    this->getFactory()->createEntity("Wall", 8, 5);
    this->getFactory()->createEntity("Wall", 9, 5);

    for (int i = 7; i < 13; ++i){
        this->getFactory()->createEntity("Wall", 2, i);
        this->getFactory()->createEntity("Wall", 6, i);
        this->getFactory()->createEntity("Wall", 8, i);
    }

    this->getFactory()->createEntity("Wall", 5, 7);
    this->getFactory()->createEntity("Wall", 5, 12);

    this->getFactory()->createEntity("Wall", 4, 7);
    this->getFactory()->createEntity("Wall", 4, 8);
    this->getFactory()->createEntity("Wall", 4, 11);
    this->getFactory()->createEntity("Wall", 4, 12);

    // Rechts
    this->getFactory()->createEntity("Wall", 2, this->getWidth() - 1 - 2);
    this->getFactory()->createEntity("Wall", 2, this->getWidth() - 1 - 3);
    this->getFactory()->createEntity("Wall", 3, this->getWidth() - 1 - 2);
    this->getFactory()->createEntity("Wall", 4, this->getWidth() - 1 - 2);

    this->getFactory()->createEntity("Wall", 6, this->getWidth() - 1 - 2);
    this->getFactory()->createEntity("Wall", 7, this->getWidth() - 1 - 2);
    this->getFactory()->createEntity("Wall", 8, this->getWidth() - 1 - 2);
    this->getFactory()->createEntity("Wall", 8, this->getWidth() - 1 - 3);

    this->getFactory()->createEntity("Wall", 4, this->getWidth() - 1 - 4);
    this->getFactory()->createEntity("Wall", 4, this->getWidth() - 1 - 5);

    this->getFactory()->createEntity("Wall", 6, this->getWidth() - 1 - 4);
    this->getFactory()->createEntity("Wall", 6, this->getWidth() - 1 - 5);

    this->getFactory()->createEntity("Wall", 1, this->getWidth() - 1 - 5);
    this->getFactory()->createEntity("Wall", 2, this->getWidth() - 1 - 5);

    this->getFactory()->createEntity("Wall", 8, this->getWidth() - 1 - 5);
    this->getFactory()->createEntity("Wall", 9, this->getWidth() - 1 - 5);
}

World::~World() {
    int entitySize = int(entities.size());
    for (int i = 0; i < entitySize; ++i){
        delete entities[i];
    }
}

AbstractFactory::AbstractFactory(World *world) : world(world) {}

EntityModel *AbstractFactory::createEntity(const string &tag, const int &row, const int &col) {
    if (tag == "Wall"){
        auto entity = new Wall(row, col);
        world->addItem(entity);
        return entity;
    }
    return nullptr;
}