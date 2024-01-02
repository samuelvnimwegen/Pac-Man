//
// Created by Samuel on 16/11/2023.
//

#include "GUIPacMan.h"
#include "Camera.h"
using namespace std;








int GUI::GUIPacMan::getTextureNr() const {
    return textureNr;
}

void GUI::GUIPacMan::setTextureNr(int nr) {
    GUIPacMan::textureNr = nr;
}

void GUI::GUIPacMan::updateTextureNr() {
    if (this->getPacManModel()->isDead()){
        double interval = 2.0 / 11;
        if ((this->getDeadTextureNr() + 1) * interval < Model::Stopwatch::instance()->getLevelTime() - this->getPacManModel()->getDeathTime()){
            this->setDeadTextureNr(this->getDeadTextureNr() + 1);
        }
        if (this->getDeadTextureNr() > 10){
            this->setDeadTextureNr(0);
        }
    }
    else{
        static double lastUpdated = Model::Stopwatch::instance()->getTotalSeconds();
        // Elke 0.05 seconden de sprite bijwerken
        if (lastUpdated + 0.075 < Model::Stopwatch::instance()->getTotalSeconds()){
            if (this->getDeadTextureNr() != 0){
                this->setDeadTextureNr(0);
            }
            if (this->getTextureNr() < 1 and 0 <= this->getTextureNr()){
                this->setTextureNr(this->getTextureNr() + 1);
            }
            else{
                this->setTextureNr(0);
            }
            lastUpdated = Model::Stopwatch::instance()->getTotalSeconds();
        }
    }
}


std::shared_ptr<Model::PacMan> GUI::GUIPacMan::getPacManModel() const {
    return pacManModel.lock();
}

GUI::GUIPacMan::GUIPacMan(const shared_ptr<Model::PacMan> &subject) : EntityView(subject) {
    deadTextureNr = 0;
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

    if (this->getPacManModel()->isDead()){
        int spriteY = this->getDeadTextureNr() * 50;
        sprite = sf::Sprite(*this->getTexture(), sf::IntRect(350, spriteY, 40, 40));
    }
    else{
        // Sprite aanpassen aan richting en texture nummer (plaats in animatie)
        direction dir = this->getPacManModel()->getCurrentDirection();
        if (dir == direction::none){
            sprite = sf::Sprite(*this->getTexture(), sf::IntRect(850, 0, 40, 40));
        }
        else{
            int spriteY = 50 + 150 * dir + this->getTextureNr() * 50;
            sprite = sf::Sprite(*this->getTexture(), sf::IntRect(850, spriteY, 40, 40));
        }
    }
    if (this->getPacManModel()->isHasMoved() or this->getPacManModel()->isDead()){
        this->updateTextureNr();
    }
    this->setSprite(make_shared<sf::Sprite>(sprite));
}

int GUI::GUIPacMan::getDeadTextureNr() const {
    return deadTextureNr;
}

void GUI::GUIPacMan::setDeadTextureNr(int nr) {
    GUIPacMan::deadTextureNr = nr;
}

GUI::GUIPacMan::~GUIPacMan() = default;
