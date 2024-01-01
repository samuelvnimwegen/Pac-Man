//
// Created by Samuel on 21/11/2023.
//

#include "GUIGhost.h"

#include <utility>





GUI::GUIGhost::GUIGhost(const std::shared_ptr<Model::Ghost> &ghost, color ghostColor) : GUI::EntityView(ghost) {
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
    scoreTexture = std::make_shared<sf::Texture>();
    scoreTexture->loadFromFile("100_glowing.png");
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
    int pixelY;
    auto dir = this->getSubject()->getCurrentDirection();
    switch (dir) {
        case direction::right:
            pixelY = 0;
            break;
        case direction::down:
            pixelY = 100;
            break;
        case direction::left:
            pixelY = 200;
            break;
        case direction::up:
            pixelY = 300;
            break;
        case direction::none:
            throw std::runtime_error("Ghost had geen direction bij updateSprite van GUIGhost.cpp");
    }
    if (this->getTextureNr() == 1){
        pixelY += 50;
    }
    // Texture nummer bijwerken als game gestart is en er 0.075 seconden sinds laatste update voorbij is
    static double lastUpdated = Model::Stopwatch::instance()->getTotalSeconds();
    if (this->getSubject()->getWorld()->isGameStarted() and lastUpdated + 0.075 < Model::Stopwatch::instance()->getTotalSeconds()){
        if (this->getTextureNr() == 0){
            this->setTextureNr(1);
        }
        else{
            this->setTextureNr(0);
        }
        lastUpdated = Model::Stopwatch::instance()->getTotalSeconds();
    }
    auto pixelX = getSpriteX();

    // Als hij feared is, aanpassen
    if (this->getSubject()->getStateManager()->getCurrentTag() == ghostStateTag::frightened){
        pixelX = 0;
        pixelY += 550;
    }
    // Als hij aan het resetten is, aanpassen
    else if (this->getSubject()->getStateManager()->getCurrentTag() == ghostStateTag::reset){
        pixelX = 300;
        pixelY = 250 + dir * 50;
    }

    // Als de ghost is opgegeten score displayen van 100 i.p.v. sprite
    if (this->getSubject()->getStateManager()->getCurrentTag() == ghostStateTag::eaten){
        sprite = sf::Sprite(*this->getScoreTexture());
        this->setSprite(std::make_shared<sf::Sprite>(sprite));
    }
    else{
        sprite = sf::Sprite(*this->getTexture(), sf::IntRect(pixelX, pixelY, 40, 40));
        this->setSprite(std::make_shared<sf::Sprite>(sprite));
    }



}

const std::shared_ptr<sf::Texture> &GUI::GUIGhost::getScoreTexture() const {
    return scoreTexture;
}

int GUI::GUIGhost::getTextureNr() const {
    return textureNr;
}

void GUI::GUIGhost::setTextureNr(int nr) {
    GUIGhost::textureNr = nr;
}

int GUI::GUIGhost::getSpriteX() const {
    return spriteX;
}



