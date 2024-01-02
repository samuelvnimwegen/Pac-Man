//
// Created by Samuel on 16/11/2023.
//

#include "PausedState.h"
#include "StateManager.h"
#include "../Model/World.h"

GUI::PausedState::PausedState(const std::weak_ptr<StateManager> &stateManager, const std::weak_ptr<Model::World> &world)
        : State(stateManager, world) {
    this->setTag(paused);
    pausedTime = Model::Stopwatch::instance()->getLevelTime();
    Model::Stopwatch::instance()->pause();
}

void GUI::PausedState::update(const key &key) {
    if (this->getStateManager().lock() and this->getWorld().lock()){
        auto stateManager = this->getStateManager().lock();
        auto world = this->getWorld().lock();
        // Als er opnieuw escape wordt geduwd en er is 0.5 seconde voorbij (om dubbele clicks te voorkomen): poppen tot
        // stacks size 1 heeft:
        if (key == escape and (Model::Stopwatch::instance()->getLevelTime() - this->getPausedTime()) > 0.5){
            while (stateManager->getSize() > 1){
                world->restart();
                world->getScoreClass()->restart();
                stateManager->pop();
            }
        }
        // Bij unpause stack 1 keer poppen
        else if (key == space){
            Model::Stopwatch::instance()->unpause();
            Model::Stopwatch::instance()->getDeltaTime();
            stateManager->pop();
        }
    }


}

double GUI::PausedState::getPausedTime() const {
    return pausedTime;
}

GUI::PausedState::~PausedState() = default;
