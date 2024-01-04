//
// Created by Samuel on 16/11/2023.
//

#include "PacMan.h"
#include "Camera.h"
using namespace std;

int GUI::PacMan::getTextureNr() const {
    return textureNr;
}

void GUI::PacMan::setTextureNr(int nr) {
    PacMan::textureNr = nr;
}

void GUI::PacMan::updateTextureNr() {
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


std::shared_ptr<Model::PacMan> GUI::PacMan::getPacManModel() const {
    return pacManModel.lock();
}

GUI::PacMan::PacMan(const shared_ptr<Model::PacMan> &subject) : EntityView(subject) {
    chompSoundBuffer = make_unique<sf::SoundBuffer>();
    chompSoundBuffer->loadFromFile("../SoundEffects/pacman_chomp2.wav");
    chompSound = std::make_unique<sf::Sound>(*chompSoundBuffer);

    fruitSoundBuffer = make_unique<sf::SoundBuffer>();
    fruitSoundBuffer->loadFromFile("../SoundEffects/pacman_eatfruit.wav");
    fruitSound = std::make_unique<sf::Sound>(*fruitSoundBuffer);

    frightenedSoundBuffer = make_unique<sf::SoundBuffer>();
    frightenedSoundBuffer->loadFromFile("../SoundEffects/pacman_scaredghostsound.wav");
    frightenedSound = std::make_unique<sf::Sound>(*frightenedSoundBuffer);
    frightenedSound->setVolume(50.f);

    deathSoundBuffer = make_unique<sf::SoundBuffer>();
    deathSoundBuffer->loadFromFile("../SoundEffects/pacman_death.wav");
    deathSound = std::make_unique<sf::Sound>(*deathSoundBuffer);

    lastCoinCollected = 0;
    deadTextureNr = 0;
    textureNr = 0;
    auto texture = make_shared<sf::Texture>();
    texture->loadFromFile("../Sprites/Sprites.png");
    this->setTexture(texture);

    pacManModel = subject;
    shared_ptr<Camera> cam = Camera::instance();
}

void GUI::PacMan::update(const double &ticks) {
    if (Model::Stopwatch::instance()->getTotalSeconds() - this->getLastCoinCollected() > 0.4){
        this->chompSound->setLoop(false);
    }
    this->updateSprite();
    auto camera = Camera::instance();
    auto camCoords = camera->getCameraCoords(this->getSubject()->getY(), this->getSubject()->getX());
    auto windowCoords = cameraToPixels(camCoords.getXCoord(), camCoords.getYCoord());
    this->getSprite()->setPosition(float(windowCoords.first), float(windowCoords.second));

    int i = 0;
    bool found = false;
    auto ghosts = this->getPacManModel()->getWorld()->getGhosts();
    while (i < ghosts.size() and !found){
        auto ghost = ghosts.at(i);
        if (ghost->getStateManager()->getCurrentTag() == frightened){
            found = true;
        }
        ++i;
    }
    if (found){
        if (this->frightenedSound->getStatus() != sf::SoundSource::Playing){
            this->frightenedSound->play();
        }
    }
    else{
        this->frightenedSound->stop();
    }
    EntityView::update(ticks);
}

void GUI::PacMan::updateSprite() {
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

int GUI::PacMan::getDeadTextureNr() const {
    return deadTextureNr;
}

void GUI::PacMan::setDeadTextureNr(int nr) {
    PacMan::deadTextureNr = nr;
}

void GUI::PacMan::collectableCollected(const weak_ptr<Model::Collectable> &collectable) {
    if (collectable.lock()->getTag() == coin and this->chompSound->getStatus() != sf::SoundSource::Playing){
        this->chompSound->setLoop(true);
        this->chompSound->play();
    }
    if (collectable.lock()->getTag() == entityTag::fruit){
        this->fruitSound->play();
    }
    this->setLastCoinCollected(Model::Stopwatch::instance()->getTotalSeconds());
    EntityView::collectableCollected(collectable);
}

double GUI::PacMan::getLastCoinCollected() const {
    return lastCoinCollected;
}

void GUI::PacMan::setLastCoinCollected(double lastCollected) {
    PacMan::lastCoinCollected = lastCollected;
}

void GUI::PacMan::levelHalt() {
    this->chompSound->setLoop(false);
    this->chompSound->stop();
    this->frightenedSound->stop();
    EntityView::levelHalt();
}

void GUI::PacMan::pacManDied() {
    this->deathSound->play();
    EntityView::pacManDied();
}


GUI::PacMan::~PacMan() = default;
