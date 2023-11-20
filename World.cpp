//
// Created by Samuel on 16/11/2023.
//

#include "World.h"
#include "PacMan.h"
#include "AbstractFactory.h"


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
    world[row][col] = item;
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
        return this->createWall(row, col);
    }
    else if (tag == "PacMan"){
        return this->createPacMan(row, col);
    }
    return nullptr;
}

PacMan *AbstractFactory::createPacMan(const int &row, const int &col) {
    auto* entity = new PacMan(row, col, world);
    entity->setCameraX(world->getCamera()->getCameraCoords(row, col).second);
    entity->setCameraY(world->getCamera()->getCameraCoords(row, col).first);
    world->addItem(entity);
    world->setPacMan(entity);
    return entity;
}

Wall *AbstractFactory::createWall(const int &row, const int &col) {
    auto entity = new Wall(row, col);
    entity->setCameraX(world->getCamera()->getCameraCoords(row, col).second);
    entity->setCameraY(world->getCamera()->getCameraCoords(row, col).first);
    world->addItem(entity);
    return entity;
}

void PacMan::move(const int &ticks) {
    if (this->getCurrentDirection() == "UP"){
        double yCoord = this->getCameraY();
        yCoord -= ticks * this->getYSpeed();
        // Als volgende direction naar rechts is en hij kan naar rechts:
        if (this->getNextDirection() == "RIGHT" and world->getItem(this->getRow(), this->getCol() + 1) == nullptr){
            double wallYCoord = world->getCamera()->getCameraCoords(this->getRow(), this->getCol()).first;
            if (yCoord < wallYCoord){
                this->setCameraY(wallYCoord);
                // 1 Tick naar rechts gaan als hij om de hoek is en de richtingen aanpassen
                this->setCameraX(this->getCameraX() + this->getXSpeed());
                this->setCurrentDirection("RIGHT");
                this->setNextDirection("NONE");
            }
            else{
                this->setCameraY(yCoord);
            }
        }

        // Als volgende direction naar links is en hij kan naar links:
        else if (this->getNextDirection() == "LEFT" and world->getItem(this->getRow(), this->getCol() - 1) == nullptr){
            double wallYCoord = world->getCamera()->getCameraCoords(this->getRow(), this->getCol()).first;
            if (yCoord < wallYCoord){
                this->setCameraY(wallYCoord);
                // 1 Tick naar links gaan als hij om de hoek is en de richtingen aanpassen
                this->setCameraX(this->getCameraX() - this->getXSpeed());
                this->setCurrentDirection("LEFT");
                this->setNextDirection("NONE");
            }
            else{
                this->setCameraY(yCoord);
            }
        }

        // Als de volgende tile een muur is:
        else if (world->getItem(this->getRow() - 1, this->getCol()) != nullptr and world->getItem(this->getRow() - 1, this->getCol())->getTag() == "Wall"){
            double wallYCoord = world->getCamera()->getCameraCoords(this->getRow(), this->getCol()).first;
            if (yCoord < wallYCoord){
                this->setCameraY(wallYCoord);
            }
            else{
                this->setCameraY(yCoord);
            }
        }

        // Checken of hij dichter bij een ander vakje staat dan het huidige
        else if (abs(world->getCamera()->getCameraCoords(this->getRow() - 1, this->getCol()).first - yCoord) <
                 abs(world->getCamera()->getCameraCoords(this->getRow(), this->getCol()).first - yCoord)){
            // Als het volgende vakje geen muur is: gaan
            auto nextItem = world->getItem(this->getRow() - 1, this->getCol());
            if (nextItem == nullptr){
                this->setCameraY(yCoord);
                world->setItem(nullptr, this->getRow(), this->getCol());
                world->setItem(this, this->getRow() - 1, this->getCol());
                this->setRow(this->getRow() - 1);
            }
        }else{
            this->setCameraY(yCoord);
        }
    }
    else if (this->getCurrentDirection() == "DOWN"){
        double yCoord = this->getCameraY();
        yCoord += ticks * this->getYSpeed();
        // Als volgende direction naar rechts is en hij kan naar rechts:
        if (this->getNextDirection() == "RIGHT" and world->getItem(this->getRow(), this->getCol() + 1) == nullptr){
            double wallYCoord = world->getCamera()->getCameraCoords(this->getRow(), this->getCol()).first;
            if (yCoord > wallYCoord){
                this->setCameraY(wallYCoord);
                // 1 Tick naar rechts gaan als hij om de hoek is en de richtingen aanpassen
                this->setCameraX(this->getCameraX() + this->getXSpeed());
                this->setCurrentDirection("RIGHT");
                this->setNextDirection("NONE");
            }
            else{
                this->setCameraY(yCoord);
            }
        }
        // Als volgende direction naar links is en hij kan naar links:
        else if (this->getNextDirection() == "LEFT" and world->getItem(this->getRow(), this->getCol() - 1) == nullptr){
            double wallYCoord = world->getCamera()->getCameraCoords(this->getRow(), this->getCol()).first;
            if (yCoord > wallYCoord){
                this->setCameraY(wallYCoord);
                // 1 Tick naar links gaan als hij om de hoek is en de richtingen aanpassen
                this->setCameraX(this->getCameraX() - this->getXSpeed());
                this->setCurrentDirection("LEFT");
                this->setNextDirection("NONE");
            }
            else{
                this->setCameraY(yCoord);
            }
        }
        // Als de volgende tile een muur is:
        else if (world->getItem(this->getRow() + 1, this->getCol()) != nullptr and world->getItem(this->getRow() + 1, this->getCol())->getTag() == "Wall"){
            double wallYCoord = world->getCamera()->getCameraCoords(this->getRow(), this->getCol()).first;
            if (yCoord > wallYCoord){
                this->setCameraY(wallYCoord);
            }
            else{
                this->setCameraY(yCoord);
            }
        }
            // Checken of hij dichter bij een ander vakje staat dan het huidige
        else if (abs(world->getCamera()->getCameraCoords(this->getRow() + 1, this->getCol()).first - yCoord) <
                 abs(world->getCamera()->getCameraCoords(this->getRow(), this->getCol()).first - yCoord)){
            // Als het volgende vakje geen muur is: gaan
            auto nextItem = world->getItem(this->getRow() + 1, this->getCol());
            if (nextItem == nullptr){
                this->setCameraY(yCoord);
                world->setItem(nullptr, this->getRow(), this->getCol());
                world->setItem(this, this->getRow() + 1, this->getCol());
                this->setRow(this->getRow() + 1);
            }
        }
        else{
            this->setCameraY(yCoord);
        }
    }
    else if (this->getCurrentDirection() == "RIGHT"){
        double xCoord = this->getCameraX();
        xCoord += ticks * this->getXSpeed();
        // Als volgende direction naar links is en hij kan naar links:
        if (this->getNextDirection() == "UP" and world->getItem(this->getRow() - 1, this->getCol()) == nullptr){
            double wallXCoord = world->getCamera()->getCameraCoords(this->getRow(), this->getCol()).second;
            if (xCoord > wallXCoord){
                this->setCameraX(wallXCoord);
                // 1 Tick naar links gaan als hij om de hoek is en de richtingen aanpassen
                this->setCameraY(this->getCameraY() - this->getYSpeed());
                this->setCurrentDirection("UP");
                this->setNextDirection("NONE");
            }
            else{
                this->setCameraX(xCoord);
            }
        }
        else if (this->getNextDirection() == "DOWN" and world->getItem(this->getRow() + 1, this->getCol()) == nullptr){
            double wallXCoord = world->getCamera()->getCameraCoords(this->getRow(), this->getCol()).second;
            if (xCoord > wallXCoord){
                this->setCameraX(wallXCoord);
                // 1 Tick naar links gaan als hij om de hoek is en de richtingen aanpassen
                this->setCameraY(this->getCameraY() + this->getYSpeed());
                this->setCurrentDirection("DOWN");
                this->setNextDirection("NONE");
            }
            else{
                this->setCameraX(xCoord);
            }
        }
        // Als de volgende tile een muur is:
        else if (world->getItem(this->getRow(), this->getCol() + 1) != nullptr and world->getItem(this->getRow(), this->getCol() + 1)->getTag() == "Wall"){
            double wallXCoord = world->getCamera()->getCameraCoords(this->getRow(), this->getCol()).second;
            if (xCoord > wallXCoord){
                this->setCameraX(wallXCoord);
            }
            else{
                this->setCameraX(xCoord);
            }
        }
            // Checken of hij dichter bij een ander vakje staat dan het huidige
        else if (abs(world->getCamera()->getCameraCoords(this->getRow(), this->getCol() + 1).second - xCoord) <
                 abs(world->getCamera()->getCameraCoords(this->getRow(), this->getCol()).second - xCoord)){
            // Als het volgende vakje geen muur is: gaan
            auto nextItem = world->getItem(this->getRow(), this->getCol() + 1);
            if (nextItem == nullptr){
                this->setCameraX(xCoord);
                world->setItem(nullptr, this->getRow(), this->getCol());
                world->setItem(this, this->getRow(), this->getCol() + 1);
                this->setCol(this->getCol() + 1);
            }
        }else{
            this->setCameraX(xCoord);
        }
    }
    else if (this->getCurrentDirection() == "LEFT"){
        double xCoord = this->getCameraX();
        xCoord -= ticks * this->getXSpeed();
        // Als volgende direction naar links is en hij kan naar links:
        if (this->getNextDirection() == "UP" and world->getItem(this->getRow() - 1, this->getCol()) == nullptr){
            double wallXCoord = world->getCamera()->getCameraCoords(this->getRow(), this->getCol()).second;
            if (xCoord < wallXCoord){
                this->setCameraX(wallXCoord);
                // 1 Tick naar links gaan als hij om de hoek is en de richtingen aanpassen
                this->setCameraY(this->getCameraY() - this->getYSpeed());
                this->setCurrentDirection("UP");
                this->setNextDirection("NONE");
            }
            else{
                this->setCameraX(xCoord);
            }
        }
        else if (this->getNextDirection() == "DOWN" and world->getItem(this->getRow() + 1, this->getCol()) == nullptr){
            double wallXCoord = world->getCamera()->getCameraCoords(this->getRow(), this->getCol()).second;
            if (xCoord < wallXCoord){
                this->setCameraX(wallXCoord);
                // 1 Tick naar links gaan als hij om de hoek is en de richtingen aanpassen
                this->setCameraY(this->getCameraY() + this->getYSpeed());
                this->setCurrentDirection("DOWN");
                this->setNextDirection("NONE");
            }
            else{
                this->setCameraX(xCoord);
            }
        }
        // Als de volgende tile een muur is:
        else if (world->getItem(this->getRow(), this->getCol() - 1) != nullptr and world->getItem(this->getRow(), this->getCol() - 1)->getTag() == "Wall"){
            double wallXCoord = world->getCamera()->getCameraCoords(this->getRow(), this->getCol()).second;
            if (xCoord < wallXCoord){
                this->setCameraX(wallXCoord);
            }
            else{
                this->setCameraX(xCoord);
            }
        }
            // Checken of hij dichter bij een ander vakje staat dan het huidige
        else if (abs(world->getCamera()->getCameraCoords(this->getRow(), this->getCol() - 1).second - xCoord) <
                 abs(world->getCamera()->getCameraCoords(this->getRow(), this->getCol()).second - xCoord)){
            // Als het volgende vakje geen muur is: gaan
            auto nextItem = world->getItem(this->getRow(), this->getCol() - 1);
            if (nextItem == nullptr){
                this->setCameraX(xCoord);
                world->setItem(nullptr, this->getRow(), this->getCol());
                world->setItem(this, this->getRow(), this->getCol() - 1);
                this->setCol(this->getCol() - 1);
            }
        }else{
            this->setCameraX(xCoord);
        }
    }
    else{
        assert(this->getCurrentDirection() == "NONE");
    }

}

