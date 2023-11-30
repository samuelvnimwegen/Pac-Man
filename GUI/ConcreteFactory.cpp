//
// Created by Samuel on 17/11/2023.
//

#include "ConcreteFactory.h"


GUI::ConcreteFactory::ConcreteFactory(Model::World *world) : AbstractFactory(world) {
    camera = GUI::Camera::instance();
}

Model::PacMan *GUI::ConcreteFactory::createPacMan(const int &row, const int &col) {
    auto* entity = new Model::PacMan(row, col, this->getWorld());
    auto observer = new GUI::GUIPacMan(entity);
    entity->addObserver(observer);
    this->getWorld()->addItem(entity);
    this->getWorld()->setPacMan(entity);
    observer->setCameraX(this->getCamera()->getCameraCoords(row, col).getXCoord());
    observer->setCameraY(this->getCamera()->getCameraCoords(row, col).getYCoord());
    return entity;
}

Model::Wall *GUI::ConcreteFactory::createWall(const int &row, const int &col) {
    auto* subject = new Model::Wall(row, col);
    auto observer = new GUI::GUIWall();
    subject->addObserver(observer);
    this->getWorld()->addItem(subject);
    this->getWorld()->addWall(subject);
    observer->setCameraX(this->getCamera()->getCameraCoords(row, col).getXCoord());
    observer->setCameraY(this->getCamera()->getCameraCoords(row, col).getYCoord());

    return subject;
}

Model::Coin *GUI::ConcreteFactory::createCoin(const int &row, const int &col) {
    auto entity = new Model::Coin(row, col);
    auto observer = new GUI::GUIWall;
    entity->addObserver(observer);
    this->getWorld()->addItem(entity);
    observer->setCameraX(this->getCamera()->getCameraCoords(row, col).getXCoord());
    observer->setCameraY(this->getCamera()->getCameraCoords(row, col).getYCoord());
    return entity;
}

Model::Ghost *GUI::ConcreteFactory::createGhost(const int &row, const int &col) {
    auto entity = new Model::Ghost(row, col, this->getWorld());
    auto observer = new GUI::GUIWall;
    entity->addObserver(observer);
    this->getWorld()->addItem(entity);
    observer->setCameraX(this->getCamera()->getCameraCoords(row, col).getXCoord());
    observer->setCameraY(this->getCamera()->getCameraCoords(row, col).getYCoord());
    return entity;
}

GUI::Camera *GUI::ConcreteFactory::getCamera() const {
    return camera;
}









