//
// Created by Samuel on 16/11/2023.
//

#include "Ghost.h"
using namespace std;
Model::World *Model::Ghost::getWorld() const {
    return world;
}

void Model::Ghost::changeDirection() {
    int minDistance = 1000000;
    direction dir = direction::none;
    // Als hij omhoog kan:
    if (this->canMove(this->getRow() - 1, this->getCol())){
        int distance = this->getManhattanDistance(direction::up);
        if (distance < minDistance){
            minDistance = distance;
            dir = direction::up;
        }
    }
    // Als hij naar beneden kan:
    if (this->canMove(this->getRow() + 1, this->getCol())){
        int distance = this->getManhattanDistance(down);
        if (distance < minDistance){
            minDistance = distance;
            dir = down;
        }
    }
    // Als hij naar rechts kan:
    if (this->canMove(this->getRow(), this->getCol() + 1)){
        int distance = this->getManhattanDistance(direction::right);
        if (distance < minDistance){
            minDistance = distance;
            dir = direction::right;
        }
    }
    // Als hij naar links kan:
    if (this->canMove(this->getRow(), this->getCol() - 1)){
        int distance = this->getManhattanDistance(direction::left);
        if (distance < minDistance){
            dir = direction::left;
        }
    }


    if (this->getCurrentDirection() == direction::up){
        if (dir == direction::down and !canMove(this->getRow() - 1, this->getCol())){
            this->setCurrentDirection(direction::down);
        }
        else if (dir == direction::left){
            this->setNextDirection(direction::left);
        }
        else if (dir == direction::right){
            this->setNextDirection(direction::right);
        }
    }
    else if (this->getCurrentDirection() == direction::down ){
        if (dir == direction::up and !canMove(this->getRow() + 1, this->getCol())){
            this->setCurrentDirection(direction::up);
        }
        else if (dir == direction::left){
            this->setNextDirection(direction::left);
        }
        else if (dir == direction::right){
            this->setNextDirection(direction::right);
        }
    }
    else if (this->getCurrentDirection() == direction::left){
        if (dir == direction::right and !canMove(this->getRow(), this->getCol() - 1)){
            this->setCurrentDirection(direction::right);
        }
        else if (dir == direction::up){
            this->setNextDirection(direction::up);
        }
        else if (dir == direction::down){
            this->setNextDirection(direction::down);
        }
    }
    else if (this->getCurrentDirection() == direction::right){
        if (dir == direction::left and !canMove(this->getRow(), this->getCol() + 1)){
            this->setCurrentDirection(direction::left);
        }
        else if (dir == direction::up){
            this->setNextDirection(direction::up);
        }
        else if (dir == direction::down){
            this->setNextDirection(direction::down);
        }
    }
}

bool Model::Ghost::isJustTurned() const {
    return justTurned;
}

void Model::Ghost::setJustTurned(bool turned) {
    Ghost::justTurned = turned;
}

void Model::Ghost::setWorld(World *gWorld) {
    Ghost::world = gWorld;
}

const string &Model::Ghost::getCurrentState() const {
    return currentState;
}

void Model::Ghost::setCurrentState(const string &state) {
    Ghost::currentState = state;
}

int Model::Ghost::getStartRow() const {
    return startRow;
}

void Model::Ghost::setStartRow(int row) {
    Ghost::startRow = row;
}

int Model::Ghost::getStartCol() const {
    return startCol;
}

void Model::Ghost::setStartCol(int col) {
    Ghost::startCol = col;
}


color Model::Ghost::getColor() const {
    return ghostColor;
}

void Model::Ghost::setColor(color col) {
    Ghost::ghostColor = col;
}

direction Model::Ghost::getCurrentDirection() const {
    return currentDirection;
}

void Model::Ghost::setCurrentDirection(direction direction) {
    Ghost::currentDirection = direction;
}

direction Model::Ghost::getNextDirection() const {
    return nextDirection;
}

void Model::Ghost::setNextDirection(direction direction) {
    Ghost::nextDirection = direction;
}


void Model::Ghost::reset() {
    this->setCurrentDirection(up);
    this->setNextDirection(none);
    this->setCol(getStartCol());
    this->setRow(getStartRow());
}