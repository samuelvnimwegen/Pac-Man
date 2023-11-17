//
// Created by Samuel on 16/11/2023.
//

#include "EntityView.h"


string EntityView::getSpriteFileName() {
    return "Sprites/Error.png";
}

EntityView::EntityView(World *world, int posX, int posY) : Observer(world), posX(posX), posY(posY) {}
