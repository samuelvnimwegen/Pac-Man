//
// Created by Samuel on 16/11/2023.
//

#include "World.h"

using namespace std;

Model::World::World() {
    width = 20;
    height = 11;
    factory = nullptr;
    coinsLeft = 0;
    pacMan = nullptr;
}

int Model::World::getHeight() const {
    return height;
}

void Model::World::setHeight(int hg) {
    World::height = hg;
}

int Model::World::getWidth() const {
    return width;
}

void Model::World::setWidth(int wd) {
    World::width = wd;
}

Model::EntityModel *Model::World::getItem(const int &row, const int &col) {
    return world[row][col];
}

void Model::World::addItem(EntityModel *item) {
    world[item->getRow()][item->getCol()] = item;
}

Model::AbstractFactory *Model::World::getFactory() const {
    return factory;
}

void Model::World::setFactory(AbstractFactory *fac) {
    World::factory = fac;
}

void Model::World::buildWorld() {
    assert(this->getFactory() != nullptr);
    // Lege map met null-pointers maken:
    for (int i = 0; i < this->getHeight(); ++i){
        vector<EntityModel*> row;
        for (int j = 0; j < this->getWidth(); ++j){
            row.push_back(nullptr);
        }
        this->world.push_back(row);
    }

    // Muren om level heen
    for (int i = 0; i < this->getWidth(); ++i){
        this->getFactory()->createWall(0, i);
        this->getFactory()->createWall(this->getHeight() - 1, i);
    }
    for (int i = 0; i < this->getHeight(); ++i){
        this->getFactory()->createWall(i, 0);
        this->getFactory()->createWall(i, this->getWidth() - 1);
    }

    // Links muren:
    this->getFactory()->createWall(2, 2);
    this->getFactory()->createWall(2, 3);
    this->getFactory()->createWall(3, 2);
    this->getFactory()->createWall(4, 2);

    this->getFactory()->createWall(6, 2);
    this->getFactory()->createWall(7, 2);
    this->getFactory()->createWall(8, 2);
    this->getFactory()->createWall(8, 3);

    this->getFactory()->createWall(4, 4);
    this->getFactory()->createWall(4, 5);

    this->getFactory()->createWall(6, 4);
    this->getFactory()->createWall(6, 5);

    this->getFactory()->createWall(1, 5);
    this->getFactory()->createWall(2, 5);

    this->getFactory()->createWall(8, 5);
    this->getFactory()->createWall(9, 5);

    for (int i = 7; i < 13; ++i){
        this->getFactory()->createWall(2, i);
        this->getFactory()->createWall(6, i);
        this->getFactory()->createWall(8, i);
    }

    this->getFactory()->createWall(5, 7);
    this->getFactory()->createWall(5, 12);

    this->getFactory()->createWall(4, 7);
    this->getFactory()->createWall(4, 8);
    this->getFactory()->createWall(4, 11);
    this->getFactory()->createWall(4, 12);

    // Rechts
    this->getFactory()->createWall(2, this->getWidth() - 1 - 2);
    this->getFactory()->createWall(2, this->getWidth() - 1 - 3);
    this->getFactory()->createWall(3, this->getWidth() - 1 - 2);
    this->getFactory()->createWall(4, this->getWidth() - 1 - 2);

    this->getFactory()->createWall(6, this->getWidth() - 1 - 2);
    this->getFactory()->createWall(7, this->getWidth() - 1 - 2);
    this->getFactory()->createWall(8, this->getWidth() - 1 - 2);
    this->getFactory()->createWall(8, this->getWidth() - 1 - 3);

    this->getFactory()->createWall(4, this->getWidth() - 1 - 4);
    this->getFactory()->createWall(4, this->getWidth() - 1 - 5);

    this->getFactory()->createWall(6, this->getWidth() - 1 - 4);
    this->getFactory()->createWall(6, this->getWidth() - 1 - 5);

    this->getFactory()->createWall(1, this->getWidth() - 1 - 5);
    this->getFactory()->createWall(2, this->getWidth() - 1 - 5);

    this->getFactory()->createWall(8, this->getWidth() - 1 - 5);
    this->getFactory()->createWall(9, this->getWidth() - 1 - 5);

    this->getFactory()->createPacMan(1, 1);

    this->getFactory()->createGhost(5, 9);

    for (int i = 0; i < this->getHeight(); ++i){
        for (int j = 0; j < this->getWidth(); ++j){
            if (this->getItem(i, j) == nullptr){
                this->getFactory()->createCoin(i, j);
                this->setCoinsLeft(this->getCoinsLeft() + 1);
            }
        }
    }

}

