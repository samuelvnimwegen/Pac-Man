//
// Created by Samuel on 17/11/2023.
//

#include "ConcreteFactory.h"
#include "iostream"
using namespace std;

GUI::ConcreteFactory::ConcreteFactory(const std::shared_ptr<Model::World>& world, const std::shared_ptr<sf::RenderWindow>& win): AbstractFactory(world), window(win) {}

shared_ptr<Model::PacMan> GUI::ConcreteFactory::createPacMan(const int &row, const int &col) {
    shared_ptr<Model::PacMan> entity(new Model::PacMan(row, col, this->getWorld()));
    shared_ptr<GUI::GUIPacMan> observer(new GUI::GUIPacMan(entity, this->getWindow()));
    entity->addObserver(observer);
    this->getWorld()->setPacMan(entity);
    return entity;
}

shared_ptr<Model::Wall> GUI::ConcreteFactory::createWall(const int &row, const int &col) {
    shared_ptr<Model::Wall> subject(new Model::Wall(row, col));
    shared_ptr<GUI::GUIWall> observer(new GUI::GUIWall(subject, this->getWindow()));
    subject->addObserver(observer);
    this->getWorld()->addItem(subject);
    this->getWorld()->addWall(subject);
    return subject;
}

shared_ptr<Model::Coin> GUI::ConcreteFactory::createCoin(const int &row, const int &col) {
    shared_ptr<Model::Coin> entity(new Model::Coin(row, col));
    shared_ptr<GUI::GUICoin> observer(new GUI::GUICoin(entity, this->getWindow()));
    entity->addObserver(observer);
    this->getWorld()->addItem(entity);
    this->getWorld()->addCoin(entity);
    return entity;
}

shared_ptr<Model::Ghost> GUI::ConcreteFactory::createGhost(const int &row, const int &col) {
    shared_ptr<Model::Ghost> entity(new Model::Ghost(row, col, this->getWorld()));
    shared_ptr<GUI::GUIGhost> observer(new GUI::GUIGhost(entity, this->getWindow()));
    entity->addObserver(observer);
    this->getWorld()->addGhost(entity);
    return entity;
}

const shared_ptr<sf::RenderWindow> &GUI::ConcreteFactory::getWindow() const {
    return window;
}










