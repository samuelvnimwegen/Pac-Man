//
// Created by Samuel on 31/12/2023.
//

#include "GameOverState.h"
#include "../World.h"
#include "StateManager.h"

GUI::GameOverState::GameOverState(const std::weak_ptr<StateManager> &stateManager,
                                  const std::weak_ptr<Model::World> &world) : State(stateManager, world) {
    this->setTag(gameOver);
}

void GUI::GameOverState::update(const key &key) {
    // Als er spatie is ingeduwd teruggaan naar menu
    if (key == space){
        this->getWorld().lock()->restartWorld();
        while(this->getStateManager().lock()->getCurrentTag() != menu){
            this->getStateManager().lock()->pop();
        }
    }
}