Model::World::~World() {

}

Model::PacMan *Model::World::getPacMan() const {
    return pacMan;
}

void Model::World::setPacMan(PacMan *pMan) {
    World::pacMan = pMan;
}

void Model::World::setItem(EntityModel* item, const int &row, const int &col) {
    world[row][col] = item;
}

int Model::World::getCoinsLeft() const {
    return coinsLeft;
}

void Model::World::setCoinsLeft(int coins) {
    World::coinsLeft = coins;
}

const vector<Model::Ghost *> &Model::World::getGhosts() const {
    return ghosts;
}

void Model::World::setGhosts(const vector<Ghost *> &ghostVector) {
    World::ghosts = ghostVector;
}

void Model::World::die() const {
    this->getPacMan()->die();
    for (auto ghost: this->getGhosts()){
        ghost->reset();
    }
}

const vector<std::vector<Model::EntityModel *>> &Model::World::getWorld() const {
    return world;
}

const vector<Model::Coin *> &Model::World::getCoins() const {
    return coins;
}

const vector<Model::Wall *> &Model::World::getWalls() const {
    return walls;
}

void Model::World::addWall(Model::Wall *&wall) {
    auto newWalls = this->getWalls();
    newWalls.push_back(wall);
    this->setWalls(newWalls);
}

void Model::World::setWorld(const vector<std::vector<Model::EntityModel *>> &newWorld) {
    World::world = newWorld;
}

void Model::World::setCoins(const vector<Coin *> &coinVector) {
    World::coins = coinVector;
}

void Model::World::setWalls(const vector<Wall *> &wallVector) {
    World::walls = wallVector;
}

void Model::World::addCoin(Model::Coin *&coin) {
    auto coinVector = this->getCoins();
    coinVector.push_back(coin);
    this->setCoins(coinVector);
}

void Model::World::addGhost(Model::Ghost *ghost) {
    auto ghostVector = this->getGhosts();
    ghostVector.push_back(ghost);
    this->setGhosts(ghostVector);
    if (ghosts.size() == 1){
        ghost->setColor(color::red);
    }else if (ghosts.size() == 2){
        ghost->setColor(color::pink);
    }else if (ghosts.size() == 3){
        ghost->setColor(color::blue);
    }else{
        ghost->setColor(color::orange);
    }
}

Model::AbstractFactory::AbstractFactory(World *world) : world(world) {}



Model::World *Model::AbstractFactory::getWorld() const {
    return world;
}

void Model::AbstractFactory::setWorld(Model::World *newWorld) {
    AbstractFactory::world = newWorld;
}



Model::PacMan::PacMan(int row, int col, Model::World *world) : EntityModel(row, col), world(world) {
    this->setCurrentDirection(direction::none);
    this->setNextDirection(direction::none);
    xSpeed = double(1) / this->getWorld()->getWidth() / 100;
    ySpeed = double(1) / this->getWorld()->getHeight() / 100;
    this->setTag("PacMan");
    hasMoved = false;
    score = 0;
    startRow = row;
    startCol = col;
    currentDirection = direction::none;
    nextDirection = direction::none;
}


/*
 * Verandert de richting afhankelijk van de volgende richting
 */
