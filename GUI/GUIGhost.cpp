//
// Created by Samuel on 21/11/2023.
//

#include "GUIGhost.h"

#include <utility>





GUI::GUIGhost::GUIGhost(const std::shared_ptr<Model::Ghost>& ghost, std::weak_ptr<sf::RenderWindow> win) : GUI::EntityView(ghost, std::move(win)) {
    subject = ghost;
    textureNr = 0;
    auto texture = std::make_shared<sf::Texture>();
    texture->loadFromFile("Sprites.png");
    this->setTexture(texture);
    color ghostColor = this->getSubject()->getColor();
    if (ghostColor == color::red){
        spriteX = 0;
    }else if (ghostColor == color::pink){
        spriteX = 50;
    }else if (ghostColor == color::blue){
        spriteX = 100;
    }else {
        spriteX = 150;
    }
    auto camera = Camera::instance();
    subject = ghost;
}

std::shared_ptr<Model::Ghost> GUI::GUIGhost::getSubject(){
    return subject.lock();
}

void GUI::GUIGhost::update(const double &seconds) {
    this->updateSprite();
    auto camera = Camera::instance();
    auto camCoords = camera->getCameraCoords(this->getSubject()->getY(), this->getSubject()->getX());
    auto windowCoords = cameraToPixels(camCoords.getXCoord(), camCoords.getYCoord());
    auto sprite1 = this->getSprite();
    sprite1->setPosition(float(windowCoords.first), float(windowCoords.second));
    this->setSprite(sprite1);
    EntityView::update(seconds);
}

void GUI::GUIGhost::updateSprite() {
    sf::Sprite sprite;
    sprite = sf::Sprite(*this->getTexture(), sf::IntRect(spriteX, 0, 40, 40));
    this->setSprite(std::make_shared<sf::Sprite>(sprite));
}



