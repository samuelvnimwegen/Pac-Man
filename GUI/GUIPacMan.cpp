//
// Created by Samuel on 16/11/2023.
//

#include "GUIPacMan.h"


sf::Sprite GUI::GUIPacMan::getSprite() {
    sf::Sprite sprite;
    string direction = this->getSubject()->getCurrentDirection();
    if (direction == "NONE"){
        sprite = sf::Sprite(this->getTexture(), sf::IntRect(850, 1, 40, 40));
    }
    else if (direction == "RIGHT"){
        if (this->getTextureNr() == 0){
           sprite = sf::Sprite(this->getTexture(), sf::IntRect(850, 51, 40, 40));
        }
        else{
            sprite = sf::Sprite(this->getTexture(), sf::IntRect(850, 101, 40, 40));
        }
    }
    else if (direction == "DOWN"){
        if (this->getTextureNr() == 0){
            sprite = sf::Sprite(this->getTexture(), sf::IntRect(850, 201, 40, 40));
        }
        else{
            sprite = sf::Sprite(this->getTexture(), sf::IntRect(850, 251, 40, 40));
        }
    }
    else if (direction == "LEFT"){
        if (this->getTextureNr() == 0){
            sprite = sf::Sprite(this->getTexture(), sf::IntRect(850, 351, 40, 40));
        }
        else{
            sprite = sf::Sprite(this->getTexture(), sf::IntRect(850, 401, 40, 40));
        }
    }
    else{
        assert(direction == "UP");
        if (this->getTextureNr() == 0){
            sprite = sf::Sprite(this->getTexture(), sf::IntRect(850, 501, 40, 40));
        }
        else{
            sprite = sf::Sprite(this->getTexture(), sf::IntRect(850, 551, 40, 40));
        }
    }
    if (this->getSubject()->isHasMoved()){
        this->updateTextureNr();
    }
    return sprite;
}

GUI::GUIPacMan::GUIPacMan(PacMan *subject) : subject(subject) {
    this->setRow(subject->getRow());
    this->setCol(subject->getCol());
    textureNr = 0;
    sf::Texture texture;
    texture.loadFromFile("Sprites.png");
    this->setTexture(texture);
}

PacMan *GUI::GUIPacMan::getSubject() const {
    return subject;
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

GUI::GUIPacMan::~GUIPacMan() {

}
