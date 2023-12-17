//
// Created by Samuel on 16/11/2023.
//

#include "GUIWall.h"

#include <utility>


GUI::GUIWall::~GUIWall() = default;


GUI::GUIWall::GUIWall(const std::shared_ptr<Model::Wall>& subject, std::weak_ptr<sf::RenderWindow> win) : EntityView(subject, std::move(win)) {
    sf::Texture texture;
    texture.loadFromFile("Muur2.png");
    this->setTexture(texture);
    sf::Sprite sprite(this->getTexture());
    this->setSprite(sprite);
}

