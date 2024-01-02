//
// Created by Samuel on 21/11/2023.
//

#include "GUIGhost.h"

#include <utility>
#include "cmath"
 using namespace std;



GUI::GUIGhost::GUIGhost(const std::shared_ptr<Model::Ghost> &ghost, color ghostColor) : GUI::EntityView(ghost) {
    fearedTextureNr = 0;
    subject = ghost;
    textureNr = 0;
    spriteX = ghostColor * 50;
    auto texture = std::make_shared<sf::Texture>();
    texture->loadFromFile("Sprites.png");
    this->setTexture(texture);
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

    // Sprite aanpassen aan direction
    auto dir = this->getSubject()->getCurrentDirection();
    pixelY = dir * 100;

    // Aanpassen aan texture number
    pixelY += this->getTextureNr() * 50;

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
    if (this->getSubject()->getStateManager()->getCurrentTag() != ghostStateTag::frightened){
        this->setFearedUpdateTime(0);
    }
    // Als hij feared is, aanpassen
    if (this->getSubject()->getStateManager()->getCurrentTag() == ghostStateTag::frightened){
        pixelX = 0;
        pixelY += 550;
        auto levelNr = this->getSubject()->getWorld()->getLevelNr();
        // Als de eerste 75% van de frightened-time al voorbij is, knipper animatie:
        if (this->getSubject()->getFrightenTime() + ((5 * pow(0.9, levelNr)) * 0.75) < Model::Stopwatch::instance()->getLevelTime()){
            // Update-interval berekenen, we willen dat de animatie 5 keer (5 keer aan + uit → 10 keer updaten)
            // flikkert voor dat hij un-feared.
            double updateInterval = 5 * pow(0.9, levelNr) * 0.25 / 10;

            // Kijken of er een interval voorbij is:
            if (this->getFearedUpdateTime() + updateInterval < Model::Stopwatch::instance()->getLevelTime()){
                // Laatste updatetijd bijwerken:
                this->setFearedUpdateTime(Model::Stopwatch::instance()->getLevelTime());

                // Texture-nummer updaten
                if (this->getFearedTextureNr() == 1){
                    this->setFearedTextureNr(0);
                }
                else{
                    this->setFearedTextureNr(this->getFearedTextureNr() + 1);
                }
            }

            pixelX += this->getFearedTextureNr() * 50;
        }
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

int GUI::GUIGhost::getFearedTextureNr() const {
    return fearedTextureNr;
}

void GUI::GUIGhost::setFearedTextureNr(int nr) {
    GUIGhost::fearedTextureNr = nr;
}

double GUI::GUIGhost::getFearedUpdateTime() const {
    return fearedUpdateTime;
}

void GUI::GUIGhost::setFearedUpdateTime(double updateTime) {
    GUIGhost::fearedUpdateTime = updateTime;
}

void GUI::GUIGhost::collectableCollected(const weak_ptr<Model::Collectable> &collectable) {
    EntityView::collectableCollected(collectable);
}



