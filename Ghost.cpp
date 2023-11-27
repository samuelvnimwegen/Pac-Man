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
    string direction = "NONE";
    // Als hij omhoog kan:
    if (this->canMove(this->getRow() - 1, this->getCol())){
        int distance = this->getManhattanDistance(direction::up);
        if (distance < minDistance){
            minDistance = distance;
            direction = direction::up;
        }
    }
    // Als hij naar beneden kan:
    if (this->canMove(this->getRow() + 1, this->getCol())){
        int distance = this->getManhattanDistance(down);
        if (distance < minDistance){
            minDistance = distance;
            direction = down;
        }
    }
    // Als hij naar rechts kan:
    if (this->canMove(this->getRow(), this->getCol() + 1)){
        int distance = this->getManhattanDistance("RIGHT");
        if (distance < minDistance){
            minDistance = distance;
            direction = "RIGHT";
        }
    }
    // Als hij naar links kan:
    if (this->canMove(this->getRow(), this->getCol() - 1)){
        int distance = this->getManhattanDistance("LEFT");
        if (distance < minDistance){
            direction = "LEFT";
        }
    }


    if (this->getCurrentDirection() == "UP"){
        if (direction == "DOWN" and !canMove(this->getRow() - 1, this->getCol())){
            this->setCurrentDirection("DOWN");
        }
        else if (direction == "LEFT"){
            this->setNextDirection("LEFT");
        }
        else if (direction == "RIGHT"){
            this->setNextDirection("RIGHT");
        }
    }
    else if (this->getCurrentDirection() == "DOWN" ){
        if (direction == "UP" and !canMove(this->getRow() + 1, this->getCol())){
            this->setCurrentDirection("UP");
        }
        else if (direction == "LEFT"){
            this->setNextDirection("LEFT");
        }
        else if (direction == "RIGHT"){
            this->setNextDirection("RIGHT");
        }
    }
    else if (this->getCurrentDirection() == "LEFT"){
        if (direction == "RIGHT" and !canMove(this->getRow(), this->getCol() - 1)){
            this->setCurrentDirection("RIGHT");
        }
        else if (direction == "UP"){
            this->setNextDirection("UP");
        }
        else if (direction == "DOWN"){
            this->setNextDirection("DOWN");
        }
    }
    else if (this->getCurrentDirection() == "RIGHT"){
        if (direction == "LEFT" and !canMove(this->getRow(), this->getCol() + 1)){
            this->setCurrentDirection("LEFT");
        }
        else if (direction == "UP"){
            this->setNextDirection("UP");
        }
        else if (direction == "DOWN"){
            this->setNextDirection("DOWN");
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