//
// Created by Samuel on 03/01/2024.
//

#include "GUIEscapeWall.h"
#include "Camera.h"

GUI::GUIEscapeWall::GUIEscapeWall(const std::shared_ptr<Model::EscapeWall> &sub) : GUI::EntityView(sub) {
    auto texture = std::make_shared<sf::Texture>();
    texture->loadFromFile("../Sprites/EscapeWall.png");
    this->setTexture(texture);

    auto camera = Camera::instance();
    auto camCoords = camera->getCameraCoords(this->getSubject()->getY(), this->getSubject()->getX());
    auto windowCoords = cameraToPixels(camCoords.getXCoord(), camCoords.getYCoord());

    auto sprite = std::make_shared<sf::Sprite>(*this->getTexture());
    sprite->setPosition(float(windowCoords.first), float(windowCoords.second));
    this->setSprite(sprite);
}

void GUI::GUIEscapeWall::collectableCollected(const std::weak_ptr<Model::Collectable> &collectable) {
    EntityView::collectableCollected(collectable);
}

void GUI::GUIEscapeWall::update(const double &ticks) {
    EntityView::update(ticks);
}

std::shared_ptr<Model::EntityModel> GUI::GUIEscapeWall::getSubject() const {
    return EntityView::getSubject();
}

std::shared_ptr<sf::Sprite> GUI::GUIEscapeWall::getSprite() {
    return EntityView::getSprite();
}


