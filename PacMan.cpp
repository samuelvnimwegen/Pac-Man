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