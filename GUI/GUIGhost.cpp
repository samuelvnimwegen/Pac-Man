//
// Created by Samuel on 21/11/2023.
//

#include "GUIGhost.h"

#include <utility>





GUI::GUIGhost::GUIGhost(const std::shared_ptr<Model::Ghost> &ghost, std::weak_ptr<sf::RenderWindow> win,
                        color ghostColor) : GUI::EntityView(ghost, std::move(win)) {
    subject = ghost;
    textureNr = 0;
    auto texture = std::make_shared<sf::Texture>();
    texture->loadFromFile("Sprites.png");
    this->setTexture(texture);
    switch (ghostColor) {
        case color::red:
            spriteX = 0;
            break;
        case color::pink:
            spriteX = 50;
            break;
        case color::blue:
            spriteX = 100;
            break;
        case color::orange:
            spriteX = 150;
            break;
        case color::green:
            spriteX = 200;
            break;
        case color::purple:
            spriteX = 250;
            break;
    }
    auto camera = Camera::instance();
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
    int spriteY;
    auto dir = this->getSubject()->getCurrentDirection();
    if (dir == direction::right){
        spriteY = 0;
    }
    else if (dir == direction::down){
        spriteY = 100;
    }
    else if (dir == direction::left){
        spriteY = 200;
    }
    else{
        assert(dir == direction::up);
        spriteY = 300;
    }
    if (this->textureNr == 1){
        spriteY += 50;
    }
    // Texture nummer bijwerken als game gestart is
    if (this->getSubject()->getWorld()->isGameStarted()){
        if (this->textureNr == 0){
            this->textureNr = 1;
        }
        else{
            this->textureNr = 0;
        }
    }
    sprite = sf::Sprite(*this->getTexture(), sf::IntRect(spriteX, spriteY, 40, 40));
    this->setSprite(std::make_shared<sf::Sprite>(sprite));
}



