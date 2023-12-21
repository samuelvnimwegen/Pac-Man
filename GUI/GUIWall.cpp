//
// Created by Samuel on 16/11/2023.
//

#include "GUIWall.h"

#include <memory>
#include <utility>


GUI::GUIWall::~GUIWall() = default;


GUI::GUIWall::GUIWall(const std::shared_ptr<Model::Wall>& subject, std::weak_ptr<sf::RenderWindow> win) : EntityView(subject, std::move(win)) {
    auto texture = std::make_shared<sf::Texture>();
    texture->loadFromFile("Muur2.png");
    this->setTexture(texture);

    auto camera = Camera::instance();
    auto camCoords = camera->getCameraCoords(this->getSubject()->getY(), this->getSubject()->getX());
    auto windowCoords = cameraToPixels(camCoords.getXCoord(), camCoords.getYCoord());

    auto sprite = std::make_shared<sf::Sprite>(*this->getTexture());
    sprite->setPosition(float(windowCoords.first), float(windowCoords.second));
    this->setSprite(sprite);
}



