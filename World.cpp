//
// Created by Samuel on 16/11/2023.
//

#include "World.h"

World::World() {
    width = 20;
    height = 11;
    factory = nullptr;
    camera = new Camera(width, height);
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

    this->getFactory()->createEntity("PacMan", 1, 1);
}

World::~World() {
    int entitySize = int(entities.size());
    for (int i = 0; i < entitySize; ++i){
        delete entities[i];
    }
}

PacMan *World::getPacMan() const {
    return pacMan;
}

void World::setPacMan(PacMan *pMan) {
    World::pacMan = pMan;
}

void World::setItem(EntityModel* item, const int &row, const int &col) {
    world[col][row] = item;
}

const vector<EntityModel *> &World::getEntities() const {
    return entities;
}

void World::setEntities(const vector<EntityModel *> &ent) {
    World::entities = ent;
}

Camera *World::getCamera() const {
    return camera;
}

void World::setCamera(Camera *cam) {
    World::camera = cam;
}

AbstractFactory::AbstractFactory(World *world) : world(world) {}

EntityModel *AbstractFactory::createEntity(const string &tag, const int &row, const int &col) {
    if (tag == "Wall"){
        auto entity = new Wall(row, col);
        entity->setCameraX(world->getCamera()->getCameraCoords(row, col).second);
        entity->setCameraY(world->getCamera()->getCameraCoords(row, col).first);
        world->addItem(entity);
        return entity;
    }
    else if (tag == "PacMan"){
        auto* entity = new PacMan(row, col, world);
        entity->setCameraX(world->getCamera()->getCameraCoords(row, col).second);
        entity->setCameraY(world->getCamera()->getCameraCoords(row, col).first);
        world->addItem(entity);
        world->setPacMan(entity);
        return entity;
    }
    return nullptr;
}

void PacMan::move(const int &ticks) {
    if (this->getCurrentDirection() == "UP"){
        double yCoord = this->getCameraY();
        yCoord -= ticks * this->getYSpeed();
        this->setCameraY(yCoord);
        // Checken of hij dichter bij een ander vakje staat dan het huidige
        if (abs(world->getCamera()->getCameraCoords(this->getRow() - 1, this->getCol()).first - this->getCameraY()) <
                abs(world->getCamera()->getCameraCoords(this->getRow(), this->getCol()).first - this->getCameraY())){
            world->setItem(nullptr, this->getRow(), this->getCol());
            world->setItem(this, this->getRow() - 1, this->getCol());
        }
    }else if (this->getCurrentDirection() == "DOWN"){
        double yCoord = this->getCameraY();
        yCoord += ticks * this->getYSpeed();
        this->setCameraY(yCoord);
        // Checken of hij dichter bij een ander vakje staat dan het huidige
        if (abs(world->getCamera()->getCameraCoords(this->getRow() + 1, this->getCol()).first - this->getCameraY()) <
            abs(world->getCamera()->getCameraCoords(this->getRow(), this->getCol()).first - this->getCameraY())){
            world->setItem(nullptr, this->getRow(), this->getCol());
            world->setItem(this, this->getRow() + 1, this->getCol());
        }
    }
    else if (this->getCurrentDirection() == "RIGHT"){
        double xCoord = this->getCameraX();
        xCoord += ticks * this->getXSpeed();
        this->setCameraX(xCoord);
        // Checken of hij dichter bij een ander vakje staat dan het huidige
        if (abs(world->getCamera()->getCameraCoords(this->getRow(), this->getCol() + 1).second - this->getCameraX()) <
            abs(world->getCamera()->getCameraCoords(this->getRow(), this->getCol()).second - this->getCameraX())){
            world->setItem(nullptr, this->getRow(), this->getCol());
            world->setItem(this, this->getRow(), this->getCol() + 1);
        }
    }
    else if (this->getCurrentDirection() == "LEFT"){
        double xCoord = this->getCameraX();
        xCoord -= ticks * this->getXSpeed();
        this->setCameraX(xCoord);
        // Checken of hij dichter bij een ander vakje staat dan het huidige
        if (abs(world->getCamera()->getCameraCoords(this->getRow(), this->getCol() - 1).second - this->getCameraX()) <
            abs(world->getCamera()->getCameraCoords(this->getRow(), this->getCol()).second - this->getCameraX())){
            world->setItem(nullptr, this->getRow(), this->getCol());
            world->setItem(this, this->getRow(), this->getCol() - 1);
        }
    }
    else{
        assert(this->getCurrentDirection() == "NONE");
    }
}

PacMan::PacMan(int row, int col, World *world) : EntityModel(row, col), world(world) {
    this->setCurrentDirection("NONE");
    xSpeed = double(1) / this->getWorld()->getWidth() / 11;
    ySpeed = double(1) / this->getWorld()->getHeight() / 11;
}

double PacMan::getXSpeed() const {
    return xSpeed;
}

void PacMan::setXSpeed(double speed) {
    PacMan::xSpeed = speed;
}

double PacMan::getYSpeed() const {
    return ySpeed;
}

void PacMan::setYSpeed(double speed) {
    PacMan::ySpeed = speed;
}
