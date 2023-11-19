//
// Created by Samuel on 16/11/2023.
//

#include "GUIWall.h"

sf::Sprite GUIWall::getSprite() {
    sf::Texture texture;
    texture.loadFromFile("Muur2.png");
    this->setTexture(texture);
    sf::Sprite sprite(this->getTexture());
    return sprite;
}

GUIWall::GUIWall(Subject *subject) : EntityView(subject) {}



