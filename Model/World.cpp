//
// Created by Samuel on 16/11/2023.
//

#include "World.h"
#include "Ghost.h"

#include <memory>
#include <utility>
#include "cmath"
#include "algorithm"
using namespace std;

Model::World::World() {
    levelNr = 0;
    gameStarted = false;
    width = 20;
    height = 11;
    factory = nullptr;
    pacMan = nullptr;
    score = nullptr;
}

int Model::World::getHeight() const {
    return height;
}


int Model::World::getWidth() const {
    return width;
}

std::shared_ptr<Model::EntityModel> Model::World::getItem(const int &row, const int &col) {
    return world[row][col];
}

void Model::World::addItem(const std::shared_ptr<Model::EntityModel>& item) {
    if (item){
        world[toTile(item->getY())][toTile(item->getX())] = item;
    }

}

std::shared_ptr<Model::AbstractFactory> Model::World::getFactory() const {
    return factory;
}

void Model::World::setFactory(std::shared_ptr<AbstractFactory> fac) {
    World::factory = std::move(fac);
}

void Model::World::buildWorld() {
    assert(this->getFactory() != nullptr);
    // Lege map met null-pointers maken:
    for (int i = 0; i < this->getHeight(); ++i){
        vector<std::shared_ptr<Model::EntityModel>> row;
        row.reserve(this->getWidth());
        for (int j = 0; j < this->getWidth(); ++j){
            row.push_back(nullptr);
        }
        this->world.push_back(row);
    }
    // Map voor collectables maken
    for (int i = 0; i < this->getHeight(); ++i){
        vector<std::shared_ptr<Model::Collectable>> row;
        row.reserve(this->getWidth());
        for (int j = 0; j < this->getWidth(); ++j){
            row.push_back(nullptr);
        }
        this->collectableWorld.push_back(row);
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

    this->getFactory()->createPacMan(9, 9);

    this->getFactory()->createGhost(5, 8);
    this->getFactory()->createGhost(5, 9);
    this->getFactory()->createGhost(5, 10);
    this->getFactory()->createGhost(5, 11);

    this->getFactory()->createFruit(1, 1);
    this->getFactory()->createFruit(9, 18);

    vector<pair<int, int>> illegalPairs = {{5, 8}, {5, 9}, {5, 10}, {5, 11}, {4, 9}, {4, 10}};
    for (int i = 0; i < this->getHeight(); ++i){
        for (int j = 0; j < this->getWidth(); ++j){
            if (this->getItem(i, j) == nullptr and !(this->getPacMan()->getX() == j and this->getPacMan()->getY() == i)
            and !std::count(illegalPairs.begin(), illegalPairs.end(), make_pair(i, j))){
                this->getFactory()->createCoin(i, j);
            }
        }
    }

}

Model::World::~World() = default;


void Model::World::restart() {
    this->getPacMan()->reset();
    for (const auto& ghost: this->getGhosts()){
        ghost->reset();
    }
    setGameStarted(false);
}


void Model::World::addWall(const std::shared_ptr<Model::Wall> &wall) {
    auto newWalls = this->getWalls();
    newWalls.push_back(wall);
    this->setWalls(newWalls);
}


void Model::World::addCoin(const std::shared_ptr<Model::Coin> &coin) {
    auto coinVector = this->getCoins();
    coinVector.push_back(coin);
    collectableWorld.at(toTile(coin->getY())).at(toTile(coin->getX())) = coin;
    this->setCoins(coinVector);
}

void Model::World::addFruit(const shared_ptr<Model::Fruit> &fruit) {
    auto fruitVector = this->getFruits();
    fruitVector.push_back(fruit);
    collectableWorld.at(toTile(fruit->getY())).at(toTile(fruit->getX())) = fruit;
    this->setFruits(fruitVector);
}

void Model::World::addGhost(const std::shared_ptr<Model::Ghost>& ghost) {
    auto ghostVector = this->getGhosts();
    ghostVector.push_back(ghost);
    this->setGhosts(ghostVector);
}


const shared_ptr<Model::PacMan> &Model::World::getPacMan() const {
    return pacMan;
}

void Model::World::setPacMan(const shared_ptr<Model::PacMan> &newPacMan) {
    World::pacMan = newPacMan;
}

const vector<std::shared_ptr<Model::Coin>> &Model::World::getCoins() const {
    return coins;
}

void Model::World::setCoins(const vector<std::shared_ptr<Coin>> &newCoins) {
    World::coins = newCoins;
}

const vector<std::shared_ptr<Model::Ghost>> &Model::World::getGhosts() const {
    return ghosts;
}

void Model::World::setGhosts(const vector<std::shared_ptr<Ghost>> &newGhosts) {
    World::ghosts = newGhosts;
}

const vector<std::shared_ptr<Model::Wall>> &Model::World::getWalls() const {
    return walls;
}

void Model::World::setWalls(const vector<std::shared_ptr<Wall>> &newWalls) {
    World::walls = newWalls;
}

void Model::World::update(const double &seconds) const {
    for (const auto& wall: this->getWalls()){
        wall->update(seconds);
    }
    for (const auto& coin: this->getCoins()){
        coin->update(seconds);
    }
    for (const auto& fruit: this->getFruits()){
        fruit->update(seconds);
    }
    // Ghosts alleen updaten als pacman leeft:
    if (!this->getPacMan()->isDead()){
        for (const auto& ghost: this->getGhosts()){
            ghost->update(seconds);
        }
    }

    this->getPacMan()->update(seconds);

    // Checken op collisions van ghosts en pacMans:
    for (const auto& ghost: this->getGhosts()){
        if (toTile(ghost->getX()) == toTile(this->getPacMan()->getX()) and toTile(ghost->getY()) == toTile(this->getPacMan()->getY())){
            // Als de ghost in chase modus staat, level restart
            if (ghost->getStateManager()->getCurrentTag() == ghostStateTag::chasing and !this->getPacMan()->isDead()){
                this->getPacMan()->die();
            }
        }
    }
}

bool Model::World::isGameStarted() const {
    return gameStarted;
}

void Model::World::setGameStarted(bool started) {
    World::gameStarted = started;
}

Model::AbstractFactory::AbstractFactory(const std::shared_ptr<Model::World>& world) : world(world) {}



std::shared_ptr<Model::World> Model::AbstractFactory::getWorld() const {
    return world.lock();
}


Model::PacMan::PacMan(int row, int col, const shared_ptr<World>& world) : EntityModel(row, col), world(world) {
    deathTime = 0;
    dead = false;
    this->setCurrentDirection(direction::none);
    this->setNextDirection(direction::none);
    speed = 5.0;
    this->setTag(pacMan);
    hasMoved = false;
    startRow = row;
    startCol = col;
    currentDirection = direction::none;
    nextDirection = direction::none;
}




bool Model::PacMan::canMove(const int &row, const int &col)  {
    if (this->getWorld()->getItem(row, col) == nullptr or this->getWorld()->getItem(row, col)->getTag() != wall){
        return true;
    }
    return false;
}





void Model::PacMan::reset() {
    this->setHasMoved(false);
    this->setCurrentDirection(direction::none);
    this->setNextDirection(direction::none);
    this->setX(getStartCol());
    this->setY(getStartRow());
    this->setDead(false);
}



int Model::Ghost::getManhattanDistancePacMan(const direction &direction) {
    int pacManRow = toTile(this->getWorld()->getPacMan()->getY());
    int pacManCol = toTile(this->getWorld()->getPacMan()->getX());
    if (direction == direction::up){
        return abs(toTile(this->getY()) - 1 - pacManRow) + abs(toTile(this->getX()) - pacManCol);
    }
    else if (direction == direction::down){
        return abs(toTile(this->getY()) + 1 - pacManRow) + abs(toTile(this->getX()) - pacManCol);
    }
    else if (direction == direction::left){
        return abs(toTile(this->getY()) - pacManRow) + abs(toTile(this->getX()) - 1 - pacManCol);
    }
    else {
        assert(direction == direction::right);
        return abs(toTile(this->getY()) - pacManRow) + abs(toTile(this->getX()) + 1 - pacManCol);
    }
}

bool Model::Ghost::canMove(const int &row, const int &col) {
    if (this->getWorld()->getItem(row, col) == nullptr or this->getWorld()->getItem(row, col)->getTag() != wall){
        return true;
    }
    return false;
}

Model::Ghost::Ghost(int row, int col, const std::shared_ptr<Model::World>& world) : EntityModel(row, col), world(world) {
    frightenTime = 0;
    this->setTag(ghost);
    currentDirection = direction::up;
    startDirection = direction::up;
    stateManager = std::make_unique<Model::GhostStateManager>();
    startRow = row;
    startCol = col;
    nextDirection = direction::none;
    waitTime = 0;
    defaultSpeed = 2.5;
    speed = defaultSpeed;
    frightened = false;

}

void Model::Ghost::move(const double &seconds) {
    // Niks doen bij idle mode:
    if (this->getStateManager()->getCurrentTag() == ghostStateTag::idle or this->getStateManager()->getCurrentTag() == ghostStateTag::eaten or this->getStateManager()->getCurrentTag() == ghostStateTag::idleFrightened){
        return;
    }
    if (this->getCurrentDirection() == direction::up){
        double yCoord = this->getY();
        yCoord -= seconds * this->getSpeed();
        // Als volgende direction naar rechts is en hij kan naar rechts:
        if (this->getNextDirection() == direction::right and this->canMove(toTile(this->getY()), toTile(this->getX()) + 1)){
            double maxYCoord = toTile(this->getY());
            if (yCoord < maxYCoord){
                this->setY(maxYCoord);
                // 1 Tick naar rechts gaan als hij om de hoek is en de richtingen aanpassen
                this->setX(this->getX() + this->getSpeed() / 1000);
                this->setCurrentDirection(direction::right);
                this->setNextDirection(direction::none);
            }
            else{
                this->setY(yCoord);
            }
        }

        // Als volgende direction naar links is en hij kan naar links:
        else if (this->getNextDirection() == direction::left and this->canMove(toTile(this->getY()), toTile(this->getX()) - 1)){
            double maxYCoord = toTile(this->getY());
            if (yCoord < maxYCoord){
                this->setY(maxYCoord);
                // 1 Tick naar links gaan als hij om de hoek is en de richtingen aanpassen
                this->setX(this->getX() - this->getSpeed() / 1000);
                this->setCurrentDirection(direction::left);
                this->setNextDirection(direction::none);
            }
            else{
                this->setY(yCoord);
            }
        }

            // Als de volgende tile een muur is:
        else if (this->getWorld()->getItem(toTile(this->getY()) - 1, toTile(this->getX())) != nullptr and this->getWorld()->getItem(
                toTile(this->getY()) - 1, toTile(this->getX()))->getTag() == wall){
            double maxYCoord = toTile(this->getY());
            if (yCoord < maxYCoord){
                this->setY(maxYCoord);
            }
            else{
                this->setY(yCoord);
            }
        }

            // Checken of hij dichter bij een ander vakje staat dan het huidige
        else if (toTile(this->getY()) != toTile(yCoord)){
            // Als het volgende vakje geen muur is: gaan
            if (this->canMove(toTile(this->getY()) - 1, toTile(this->getX()))){
                this->setY(yCoord);
                this->changeDirection();
            }
        }else{
            this->setY(yCoord);
        }
    }
    else if (this->getCurrentDirection() == direction::down){
        double yCoord = this->getY();
        yCoord += seconds * this->getSpeed();
        // Als volgende direction naar rechts is en hij kan naar rechts:
        if (this->getNextDirection() == direction::right and this->canMove(toTile(this->getY()),
                                                                           toTile(this->getX()) + 1)){
            double wallYCoord = toTile(this->getY());
            if (yCoord > wallYCoord){
                this->setY(wallYCoord);
                // 1 Tick naar rechts gaan als hij om de hoek is en de richtingen aanpassen
                this->setX(this->getX() + this->getSpeed() / 1000);
                this->setCurrentDirection(direction::right);
                this->setNextDirection(direction::none);
            }
            else{
                this->setY(yCoord);
            }
        }
            // Als volgende direction naar links is en hij kan naar links:
        else if (this->getNextDirection() == direction::left and this->canMove(toTile(this->getY()), toTile(this->getX()) - 1)){
            double wallYCoord = toTile(this->getY());
            if (yCoord > wallYCoord){
                this->setY(wallYCoord);
                // 1 Tick naar links gaan als hij om de hoek is en de richtingen aanpassen
                this->setX(this->getX() - this->getSpeed() / 1000);
                this->setCurrentDirection(direction::left);
                this->setNextDirection(direction::none);
            }
            else{
                this->setY(yCoord);
            }
        }
            // Als de volgende tile een muur is:
        else if (this->getWorld()->getItem(toTile(this->getY()) + 1, toTile(this->getX())) != nullptr and this->getWorld()->getItem(
                toTile(this->getY()) + 1, toTile(this->getX()))->getTag() == wall){
            double wallYCoord = toTile(this->getY());
            if (yCoord > wallYCoord){
                this->setY(wallYCoord);
            }
            else{
                this->setY(yCoord);
            }
        }
            // Checken of hij dichter bij een ander vakje staat dan het huidige
        else if (toTile(this->getY()) != toTile(yCoord)){
            // Als het volgende vakje geen muur is: gaan
            if (this->canMove(toTile(this->getY()) + 1, toTile(this->getX()))){
                this->setY(yCoord);
                this->changeDirection();
            }
        }
        else{
            this->setY(yCoord);
        }
    }
    else if (this->getCurrentDirection() == direction::right){
        double xCoord = this->getX();
        xCoord += seconds * this->getSpeed();
        // Als volgende direction naar links is en hij kan naar links:
        if (this->getNextDirection() == direction::up and this->canMove(toTile(this->getY()) - 1, toTile(this->getX()))){
            double wallXCoord = toTile(this->getX());
            if (xCoord > wallXCoord){
                this->setX(wallXCoord);
                // 1 Tick naar links gaan als hij om de hoek is en de richtingen aanpassen
                this->setY(this->getY() - this->getSpeed() / 1000);
                this->setCurrentDirection(direction::up);
                this->setNextDirection(direction::none);
            }
            else{
                this->setX(xCoord);
            }
        }
        else if (this->getNextDirection() == direction::down and this->canMove(toTile(this->getY()) + 1, toTile(this->getX()))){
            double wallXCoord = toTile(getX());
            if (xCoord > wallXCoord){
                this->setX(wallXCoord);
                // 1 Tick naar links gaan als hij om de hoek is en de richtingen aanpassen
                this->setY(this->getY() + this->getSpeed() / 1000);
                this->setCurrentDirection(direction::down);
                this->setNextDirection(direction::none);
            }
            else{
                this->setX(xCoord);
            }
        }
            // Als de volgende tile een muur is:
        else if (this->getWorld()->getItem(toTile(this->getY()), toTile(this->getX()) + 1) != nullptr and this->getWorld()->getItem(
                toTile(this->getY()), toTile(this->getX()) + 1)->getTag() == wall){
            double wallXCoord = toTile(this->getX());
            if (xCoord > wallXCoord){
                this->setX(wallXCoord);
            }
            else{
                this->setX(xCoord);
            }
        }
            // Checken of hij dichter bij een ander vakje staat dan het huidige
        else if (toTile(this->getX()) != toTile(xCoord)){
            // Als het volgende vakje geen muur is: gaan
            if (this->canMove(toTile(this->getY()), toTile(this->getX()) + 1)){
                this->setX(xCoord);
                this->changeDirection();
            }
        }else{
            this->setX(xCoord);
        }
    }
    else if (this->getCurrentDirection() == direction::left){
        double xCoord = this->getX();
        xCoord -= seconds * this->getSpeed();
        // Als volgende direction naar links is en hij kan naar links:
        if (this->getNextDirection() == direction::up and this->canMove(toTile(this->getY()) - 1,toTile(this->getX()))){
            double wallXCoord = toTile(this->getX());
            if (xCoord < wallXCoord){
                this->setX(wallXCoord);
                // 1 Tick naar links gaan als hij om de hoek is en de richtingen aanpassen
                this->setY(this->getY() - this->getSpeed() / 1000);
                this->setCurrentDirection(direction::up);
                this->setNextDirection(direction::none);
            }
            else{
                this->setX(xCoord);
            }
        }
        else if (this->getNextDirection() == direction::down and this->canMove(toTile(this->getY()) + 1,
                                                                               toTile(this->getX()))){
            double wallXCoord = toTile(this->getX());
            if (xCoord < wallXCoord){
                this->setX(wallXCoord);
                // 1 Tick naar links gaan als hij om de hoek is en de richtingen aanpassen
                this->setY(this->getY() + this->getSpeed() / 1000);
                this->setCurrentDirection(direction::down);
                this->setNextDirection(direction::none);
            }
            else{
                this->setX(xCoord);
            }
        }
            // Als de volgende tile een muur is:
        else if (this->getWorld()->getItem(toTile(this->getY()), toTile(this->getX()) - 1) != nullptr and this->getWorld()->getItem(
                toTile(this->getY()), toTile(this->getX()) - 1)->getTag() == wall){
            double wallXCoord = toTile(this->getX());
            if (xCoord < wallXCoord){
                this->setX(wallXCoord);
            }
            else{
                this->setX(xCoord);
            }
        }
            // Checken of hij dichter bij een ander vakje staat dan het huidige
        else if (toTile(this->getX()) != toTile(xCoord)){
            // Als het volgende vakje geen muur is: gaan
            if (this->canMove(toTile(this->getY()), toTile(this->getX()) - 1)){
                this->setX(xCoord);
                this->changeDirection();
            }
        }else{
            this->setX(xCoord);
        }
    }
    else{
        assert(this->getCurrentDirection() == direction::none);
    }
}

shared_ptr<Model::World> Model::Ghost::getWorld() {
    return world.lock();
}

void Model::Ghost::update(const double &seconds) {
    if (this->getWorld()->isGameStarted()){
        this->move(seconds);
    }
    for (const auto& observers: this->getObservers()){
        observers->update(seconds);
    }
    this->getStateManager()->update();
}

double Model::Ghost::getSpeed() const {
    return speed;
}

bool Model::Ghost::canMove(const direction &direction) {
    assert(direction != direction::none);
    if (direction == direction::up){
        return this->canMove(toTile(this->getY()) - 1, toTile(this->getX()));
    }
    else if (direction == direction::down){
        return this->canMove(toTile(this->getY()) + 1, toTile(this->getX()));
    }
    else if (direction == direction::left){
        return this->canMove(toTile(this->getY()), toTile(this->getX()) - 1);
    }
    else{
        assert(direction == direction::right);
        return this->canMove(toTile(this->getY()), toTile(this->getX()) + 1);
    }
}

direction Model::Ghost::getStartDirection() const {
    return startDirection;
}

void Model::Ghost::setStartDirection(direction direction) {
    Ghost::startDirection = direction;
    Ghost::currentDirection = direction;
}

const shared_ptr<Model::GhostStateManager> &Model::Ghost::getStateManager() const {
    return stateManager;
}

double Model::Ghost::getWaitTime() const {
    return waitTime;
}

void Model::Ghost::setWaitTime(double seconds) {
    Ghost::waitTime = seconds;
}

bool Model::Ghost::isFrightened() const {
    return frightened;
}

void Model::Ghost::setFrightened(bool b) {
    if (!b){
        this->setFrightenTime(Stopwatch::instance()->getLevelTime());
    }
    Ghost::frightened = b;
}

int Model::Ghost::getManhattanDistanceSpawn(const direction &direction) {
    if (direction == direction::up){
        return abs(toTile(this->getY()) - 1 - this->getStartRow()) + abs(toTile(this->getX()) - this->getStartCol());
    }
    else if (direction == direction::down){
        return abs(toTile(this->getY()) + 1 - this->getStartRow()) + abs(toTile(this->getX()) - this->getStartCol());
    }
    else if (direction == direction::left){
        return abs(toTile(this->getY()) - this->getStartRow()) + abs(toTile(this->getX()) - 1 - this->getStartCol());
    }
    else {
        assert(direction == direction::right);
        return abs(toTile(this->getY()) - this->getStartRow()) + abs(toTile(this->getX()) + 1 - this->getStartCol());
    }
}

double Model::Ghost::getDefaultSpeed()  {
    // Elk level wordt de snelheid 10% sneller
    return defaultSpeed * pow(1.10, this->getWorld()->getLevelNr());
}

double Model::Ghost::getFrightenTime() const {
    return frightenTime;
}

void Model::Ghost::setFrightenTime(double d) {
    Ghost::frightenTime = d;
}


void Model::PacMan::move(const double &seconds) {
    this->setHasMoved(true);
    if (this->getCurrentDirection() == direction::up){
        double yCoord = this->getY();
        yCoord -= seconds * this->getSpeed();
        // Als volgende direction naar rechts is en hij kan naar rechts:
        if (this->getNextDirection() == direction::right and this->canMove(toTile(this->getY()), toTile(this->getX()) + 1)){
            double maxYCoord = toTile(this->getY());
            if (yCoord < maxYCoord){
                this->setY(maxYCoord);
                // 1 Tick naar rechts gaan als hij om de hoek is en de richtingen aanpassen
                this->setX(this->getX() + this->getSpeed() / 1000);
                this->setCurrentDirection(direction::right);
                this->setNextDirection(direction::none);
            }
            else{
                this->setY(yCoord);
            }
        }

        // Als volgende direction naar links is en hij kan naar links:
        else if (this->getNextDirection() == direction::left and this->canMove(toTile(this->getY()), toTile(this->getX()) - 1)){
            double maxYCoord = toTile(this->getY());
            if (yCoord < maxYCoord){
                this->setY(maxYCoord);
                // 1 Tick naar links gaan als hij om de hoek is en de richtingen aanpassen
                this->setX(this->getX() - this->getSpeed() / 1000);
                this->setCurrentDirection(direction::left);
                this->setNextDirection(direction::none);
            }
            else{
                this->setY(yCoord);
            }
        }

        // Als de volgende tile een muur is:
        else if (this->getWorld()->getItem(toTile(this->getY()) - 1, toTile(this->getX())) != nullptr and this->getWorld()->getItem(
                toTile(this->getY()) - 1, toTile(this->getX()))->getTag() == wall){
            double maxYCoord = toTile(this->getY());
            if (yCoord < maxYCoord){
                this->setY(maxYCoord);
                this->setHasMoved(false);
            }
            else{
                this->setY(yCoord);
            }
        }

        // Checken of hij dichter bij een ander vakje staat dan het huidige
        else if (toTile(this->getY()) != toTile(yCoord)){
            // Als het volgende vakje geen muur is: gaan
             if (this->canMove(toTile(this->getY()) - 1, toTile(this->getX()))){
                this->setY(yCoord);
                // Als er hier een coin ligt, checken of deze al geconsumeerd is:
                auto item = this->getWorld()->getCollectable(toTile(this->getY()), toTile(this->getX()));
                if (item != nullptr and (item->getTag() == coin or item->getTag() == fruit)){
                    if (!item->isConsumed()){
                        item->consume();
                        for (const auto& observer: this->getObservers()){
                            observer->collectableCollected(item);
                        }
                        if (item->getTag() == fruit){
                            for (const auto& ghost: this->getWorld()->getGhosts()){
                                if (ghost->getStateManager()->getCurrentTag() <= 2) {
                                    ghost->setFrightened(true);
                                }
                            }
                        }
                    }
                }
            }
        }else{
            this->setY(yCoord);
        }
    }
    else if (this->getCurrentDirection() == direction::down){
        double yCoord = this->getY();
        yCoord += seconds * this->getSpeed();
        // Als volgende direction naar rechts is en hij kan naar rechts:
        if (this->getNextDirection() == direction::right and this->canMove(toTile(this->getY()),
                                                                           toTile(this->getX()) + 1)){
            double wallYCoord = toTile(this->getY());
            if (yCoord > wallYCoord){
                this->setY(wallYCoord);
                // 1 Tick naar rechts gaan als hij om de hoek is en de richtingen aanpassen
                this->setX(this->getX() + this->getSpeed() / 1000);
                this->setCurrentDirection(direction::right);
                this->setNextDirection(direction::none);
            }
            else{
                this->setY(yCoord);
            }
        }
            // Als volgende direction naar links is en hij kan naar links:
        else if (this->getNextDirection() == direction::left and this->canMove(toTile(this->getY()), toTile(this->getX()) - 1)){
            double wallYCoord = toTile(this->getY());
            if (yCoord > wallYCoord){
                this->setY(wallYCoord);
                // 1 Tick naar links gaan als hij om de hoek is en de richtingen aanpassen
                this->setX(this->getX() - this->getSpeed() / 1000);
                this->setCurrentDirection(direction::left);
                this->setNextDirection(direction::none);
            }
            else{
                this->setY(yCoord);
            }
        }
            // Als de volgende tile een muur is:
        else if (this->getWorld()->getItem(toTile(this->getY()) + 1, toTile(this->getX())) != nullptr and this->getWorld()->getItem(
                toTile(this->getY()) + 1, toTile(this->getX()))->getTag() == wall){
            double wallYCoord = toTile(this->getY());
            if (yCoord > wallYCoord){
                this->setY(wallYCoord);
                this->setHasMoved(false);
            }
            else{
                this->setY(yCoord);
            }
        }
            // Checken of hij dichter bij een ander vakje staat dan het huidige
        else if (toTile(this->getY()) != toTile(yCoord)){
            // Als het volgende vakje geen muur is: gaan
             if (this->canMove(toTile(this->getY()) + 1, toTile(this->getX()))){
                this->setY(yCoord);
                // Als er hier een coin ligt, checken of deze al geconsumeerd is:
                auto item = this->getWorld()->getCollectable(toTile(this->getY()), toTile(this->getX()));
                if (item != nullptr and (item->getTag() == coin or item->getTag() == fruit)){
                    if (!item->isConsumed()){
                        item->consume();
                        for (const auto& observer: this->getObservers()){
                            observer->collectableCollected(item);
                        }
                        if (item->getTag() == fruit){
                            for (const auto& ghost: this->getWorld()->getGhosts()){
                                if (ghost->getStateManager()->getCurrentTag() <= 2) {
                                    ghost->setFrightened(true);
                                }
                            }
                        }
                    }
                }
            }
        }
        else{
            this->setY(yCoord);
        }
    }
    else if (this->getCurrentDirection() == direction::right){
        double xCoord = this->getX();
        xCoord += seconds * this->getSpeed();
        // Als volgende direction naar links is en hij kan naar links:
        if (this->getNextDirection() == direction::up and this->canMove(toTile(this->getY()) - 1, toTile(this->getX()))){
            double wallXCoord = toTile(this->getX());
            if (xCoord > wallXCoord){
                this->setX(wallXCoord);
                // 1 Tick naar links gaan als hij om de hoek is en de richtingen aanpassen
                this->setY(this->getY() - this->getSpeed() / 1000);
                this->setCurrentDirection(direction::up);
                this->setNextDirection(direction::none);
            }
            else{
                this->setX(xCoord);
            }
        }
        else if (this->getNextDirection() == direction::down and this->canMove(toTile(this->getY()) + 1, toTile(this->getX()))){
            double wallXCoord = toTile(getX());
            if (xCoord > wallXCoord){
                this->setX(wallXCoord);
                // 1 Tick naar links gaan als hij om de hoek is en de richtingen aanpassen
                this->setY(this->getY() + this->getSpeed() / 1000);
                this->setCurrentDirection(direction::down);
                this->setNextDirection(direction::none);
            }
            else{
                this->setX(xCoord);
            }
        }
            // Als de volgende tile een muur is:
        else if (this->getWorld()->getItem(toTile(this->getY()), toTile(this->getX()) + 1) != nullptr and this->getWorld()->getItem(
                toTile(this->getY()), toTile(this->getX()) + 1)->getTag() == wall){
            double wallXCoord = toTile(this->getX());
            if (xCoord > wallXCoord){
                this->setX(wallXCoord);
                this->setHasMoved(false);
            }
            else{
                this->setX(xCoord);
            }
        }
            // Checken of hij dichter bij een ander vakje staat dan het huidige
        else if (toTile(this->getX()) != toTile(xCoord)){
            // Als het volgende vakje geen muur is: gaan
            if (this->canMove(toTile(this->getY()), toTile(this->getX()) + 1)){
                this->setX(xCoord);
                // Als er hier een coin ligt, checken of deze al geconsumeerd is:
                auto item = this->getWorld()->getCollectable(toTile(this->getY()), toTile(this->getX()));
                if (item != nullptr and (item->getTag() == coin or item->getTag() == fruit)){
                    if (!item->isConsumed()){
                        item->consume();
                        for (const auto& observer: this->getObservers()){
                            observer->collectableCollected(item);
                        }
                        if (item->getTag() == fruit){
                            for (const auto& ghost: this->getWorld()->getGhosts()){
                                if (ghost->getStateManager()->getCurrentTag() <= 2) {
                                    ghost->setFrightened(true);
                                }
                            }
                        }
                    }

                }
            }
        }else{
            this->setX(xCoord);
        }
    }
    else if (this->getCurrentDirection() == direction::left){
        double xCoord = this->getX();
        xCoord -= seconds * this->getSpeed();
        // Als volgende direction naar links is en hij kan naar links:
        if (this->getNextDirection() == direction::up and this->canMove(toTile(this->getY()) - 1,toTile(this->getX()))){
            double wallXCoord = toTile(this->getX());
            if (xCoord < wallXCoord){
                this->setX(wallXCoord);
                // 1 Tick naar links gaan als hij om de hoek is en de richtingen aanpassen
                this->setY(this->getY() - this->getSpeed() / 1000);
                this->setCurrentDirection(direction::up);
                this->setNextDirection(direction::none);
            }
            else{
                this->setX(xCoord);
            }
        }
        else if (this->getNextDirection() == direction::down and this->canMove(toTile(this->getY()) + 1,
                                                                               toTile(this->getX()))){
            double wallXCoord = toTile(this->getX());
            if (xCoord < wallXCoord){
                this->setX(wallXCoord);
                // 1 Tick naar links gaan als hij om de hoek is en de richtingen aanpassen
                this->setY(this->getY() + this->getSpeed() / 1000);
                this->setCurrentDirection(direction::down);
                this->setNextDirection(direction::none);
            }
            else{
                this->setX(xCoord);
            }
        }
            // Als de volgende tile een muur is:
        else if (this->getWorld()->getItem(toTile(this->getY()), toTile(this->getX()) - 1) != nullptr and this->getWorld()->getItem(
                toTile(this->getY()), toTile(this->getX()) - 1)->getTag() == wall){
            double wallXCoord = toTile(this->getX());
            if (xCoord < wallXCoord){
                this->setX(wallXCoord);
                this->setHasMoved(false);
            }
            else{
                this->setX(xCoord);
            }
        }
        // Checken of hij dichter bij een ander vakje staat dan het huidige
        else if (toTile(this->getX()) != toTile(xCoord)){
            // Als het volgende vakje geen muur is: gaan
             if (this->canMove(toTile(this->getY()), toTile(this->getX()) - 1)){
                this->setX(xCoord);
                // Als er hier een coin ligt, checken of deze al geconsumeerd is:
                auto item = this->getWorld()->getCollectable(toTile(this->getY()), toTile(this->getX()));
                if (item != nullptr and (item->getTag() == coin or item->getTag() == fruit)){
                    if (!item->isConsumed()){
                        item->consume();
                        for (const auto& observer: this->getObservers()){
                            observer->collectableCollected(item);
                        }
                        if (item->getTag() == fruit){
                            for (const auto& ghost: this->getWorld()->getGhosts()){
                                if (ghost->getStateManager()->getCurrentTag() <= 2) {
                                    ghost->setFrightened(true);
                                }
                            }
                        }
                    }
                }
            }
        }else{
            this->setX(xCoord);
        }
    }
    else{
        assert(this->getCurrentDirection() == direction::none);
    }

}

shared_ptr<Model::Collectable> Model::World::getCollectable(const int &row, const int &col) {
    return collectableWorld[row][col];
}

const shared_ptr<Model::Score> &Model::World::getScoreClass() const {
    return score;
}

void Model::World::setScore(const shared_ptr<Model::Score> &sharedPtr) {
    World::score = sharedPtr;
}

const vector<std::shared_ptr<Model::Fruit>> &Model::World::getFruits() const {
    return fruits;
}

void Model::World::setFruits(const vector<std::shared_ptr<Fruit>> &fruit) {
    World::fruits = fruit;
}

void Model::World::restartWorld() {
    this->restart();
    for (const auto& coin: this->getCoins()){
        coin->restart();
    }
    for (const auto& fruit: this->getFruits()){
        fruit->restart();
    }
    this->getScoreClass()->restart();
    this->setLevelNr(0);
}

void Model::World::nextLevel() {
    this->restart();
    for (const auto& coin: this->getCoins()){
        coin->restart();
    }
    for (const auto& fruit: this->getFruits()){
        fruit->restart();
    }
    this->getScoreClass()->nextLevel();
    this->setLevelNr(this->getLevelNr() + 1);
}

int Model::World::getLevelNr() const {
    return levelNr;
}

void Model::World::setLevelNr(int nr) {
    World::levelNr = nr;
}

void Model::Score::update(const double &seconds) {
    auto stopwatch = Model::Stopwatch::instance();
    // Als de game gestart is zetten we de level start time gelijk aan de huidige kloktijd.
    if (this->getWorld().lock() and this->getWorld().lock()->isGameStarted()){
        if (this->getLevelStartTime() == 0){
            this->setLevelStartTime(stopwatch->getTotalSeconds());
            this->setBenchMarkTime(this->getLevelStartTime());
        }
        // Nu voor elke seconde dat het level langer dan 20 seconden duurt, worden er 5 punten afgetrokken:
        // dit wordt door een benchmark-time gedaan wat die begint op de begintijd van het level en telkens per seconde
        // over 20 sec telkens 1 seconden omhoog schuift zodat mooi bij elke seconde over tijd de score wordt aangepast.
        if (stopwatch->getLevelTime() - this->getBenchMarkTime() > 20){
            this->setScore(this->getScore() - 5);
            this->setBenchMarkTime(this->getBenchMarkTime() + 1);
        }
    }
}
void Model::Score::collectableCollected(const std::weak_ptr<Model::Collectable> &collectable) {
    // De value van de collectable wordt vermenigvuldigd met een amplifying factor op basis van de tijd waarop de vorige
    // collectable die is opgepakt.
    double doubleValue = collectable.lock()->getValue() * this->getAmplifyingFactor();
    this->setScore(this->getScore() + int(std::round(doubleValue)));
    if (this->getWorld().lock() and collectable.lock() and collectable.lock()->getTag() == coin or collectable.lock()->getTag() == fruit){
        this->setCoinsCollected(this->getCoinsCollected() + 1);
    }
}

void Model::PacMan::die() {
    this->setDead(true);
    this->setDeathTime(Stopwatch::instance()->getLevelTime());
    this->getWorld()->getScoreClass()->setLivesLeft(this->getWorld()->getScoreClass()->getLivesLeft() - 1);
}

void Model::PacMan::update(const double &seconds) {
    // Niet moven bij dood
    if (!this->isDead()){
        this->move(seconds);
    }
    // Als er 3 seconden voorbij zijn, respawned de pacman
    if (this->isDead() and this->getDeathTime() + 2 < Stopwatch::instance()->getLevelTime()){
        this->setDead(false);
        this->getWorld()->restart();
    }
    for (const auto& observer: this->getObservers()){
        observer->update(seconds);
    }

}

void Model::Score::nextLevel() {
    if (this->getWorld().lock()){
        this->setCoinsCollected(0);
    }

}