//
// Created by Samuel on 21/11/2023.
//

#include "GUIGhost.h"



sf::Sprite GUI::GUIGhost::getSprite() {
    sf::Sprite sprite;

    sprite = sf::Sprite(this->getTexture(), sf::IntRect(spriteX, 0, 40, 40));


    return sprite;
}

GUI::GUIGhost::GUIGhost(color ghostColor) : ghostColor(ghostColor) {
    textureNr = 0;
    sf::Texture texture;
    texture.loadFromFile("Sprites.png");
    this->setTexture(texture);
    if (ghostColor == color::red){
        spriteX = 0;
    }else if (ghostColor == color::pink){
        spriteX = 50;
    }else if (ghostColor == color::blue){
        spriteX = 100;
    }else {
        spriteX = 150;
    }
}

void GUI::GUIGhost::move(const int &ticks) {

}


