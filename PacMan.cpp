//
// Created by Samuel on 19/11/2023.
//

#include "PacMan.h"


const direction &Model::PacMan::getCurrentDirection() const {
    return currentDirection;
}

void Model::PacMan::setCurrentDirection(const direction &dir) {
    PacMan::currentDirection = dir;
}

int Model::PacMan::getStartRow() const {
    return startRow;
}

void Model::PacMan::setStartRow(int row) {
    PacMan::startRow = row;
}

int Model::PacMan::getStartCol() const {
    return startCol;
}

void Model::PacMan::setStartCol(int col) {
    PacMan::startCol = col;
}

int Model::PacMan::getScore() const {
    return score;
}

void Model::PacMan::setScore(int newScore) {
    PacMan::score = newScore;
}
bool Model::PacMan::isHasMoved() const {
    return hasMoved;
}

void Model::PacMan::setHasMoved(bool moved) {
    PacMan::hasMoved = moved;
}
double Model::PacMan::getXSpeed() const {
    return xSpeed;
}

void Model::PacMan::setXSpeed(double speed) {
    PacMan::xSpeed = speed;
}

double Model::PacMan::getYSpeed() const {
    return ySpeed;
}

void Model::PacMan::setYSpeed(double speed) {
    PacMan::ySpeed = speed;
}

const direction &Model::PacMan::getNextDirection() const {
    return nextDirection;
}

void Model::PacMan::setNextDirection(const direction &dir) {
    PacMan::nextDirection = dir;
}

void Model::PacMan::move(const int &ticks) {
    this->getObservers().at(0)->move(ticks);
}

 std::shared_ptr<Model::World> Model::PacMan::getWorld()  {
    return world.lock();
}

void Model::PacMan::setWorld(const std::weak_ptr<Model::World> &weakPtr) {
    PacMan::world = weakPtr;
}
