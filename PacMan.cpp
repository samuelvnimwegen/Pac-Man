//
// Created by Samuel on 19/11/2023.
//

#include "PacMan.h"


const string &PacMan::getCurrentDirection() const {
    return currentDirection;
}

void PacMan::setCurrentDirection(const string &direction) {
    PacMan::currentDirection = direction;
}


World *PacMan::getWorld() const {
    return world;
}

void PacMan::setWorld(World *pWorld) {
    PacMan::world = pWorld;
}

int PacMan::getStartRow() const {
    return startRow;
}

void PacMan::setStartRow(int row) {
    PacMan::startRow = row;
}

int PacMan::getStartCol() const {
    return startCol;
}

void PacMan::setStartCol(int col) {
    PacMan::startCol = col;
}

int PacMan::getScore() const {
    return score;
}

void PacMan::setScore(int newScore) {
    PacMan::score = newScore;
}
bool PacMan::isHasMoved() const {
    return hasMoved;
}

void PacMan::setHasMoved(bool moved) {
    PacMan::hasMoved = moved;
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