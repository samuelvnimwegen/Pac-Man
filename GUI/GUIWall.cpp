//
// Created by Samuel on 16/11/2023.
//

#include "GUIWall.h"

string GUIWall::getSpriteFileName() {
    return "Muur2.png";
}

GUIWall::GUIWall(World *world, int posX, int posY) : EntityView(world, posX, posY) {}

