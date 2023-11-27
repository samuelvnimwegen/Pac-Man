//
// Created by Samuel on 16/11/2023.
//

#include "GUIPacMan.h"
using namespace std;


sf::Sprite GUI::GUIPacMan::getSprite() {
    sf::Sprite sprite;
    direction dir = this->getDirection();
    if (dir == direction::none){
        sprite = sf::Sprite(this->getTexture(), sf::IntRect(850, 1, 40, 40));
    }
    else if (dir == direction::right){
        if (this->getTextureNr() == 0){
           sprite = sf::Sprite(this->getTexture(), sf::IntRect(850, 51, 40, 40));
        }
        else{
            sprite = sf::Sprite(this->getTexture(), sf::IntRect(850, 101, 40, 40));
        }
    }
    else if (dir == direction::left){
        if (this->getTextureNr() == 0){
            sprite = sf::Sprite(this->getTexture(), sf::IntRect(850, 201, 40, 40));
        }
        else{
            sprite = sf::Sprite(this->getTexture(), sf::IntRect(850, 251, 40, 40));
        }
    }
    else if (dir == direction::up){
        if (this->getTextureNr() == 0){
            sprite = sf::Sprite(this->getTexture(), sf::IntRect(850, 351, 40, 40));
        }
        else{
            sprite = sf::Sprite(this->getTexture(), sf::IntRect(850, 401, 40, 40));
        }
    }
    else{
        assert(dir == direction::up);
        if (this->getTextureNr() == 0){
            sprite = sf::Sprite(this->getTexture(), sf::IntRect(850, 501, 40, 40));
        }
        else{
            sprite = sf::Sprite(this->getTexture(), sf::IntRect(850, 551, 40, 40));
        }
    }
    if (this->isHasMoved()){
        this->updateTextureNr();
    }
    return sprite;
}

GUI::GUIPacMan::GUIPacMan(){
    textureNr = 0;
    sf::Texture texture;
    texture.loadFromFile("Sprites.png");
    this->setTexture(texture);
    currentDirection = direction::none;
    hasMoved = false;
    pacMan = nullptr;
}



int GUI::GUIPacMan::getTextureNr() const {
    return textureNr;
}

void GUI::GUIPacMan::setTextureNr(int nr) {
    GUIPacMan::textureNr = nr;
}

void GUI::GUIPacMan::updateTextureNr() {
    if (textureNr < 1){
        ++textureNr;
    }
    else{
        textureNr = 0;
    }
}

direction GUI::GUIPacMan::getDirection() const {
    return currentDirection;
}

void GUI::GUIPacMan::setDirection(direction dir) {
    GUIPacMan::currentDirection = dir;
}

GUI::GUIPacMan::~GUIPacMan() = default;

direction GUI::GUIPacMan::getCurrentDirection() const {
    return currentDirection;
}

void GUI::GUIPacMan::setCurrentDirection(direction direction) {
    GUIPacMan::currentDirection = direction;
}

bool GUI::GUIPacMan::isHasMoved() const {
    return hasMoved;
}

void GUI::GUIPacMan::setHasMoved(bool moved) {
    GUIPacMan::hasMoved = moved;
}

void GUI::GUIPacMan::move() {

}
