//
// Created by Samuel on 19/11/2023.
//

#include "PacMan.h"


const string &Model::PacMan::getCurrentDirection() const {
    return currentDirection;
}

void Model::PacMan::setCurrentDirection(const string &direction) {
    PacMan::currentDirection = direction;
}


Model::World *Model::PacMan::getWorld() const {
    return world;
}

void Model::PacMan::setWorld(World *pWorld) {
    PacMan::world = pWorld;
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

const string &Model::PacMan::getNextDirection() const {
    return nextDirection;
}

void Model::PacMan::setNextDirection(const string &direction) {
    PacMan::nextDirection = direction;
}