//
// Created by Samuel on 20/11/2023.
//

#include "GUICoin.h"


Coin *GUICoin::getSubject() const {
    return subject;
}

GUICoin::GUICoin(Coin *subject) : subject(subject) {
    this->setCol(subject->getCol());
    this->setRow(subject->getRow());
    sf::Texture texture;
    texture.loadFromFile("Sprites.png");
    this->setTexture(texture);
    sf::Sprite sprite(this->getTexture(), sf::IntRect(400, 250, 40, 40));
    this->setSprite(sprite);
}

