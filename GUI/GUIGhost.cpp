//
// Created by Samuel on 21/11/2023.
//

#include "GUIGhost.h"

GUIGhost::GUIGhost(Ghost *subject) : subject(subject) {
    textureNr = 0;
    sf::Texture texture;
    texture.loadFromFile("Sprites.png");
    this->setTexture(texture);
    if (this->getSubject()->getColor() == "RED"){
        spriteX = 0;
    }else if (this->getSubject()->getColor() == "PINK"){
        spriteX = 50;
    }else if (this->getSubject()->getColor() == "BLUE"){
        spriteX = 100;
    }else {
        spriteX = 150;
    }
}

Ghost* GUIGhost::getSubject() const {
    return subject;
}

sf::Sprite GUIGhost::getSprite() {
    sf::Sprite sprite;

    sprite = sf::Sprite(this->getTexture(), sf::IntRect(spriteX, 0, 40, 40));


    return sprite;
}
