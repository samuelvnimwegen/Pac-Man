//
// Created by Samuel on 16/11/2023.
//

#include "GUIPacMan.h"

GUIPacMan::GUIPacMan(Subject *subject) : EntityView(subject) {}

sf::Sprite GUIPacMan::getSprite() {
    sf::Texture texture;
    texture.loadFromFile("Sprites.png");
    this->setTexture(texture);
    sf::Sprite sprite(this->getTexture(), sf::IntRect(850, 1, 40, 40));
    return sprite;
}
