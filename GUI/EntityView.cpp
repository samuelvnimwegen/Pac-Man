//
// Created by Samuel on 16/11/2023.
//

#include "EntityView.h"


sf::Sprite GUI::EntityView::getSprite() {
    return sprite;
}

GUI::EntityView::EntityView(){
    col = 0;
    row = 0;
}

int GUI::EntityView::getCol() const {
    return col;
}

void GUI::EntityView::setCol(int c) {
    EntityView::col = c;
}

int GUI::EntityView::getRow() const {
    return row;
}

void GUI::EntityView::setRow(int r) {
    EntityView::row = r;
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

GUI::EntityView::~EntityView() {

}

