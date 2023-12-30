//
// Created by Samuel on 28/12/2023.
//

#include "GUIFruit.h"

GUI::GUIFruit::GUIFruit(const std::shared_ptr<Model::Fruit> &subject)
        : GUI::EntityView(subject), subject(subject){
    auto texture = std::make_shared<sf::Texture>();
    texture->loadFromFile("Sprites.png");
    this->setTexture(texture);

    auto camCoords = Camera::instance()->getCameraCoords(this->getSubject()->getY(), this->getSubject()->getX());
    auto windowCoords = cameraToPixels(camCoords.getXCoord(), camCoords.getYCoord());

    auto sprite = std::make_shared<sf::Sprite>(*this->getTexture(), sf::IntRect(400, 300, 40, 40));
    sprite->setPosition(float(windowCoords.first), float(windowCoords.second));
    this->setSprite(sprite);
}

std::shared_ptr<Model::Fruit> GUI::GUIFruit::getSubject() {
    if (subject.expired()){
        throw std::runtime_error("Subject expired at getSubject() in GUIFruit.cpp");
    }
    else{
        return subject.lock();
    }

}

void GUI::GUIFruit::update(const double &ticks) {
    if (!this->getSubject()->isConsumed()){
        EntityView::update(ticks);
    }
}

