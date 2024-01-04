//
// Created by Samuel on 16/11/2023.
//

#include "GUIWall.h"

#include <memory>
#include "Camera.h"

GUI::GUIWall::~GUIWall() = default;



void GUI::GUIWall::updateWall() {
    auto row = toTile(this->getSubject()->getY());
    auto col = toTile(this->getSubject()->getX());
    std::string nameString;
    if (row != 0 and this->getWorld().lock()->getItem(row - 1, col) != nullptr and this->getWorld().lock()->getItem(row - 1, col)->getTag() == wall){
        nameString += "Up";
    }
    if (row != this->getWorld().lock()->getHeight() - 1 and this->getWorld().lock()->getItem(row + 1, col) != nullptr and this->getWorld().lock()->getItem(row + 1, col)->getTag() == wall){
        nameString += "Down";
    }
    if (col != 0 and this->getWorld().lock()->getItem(row, col - 1) != nullptr and this->getWorld().lock()->getItem(row, col - 1)->getTag() == wall){
        nameString += "Left";
    }
    if (col != this->getWorld().lock()->getWidth() - 1 and this->getWorld().lock()->getItem(row, col + 1) != nullptr and this->getWorld().lock()->getItem(row, col + 1)->getTag() == wall){
        nameString += "Right";
    }
    if (nameString.empty()){
        nameString = "None";
    }
    nameString = "Sprites/Walls/" + nameString + ".png";
    auto texture = std::make_shared<sf::Texture>();
    texture->loadFromFile(nameString);
    this->setTexture(texture);

    auto camera = Camera::instance();
    auto camCoords = camera->getCameraCoords(this->getSubject()->getY(), this->getSubject()->getX());
    auto windowCoords = cameraToPixels(camCoords.getXCoord(), camCoords.getYCoord());

    auto sprite = std::make_shared<sf::Sprite>(*this->getTexture());
    sprite->setPosition(float(windowCoords.first), float(windowCoords.second));
    this->setSprite(sprite);
}

void GUI::GUIWall::update(const double &ticks) {
    if (!this->isWallUpdated()){
        this->updateWall();
        this->setWallUpdated(true);
    }
    EntityView::update(ticks);
}

GUI::GUIWall::GUIWall(const std::shared_ptr<Model::EntityModel> &subject, const std::weak_ptr<Model::World> &world)
        : EntityView(subject), world(world) {
    wallUpdated = false;
    auto texture = std::make_shared<sf::Texture>();
    texture->loadFromFile("Sprites/Muur2.png");
    this->setTexture(texture);

    auto camera = Camera::instance();
    auto camCoords = camera->getCameraCoords(this->getSubject()->getY(), this->getSubject()->getX());
    auto windowCoords = cameraToPixels(camCoords.getXCoord(), camCoords.getYCoord());

    auto sprite = std::make_shared<sf::Sprite>(*this->getTexture());
    sprite->setPosition(float(windowCoords.first), float(windowCoords.second));
    this->setSprite(sprite);
}

const std::weak_ptr<Model::World> &GUI::GUIWall::getWorld() const {
    return world;
}

bool GUI::GUIWall::isWallUpdated() const {
    return wallUpdated;
}

void GUI::GUIWall::setWallUpdated(bool updated) {
    GUIWall::wallUpdated = updated;
}



