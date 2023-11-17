//
// Created by Samuel on 16/11/2023.
//

#include "Observer.h"

Observer::Observer() {
    world = new World();
}

World *Observer::getWorld() const {
    return world;
}

void Observer::setWorld(World *world) {
    Observer::world = world;
}

Observer::Observer(World *world) : world(world) {}
