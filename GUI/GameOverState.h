//
// Created by Samuel on 31/12/2023.
//

#ifndef PAC_MAN_GAMEOVERSTATE_H
#define PAC_MAN_GAMEOVERSTATE_H
#include "State.h"

class GUI::GameOverState: public GUI::State{
public:
    GameOverState(const std::weak_ptr<StateManager> &stateManager, const std::weak_ptr<Model::World> &world);

    void update(const key &key) override;
};


#endif //PAC_MAN_GAMEOVERSTATE_H