void Model::PacMan::moveDirection(const direction &dir) {
    if (this->getCurrentDirection() == direction::none){
        this->setCurrentDirection(dir);
    }
    else if (dir == direction::up){
        if (this->getCurrentDirection() == direction::down){
            setCurrentDirection(direction::up);
            setNextDirection(direction::none);
        }
        else if (this->getCurrentDirection() == direction::left or this->getCurrentDirection() == direction::right){
            setNextDirection(direction::up);
        }
    }
    else if (dir == direction::left){
        if (this->getCurrentDirection() == direction::right){
            setCurrentDirection(direction::left);
            setNextDirection(direction::none);
        }
        else if (this->getCurrentDirection() == direction::up or this->getCurrentDirection() == direction::down){
            setNextDirection(direction::left);
        }
    }
    else if (dir == direction::right){
        if (this->getCurrentDirection() == direction::left){
            setCurrentDirection(direction::right);
            setNextDirection(direction::none);
        }
        else if (this->getCurrentDirection() == direction::up or this->getCurrentDirection() == direction::down){
            setNextDirection(direction::right);
        }
    }
    else if (dir == direction::down){
        if (this->getCurrentDirection() == direction::up){
            setCurrentDirection(direction::down);
            setNextDirection(direction::none);
        }
        else if (this->getCurrentDirection() == direction::left or this->getCurrentDirection() == direction::right){
            setNextDirection(direction::down);
        }
    }
}



bool Model::PacMan::canMove(const int &row, const int &col) const {
    if (this->getWorld()->getItem(row, col) == nullptr or this->getWorld()->getItem(row, col)->getTag() == "Coin" or this->getWorld()->getItem(row, col)->getTag() == "Ghost"){
        return true;
    }
    return false;
}

void Model::PacMan::removePrevious(const int &row, const int &col) {
    if (this->getWorld()->getItem(row, col) == nullptr){
        return;
    }
    else if (this->getWorld()->getItem(row, col)->getTag() == "Coin"){
        this->setScore(this->getScore() + 10);
        this->getWorld()->getItem(row, col)->consume();
        this->getWorld()->setCoinsLeft(this->getWorld()->getCoinsLeft() - 1);
    }
}



void Model::PacMan::die() {
    this->getWorld()->setItem(nullptr, getRow(), getCol());
    this->getWorld()->setItem(this->getWorld()->getPacMan(), getStartRow(), getStartCol());
    this->setHasMoved(false);
    this->setCurrentDirection(direction::none);
    this->setNextDirection(direction::none);
    this->setCol(getStartCol());
    this->setRow(getStartRow());
}



int Model::Ghost::getManhattanDistance(const direction &direction) {
    int pacManRow = this->getWorld()->getPacMan()->getRow();
    int pacManCol = this->getWorld()->getPacMan()->getCol();
    if (direction == direction::up){
        return abs(this->getRow() - 1 - pacManRow) + abs(this->getCol() - pacManCol);
    }
    else if (direction == direction::down){
        return abs(this->getRow() + 1 - pacManRow) + abs(this->getCol() - pacManCol);
    }
    else if (direction == direction::left){
        return abs(this->getRow() - pacManRow) + abs(this->getCol() - 1 - pacManCol);
    }
    else {
        assert(direction == direction::right);
        return abs(this->getRow() - pacManRow) + abs(this->getCol() + 1 - pacManCol);
    }
}

bool Model::Ghost::canMove(const int &row, const int &col) const {
    if (this->getWorld()->getItem(row, col) == nullptr or this->getWorld()->getItem(row, col)->getTag() == "Coin" or this->getWorld()->getItem(row, col)->getTag() == "PacMan"){
        return true;
    }
    return false;
}

Model::Ghost::Ghost(int row, int col, Model::World *world) : EntityModel(row, col), world(world) {
    this->setTag("Ghost");
    currentDirection = direction::up;
    currentState = "WAITING";
    justTurned = true;
    startRow = row;
    startCol = col;
    ghostColor = color::blue;
    nextDirection = direction::none;
}

void Model::Ghost::move(const int &steps) {
    this->getObservers().at(0)->move(steps);
}






