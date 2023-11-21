//
// Created by Samuel on 16/11/2023.
//

#include "EntityView.h"


sf::Sprite EntityView::getSprite() {
    return sprite;
}

EntityView::EntityView(){
    col = 0;
    row = 0;
}

int EntityView::getCol() const {
    return col;
}

void EntityView::setCol(int c) {
    EntityView::col = c;
}

int EntityView::getRow() const {
    return row;
}

void EntityView::setRow(int r) {
    EntityView::row = r;
}

const sf::Texture &EntityView::getTexture() const {
    return texture;
}

void EntityView::setTexture(const sf::Texture &entityTexture) {
    EntityView::texture = entityTexture;
}

void EntityView::setSprite(const sf::Sprite &entitySprite) {
    EntityView::sprite = entitySprite;
}

void EntityView::removeSprite() {
    sf::Texture tex;
    tex.loadFromFile("Sprites.png");
    this->setTexture(tex);
    sf::Sprite spr(this->getTexture(), sf::IntRect(0, 0, 1, 1));
    this->setSprite(spr);
}

EntityView::~EntityView() {

}

