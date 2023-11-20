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

GUIWall::GUIWall(Wall *subject) : subject(subject) {
    this->setCol(subject->getCol());
    this->setRow(subject->getRow());
}

Subject *GUIWall::getSubject() const {
    return subject;
}






