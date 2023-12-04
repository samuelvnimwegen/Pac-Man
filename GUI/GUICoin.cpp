//
// Created by Samuel on 20/11/2023.
//

#include "GUICoin.h"



GUI::GUICoin::GUICoin(Model::Coin *coin) : GUI::EntityView(coin) {
    subject = coin;
    sf::Texture texture;
    texture.loadFromFile("Sprites.png");
    this->setTexture(texture);
    sf::Sprite sprite(this->getTexture(), sf::IntRect(400, 250, 40, 40));
    this->setSprite(sprite);
}

GUI::GUICoin::~GUICoin() = default;

