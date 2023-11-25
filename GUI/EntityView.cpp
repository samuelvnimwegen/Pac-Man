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

void GUI::EntityView::removeSprite() {
    sf::Texture tex;
    tex.loadFromFile("Sprites.png");
    this->setTexture(tex);
    sf::Sprite spr(this->getTexture(), sf::IntRect(0, 0, 1, 1));
    this->setSprite(spr);
}

GUI::EntityView::~EntityView() = default;

GUI::EntityView::EntityView() {
    cameraX = 0;
    cameraY = 0;
}

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

