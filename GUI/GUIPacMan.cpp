//
// Created by Samuel on 16/11/2023.
//

#include "GUIPacMan.h"

#include <utility>
using namespace std;








int GUI::GUIPacMan::getTextureNr() const {
    return textureNr;
}

void GUI::GUIPacMan::setTextureNr(int nr) {
    GUIPacMan::textureNr = nr;
}

void GUI::GUIPacMan::updateTextureNr() {
    if (this->getTextureNr() < 1){
        this->setTextureNr(this->getTextureNr() + 1);
    }
    else{
        this->setTextureNr(0);
    }
}


std::shared_ptr<Model::PacMan> GUI::GUIPacMan::getPacManModel() const {
    return pacManModel.lock();
}

GUI::GUIPacMan::GUIPacMan(const shared_ptr<Model::PacMan>& subject, std::weak_ptr<sf::RenderWindow> win) : EntityView(subject, std::move(win)) {
    textureNr = 0;
    auto texture = make_shared<sf::Texture>();
    texture->loadFromFile("Sprites.png");
    this->setTexture(texture);
    pacManModel = subject;
    shared_ptr<Camera> cam = Camera::instance();
}

void GUI::GUIPacMan::update(const double &ticks) {
    this->updateSprite();
    auto camera = Camera::instance();
    auto camCoords = camera->getCameraCoords(this->getSubject()->getY(), this->getSubject()->getX());
    auto windowCoords = cameraToPixels(camCoords.getXCoord(), camCoords.getYCoord());
    this->getSprite()->setPosition(float(windowCoords.first), float(windowCoords.second));
    EntityView::update(ticks);
}

void GUI::GUIPacMan::updateSprite() {
    sf::Sprite sprite;
    direction dir = this->getPacManModel()->getCurrentDirection();
    if (dir == direction::none){
        sprite = sf::Sprite(*this->getTexture(), sf::IntRect(850, 1, 40, 40));
    }
    else if (dir == direction::right){
        if (this->getTextureNr() == 0){
            sprite = sf::Sprite(*this->getTexture(), sf::IntRect(850, 51, 40, 40));
        }
        else{
            sprite = sf::Sprite(*this->getTexture(), sf::IntRect(850, 101, 40, 40));
        }
    }
    else if (dir == direction::down){
        if (this->getTextureNr() == 0){
            sprite = sf::Sprite(*this->getTexture(), sf::IntRect(850, 201, 40, 40));
        }
        else{
            sprite = sf::Sprite(*this->getTexture(), sf::IntRect(850, 251, 40, 40));
        }
    }
    else if (dir == direction::left){
        if (this->getTextureNr() == 0){
            sprite = sf::Sprite(*this->getTexture(), sf::IntRect(850, 351, 40, 40));
        }
        else{
            sprite = sf::Sprite(*this->getTexture(), sf::IntRect(850, 401, 40, 40));
        }
    }
    else{
        assert(dir == direction::up);
        if (this->getTextureNr() == 0){
            sprite = sf::Sprite(*this->getTexture(), sf::IntRect(850, 501, 40, 40));
        }
        else{
            sprite = sf::Sprite(*this->getTexture(), sf::IntRect(850, 551, 40, 40));
        }
    }
    if (this->getPacManModel()->isHasMoved()){
        this->updateTextureNr();
    }
    this->setSprite(make_shared<sf::Sprite>(sprite));
}

GUI::GUIPacMan::~GUIPacMan() = default;
