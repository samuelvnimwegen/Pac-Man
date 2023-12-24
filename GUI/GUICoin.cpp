//
// Created by Samuel on 20/11/2023.
//

#include "GUICoin.h"

#include <utility>



GUI::GUICoin::GUICoin(const std::shared_ptr<Model::Coin>& coin, std::weak_ptr<sf::RenderWindow> win) : GUI::EntityView(coin, std::move(win)) {
    subject = coin;
    auto texture = std::make_shared<sf::Texture>();
    texture->loadFromFile("Sprites.png");
    this->setTexture(texture);

    auto camera = Camera::instance();
    auto camCoords = camera->getCameraCoords(this->getSubject()->getY(), this->getSubject()->getX());
    auto windowCoords = cameraToPixels(camCoords.getXCoord(), camCoords.getYCoord());

    auto sprite = std::make_shared<sf::Sprite>(*this->getTexture(), sf::IntRect(400, 250, 40, 40));
    sprite->setPosition(float(windowCoords.first), float(windowCoords.second));
    this->setSprite(sprite);
}

void GUI::GUICoin::update(const double &ticks) {
    if (!this->getSubject()->isConsumed()){
        EntityView::update(ticks);
    }
}

std::shared_ptr<Model::Coin> GUI::GUICoin::getSubject() {
    return subject.lock();
}

GUI::GUICoin::~GUICoin() = default;

