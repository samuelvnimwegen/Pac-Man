//
// Created by Samuel on 21/11/2023.
//

#include "Ghost.h"

#include "cmath"
#include "Camera.h"
 using namespace std;



GUI::Ghost::Ghost(const std::shared_ptr<Model::Ghost> &ghost, color ghostColor) : GUI::EntityView(ghost) {
    walkLastUpdated = 0;
    fearedUpdateTime = 0;
    fearedTextureNr = 0;
    subject = ghost;
    textureNr = 0;
    spriteX = ghostColor * 50;

    ghostEatenSoundBuffer = make_unique<sf::SoundBuffer>();
    ghostEatenSoundBuffer->loadFromFile("../SoundEffects/pacman_eatghost.wav");
    ghostEatenSound = make_unique<sf::Sound>(*ghostEatenSoundBuffer);

    auto texture = std::make_shared<sf::Texture>();
    texture->loadFromFile("../Sprites/Sprites.png");
    this->setTexture(texture);
    auto camera = Camera::instance();
    scoreTexture = std::make_shared<sf::Texture>();
    scoreTexture->loadFromFile("../Sprites/100_glowing.png");
}

std::shared_ptr<Model::Ghost> GUI::Ghost::getSubject(){
    return subject.lock();
}

void GUI::Ghost::update(const double &seconds) {
    this->updateSprite();
    auto camera = Camera::instance();
    auto camCoords = camera->getCameraCoords(this->getSubject()->getY(), this->getSubject()->getX());
    auto windowCoords = cameraToPixels(camCoords.getXCoord(), camCoords.getYCoord());
    auto sprite1 = this->getSprite();
    sprite1->setPosition(float(windowCoords.first), float(windowCoords.second));
    this->setSprite(sprite1);
    EntityView::update(seconds);
}

void GUI::Ghost::updateSprite() {
    sf::Sprite sprite;
    int pixelY;

    // Sprite aanpassen aan direction
    auto dir = this->getSubject()->getCurrentDirection();
    pixelY = dir * 100;

    // Aanpassen aan texture number
    pixelY += this->getTextureNr() * 50;

    // Texture nummer bijwerken als game gestart is en er 0.075 seconden sinds laatste update voorbij is
    if (this->getSubject()->getWorld()->isGameStarted() and this->getWalkLastUpdated() + 0.075 < Model::Stopwatch::instance()->getTotalSeconds()){
        if (this->getTextureNr() == 0){
            this->setTextureNr(1);
        }
        else{
            this->setTextureNr(0);
        }
        this->setWalkLastUpdated(Model::Stopwatch::instance()->getTotalSeconds());
    }

    auto pixelX = getSpriteX();
    if (this->getSubject()->getStateManager()->getCurrentTag() != ghostStateTag::frightened and this->getSubject()->getStateManager()->getCurrentTag() != ghostStateTag::idleFrightened){
        this->setFearedUpdateTime(0);
    }
    // Als hij feared is, aanpassen
    if (this->getSubject()->getStateManager()->getCurrentTag() == ghostStateTag::frightened or this->getSubject()->getStateManager()->getCurrentTag() == ghostStateTag::idleFrightened){
        pixelX = 0;
        pixelY += 550;
        auto levelNr = this->getSubject()->getWorld()->getLevelNr();
        // Als de eerste 75% van de frightened-time al voorbij is, knipper animatie:
        if (this->getSubject()->getFrightenTime() + ((7 * pow(0.9, levelNr)) * 0.75) < Model::Stopwatch::instance()->getLevelTime()){
            // Update-interval berekenen, we willen dat de animatie 5 keer (5 keer aan + uit → 10 keer updaten)
            // flikkert voor dat hij un-feared.
            double updateInterval = 7 * pow(0.9, levelNr) * 0.25 / 10;

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
        this->setFearedTextureNr(0);
    }
    else if (this->getSubject()->getStateManager()->getCurrentTag() == ghostStateTag::idle){
        pixelY = 0;
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

const std::shared_ptr<sf::Texture> &GUI::Ghost::getScoreTexture() const {
    return scoreTexture;
}

int GUI::Ghost::getTextureNr() const {
    return textureNr;
}

void GUI::Ghost::setTextureNr(int nr) {
    Ghost::textureNr = nr;
}

int GUI::Ghost::getSpriteX() const {
    return spriteX;
}

int GUI::Ghost::getFearedTextureNr() const {
    return fearedTextureNr;
}

void GUI::Ghost::setFearedTextureNr(int nr) {
    Ghost::fearedTextureNr = nr;
}

double GUI::Ghost::getFearedUpdateTime() const {
    return fearedUpdateTime;
}

void GUI::Ghost::setFearedUpdateTime(double updateTime) {
    Ghost::fearedUpdateTime = updateTime;
}

void GUI::Ghost::collectableCollected(const weak_ptr<Model::Collectable> &collectable) {
    EntityView::collectableCollected(collectable);
}

double GUI::Ghost::getWalkLastUpdated() const {
    return walkLastUpdated;
}

void GUI::Ghost::setWalkLastUpdated(double lastUpdated) {
    Ghost::walkLastUpdated = lastUpdated;
}

void GUI::Ghost::ghostEaten() {
    this->ghostEatenSound->play();
    EntityView::ghostEaten();
}



