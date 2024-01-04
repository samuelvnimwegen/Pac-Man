//
// Created by Samuel on 17/11/2023.
//

#include "ConcreteFactory.h"
#include "iostream"
using namespace std;

GUI::ConcreteFactory::ConcreteFactory(const std::shared_ptr<Model::World>& world): AbstractFactory(world) {}

std::shared_ptr<Model::PacMan> GUI::ConcreteFactory::createPacMan(const int &row, const int &col) {
    shared_ptr<Model::PacMan> entity(new Model::PacMan(row, col, this->getWorld()));
    shared_ptr<GUI::PacMan> observer(new GUI::PacMan(entity));
    entity->addObserver(observer);
    entity->addObserver(this->getWorld()->getScoreClass());
    this->getWorld()->setPacMan(entity);
    return entity;
}

shared_ptr<Model::Wall> GUI::ConcreteFactory::createWall(const int &row, const int &col) {
    shared_ptr<Model::Wall> subject(new Model::Wall(row, col));
    shared_ptr<GUI::Wall> observer(new GUI::Wall(subject, this->getWorld()));
    subject->addObserver(observer);
    this->getWorld()->addItem(subject);
    this->getWorld()->addWall(subject);
    return subject;
}

shared_ptr<Model::Coin> GUI::ConcreteFactory::createCoin(const int &row, const int &col) {
    shared_ptr<Model::Coin> entity(new Model::Coin(row, col));
    shared_ptr<GUI::Coin> observer(new GUI::Coin(entity));
    entity->addObserver(observer);
    this->getWorld()->addItem(entity);
    this->getWorld()->addCoin(entity);
    return entity;
}

std::shared_ptr<Model::Fruit> GUI::ConcreteFactory::createFruit(const int &row, const int &col) {
    shared_ptr<Model::Fruit> entity(new Model::Fruit(row, col));
    shared_ptr<GUI::Fruit> observer(new GUI::Fruit(entity));
    entity->addObserver(observer);
    this->getWorld()->addItem(entity);
    this->getWorld()->addFruit(entity);
    return entity;
}

shared_ptr<Model::Ghost> GUI::ConcreteFactory::createGhost(const int &row, const int &col) {
    shared_ptr<Model::Ghost> entity(new Model::Ghost(row, col, this->getWorld()));
    entity->getStateManager()->push(make_unique<Model::GhostIdleState>(entity->getStateManager(), entity));
    int ghostSize = int(this->getWorld()->getGhosts().size());

    // Kleur van het viewEntity kiezen
    color ghostColor;
    switch (ghostSize) {
        case 0:
            ghostColor = color::red;
            entity->setStartDirection(direction::right);
            break;
        case 1:
            ghostColor = color::pink;
            break;
        case 2:
            ghostColor = color::blue;
            break;
        case 3:
            ghostColor = color::orange;
            entity->setStartDirection(direction::left);
            break;
        case 4:
            ghostColor = color::green;
            break;
        default:
            ghostColor = color::purple;
    }

    // Wachttijd waarin de ghost idle is aanpassen: 3 seconden meer dan vorige ghost die is toegevoegd
    if (this->getWorld()->getGhosts().size() <= 1){
        entity->setWaitTime(0);
    }
    else{
        double waitTime = entity->getWorld()->getGhosts().at(entity->getWorld()->getGhosts().size() - 1)->getWaitTime();
        entity->setWaitTime(waitTime + 5);
    }
    shared_ptr<GUI::Ghost> observer(new GUI::Ghost(entity, ghostColor));
    entity->addObserver(observer);
    this->getWorld()->addGhost(entity);
    return entity;
}

std::shared_ptr<Model::EscapeWall> GUI::ConcreteFactory::createEscapeWall(const int &row, const int &col) {
    shared_ptr<Model::EscapeWall> subject(new Model::EscapeWall(row, col));
    shared_ptr<GUI::EscapeWall> observer(new GUI::EscapeWall(subject));
    subject->addObserver(observer);
    this->getWorld()->addItem(subject);
    this->getWorld()->addWall(subject);
    return subject;
}











