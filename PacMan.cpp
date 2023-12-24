//
// Created by Samuel on 19/11/2023.
//

#include "PacMan.h"
using namespace std;

const direction &Model::PacMan::getCurrentDirection() const {
    return currentDirection;
}

void Model::PacMan::setCurrentDirection(const direction &dir) {
    PacMan::currentDirection = dir;
}

int Model::PacMan::getStartRow() const {
    return startRow;
}

int Model::PacMan::getStartCol() const {
    return startCol;
}

bool Model::PacMan::isHasMoved() const {
    return hasMoved;
}

void Model::PacMan::setHasMoved(bool moved) {
    PacMan::hasMoved = moved;
}

const direction &Model::PacMan::getNextDirection() const {
    return nextDirection;
}

void Model::PacMan::setNextDirection(const direction &dir) {
    PacMan::nextDirection = dir;
}



 std::shared_ptr<Model::World> Model::PacMan::getWorld()  {
    return world.lock();
}

void Model::PacMan::update(const double &seconds) {
    this->move(seconds);
    for (const auto& observer: this->getObservers()){
        observer->update(seconds);
    }
}


/*
 * Verandert de richting afhankelijk van de volgende richting
 */
void Model::PacMan::changeDirection(const direction &dir) {
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

double Model::PacMan::getSpeed() const {
    return speed;
}


