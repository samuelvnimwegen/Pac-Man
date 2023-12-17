//
// Created by Samuel on 20/11/2023.
//

#include "GUICoin.h"

#include <utility>



GUI::GUICoin::GUICoin(const std::shared_ptr<Model::Coin>& coin, std::weak_ptr<sf::RenderWindow> win) : GUI::EntityView(coin, std::move(win)) {
    sf::Texture texture;
    texture.loadFromFile("Sprites.png");
    this->setTexture(texture);
    sf::Sprite sprite(this->getTexture(), sf::IntRect(400, 250, 40, 40));
    this->setSprite(sprite);
}

GUI::GUICoin::~GUICoin() = default;

