//
// Created by Samuel on 16/11/2023.
//

#include "GUIWall.h"


GUI::GUIWall::~GUIWall() = default;


GUI::GUIWall::GUIWall(Model::Wall *wall) : EntityView(wall) {
    sf::Texture texture;
    texture.loadFromFile("Muur2.png");
    this->setTexture(texture);
    sf::Sprite sprite(this->getTexture());
    this->setSprite(sprite);
}

