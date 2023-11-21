//
// Created by Samuel on 16/11/2023.
//

#include "Ghost.h"

World *Ghost::getWorld() const {
    return world;
}



const string &Ghost::getColor() const {
    return color;
}

void Ghost::setColor(const string &ghostColor) {
    Ghost::color = ghostColor;
}

const string &Ghost::getCurrentDirection() const {
    return currentDirection;
}

void Ghost::setCurrentDirection(const string &direction) {
    Ghost::currentDirection = direction;
}

double Ghost::getXSpeed() const {
    return xSpeed;
}

void Ghost::setXSpeed(double speed) {
    Ghost::xSpeed = speed;
}

double Ghost::getYSpeed() const {
    return ySpeed;
}

void Ghost::setYSpeed(double speed) {
    Ghost::ySpeed = speed;
}
void Ghost::changeDirection() {
    int minDistance = 1000000;
    string direction = "NONE";
    // Als hij omhoog kan:
    if (this->canMove(this->getRow() - 1, this->getCol())){
        int distance = this->getManhattanDistance("UP");
        if (distance < minDistance){
            minDistance = distance;
            direction = "UP";
        }
    }
    // Als hij naar beneden kan:
    if (this->canMove(this->getRow() + 1, this->getCol())){
        int distance = this->getManhattanDistance("DOWN");
        if (distance < minDistance){
            minDistance = distance;
            direction = "DOWN";
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

    if (direction != "NONE"){
        this->setCurrentDirection(direction);
        this->setJustTurned(true);
    }
}

bool Ghost::isJustTurned() const {
    return justTurned;
}

void Ghost::setJustTurned(bool turned) {
    Ghost::justTurned = turned;
}