PacMan::PacMan(int row, int col, World *world) : EntityModel(row, col), world(world) {
    this->setCurrentDirection("NONE");
    this->setNextDirection("NONE");
    xSpeed = double(1) / this->getWorld()->getWidth() / 8;
    ySpeed = double(1) / this->getWorld()->getHeight() / 8;
    this->setTag("PacMan");
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

const string &PacMan::getNextDirection() const {
    return nextDirection;
}

void PacMan::setNextDirection(const string &direction) {
    PacMan::nextDirection = direction;
}
/*
 * Verandert de richting afhankelijk van de volgende richting
 */
void PacMan::moveDirection(const string &direction) {
    if (this->getCurrentDirection() == "NONE"){
        this->setCurrentDirection(direction);
    }
    else if (direction == "UP"){
        if (this->getCurrentDirection() == "DOWN"){
            setCurrentDirection("UP");
            setNextDirection("NONE");
        }
        else if (this->getCurrentDirection() == "LEFT" or this->getCurrentDirection() == "RIGHT"){
            setNextDirection("UP");
        }
    }
    else if (direction == "LEFT"){
        if (this->getCurrentDirection() == "RIGHT"){
            setCurrentDirection("LEFT");
            setNextDirection("NONE");
        }
        else if (this->getCurrentDirection() == "UP" or this->getCurrentDirection() == "DOWN"){
            setNextDirection("LEFT");
        }
    }
    else if (direction == "RIGHT"){
        if (this->getCurrentDirection() == "LEFT"){
            setCurrentDirection("RIGHT");
            setNextDirection("NONE");
        }
        else if (this->getCurrentDirection() == "UP" or this->getCurrentDirection() == "DOWN"){
            setNextDirection("RIGHT");
        }
    }
    else if (direction == "DOWN"){
        if (this->getCurrentDirection() == "UP"){
            setCurrentDirection("DOWN");
            setNextDirection("NONE");
        }
        else if (this->getCurrentDirection() == "LEFT" or this->getCurrentDirection() == "RIGHT"){
            setNextDirection("DOWN");
        }
    }
}
