//
// Created by Samuel on 16/11/2023.
//

#include "EntityView.h"


sf::Sprite GUI::EntityView::getSprite() {
    return sprite;
}

const sf::Texture &GUI::EntityView::getTexture() const {
    return texture;
}

void GUI::EntityView::setTexture(const sf::Texture &entityTexture) {
    EntityView::texture = entityTexture;
}

void GUI::EntityView::setSprite(const sf::Sprite &entitySprite) {
    EntityView::sprite = entitySprite;
}

GUI::EntityView::~EntityView() = default;


double GUI::EntityView::getCameraX() const {
    return cameraX;
}

void GUI::EntityView::setCameraX(double x) {
    EntityView::cameraX = x;
}

double GUI::EntityView::getCameraY() const {
    return cameraY;
}

void GUI::EntityView::setCameraY(double y) {
    EntityView::cameraY = y;
}

void GUI::EntityView::move(const int &ticks) {

}

GUI::EntityView::EntityView(const std::shared_ptr<Model::EntityModel>& subject) : subject(subject) {
    auto camera = GUI::Camera::instance();
    cameraX = camera->getCameraCoords(this->getSubject()->getRow(), this->getSubject()->getCol()).getXCoord();
    cameraY = camera->getCameraCoords(this->getSubject()->getRow(), this->getSubject()->getCol()).getYCoord();
}

std::shared_ptr<Model::EntityModel> GUI::EntityView::getSubject() const {
    return subject.lock();
}


