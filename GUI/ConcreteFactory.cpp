//
// Created by Samuel on 17/11/2023.
//

#include "ConcreteFactory.h"
#include "iostream"
using namespace std;

GUI::ConcreteFactory::ConcreteFactory(Model::World *world) : AbstractFactory(world) {}

unique_ptr<Model::PacMan> GUI::ConcreteFactory::createPacMan(const int &row, const int &col) {
    unique_ptr<Model::PacMan> entity(new Model::PacMan(row, col, this->getWorld()));
    unique_ptr<GUI::GUIPacMan> observer(new GUI::GUIPacMan(entity));
    entity->addObserver(observer);
    this->getWorld()->addItem(entity);
    this->getWorld()->setPacMan(entity);
    return entity;
}

Model::Wall *GUI::ConcreteFactory::createWall(const int &row, const int &col) {
    auto* subject = new Model::Wall(row, col);
    auto observer = new GUI::GUIWall(subject);
    subject->addObserver(observer);
    this->getWorld()->addItem(subject);
    this->getWorld()->addWall(subject);
    return subject;
}

Model::Coin *GUI::ConcreteFactory::createCoin(const int &row, const int &col) {
    auto entity = new Model::Coin(row, col);
    auto observer = new GUI::GUICoin(entity);
    entity->addObserver(observer);
    this->getWorld()->addItem(entity);
    this->getWorld()->addCoin(entity);
    return entity;
}

Model::Ghost *GUI::ConcreteFactory::createGhost(const int &row, const int &col) {
    auto entity = new Model::Ghost(row, col, this->getWorld());
    auto observer = new GUI::GUIGhost(entity);
    entity->addObserver(observer);
    this->getWorld()->addItem(entity);
    this->getWorld()->addGhost(entity);
    return entity;
}










