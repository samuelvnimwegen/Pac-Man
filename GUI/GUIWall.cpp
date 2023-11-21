//
// Created by Samuel on 16/11/2023.
//

#include "GUIWall.h"

GUIWall::GUIWall(Wall *subject) : subject(subject) {
    this->setCol(subject->getCol());
    this->setRow(subject->getRow());
    sf::Texture texture;
    texture.loadFromFile("Muur2.png");
    this->setTexture(texture);
    sf::Sprite sprite(this->getTexture());
    this->setSprite(sprite);
}

Subject *GUIWall::getSubject() const {
    return subject;
}

GUIWall::~GUIWall() = default;






