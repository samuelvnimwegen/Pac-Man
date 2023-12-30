//
// Created by Samuel on 16/11/2023.
//

#ifndef PAC_MAN_MENUSTATE_H
#define PAC_MAN_MENUSTATE_H
#include "State.h"
#include "LevelState.h"
class GUI::MenuState: public GUI::State{
public:
    MenuState(const std::weak_ptr<StateManager> &stateManager, const std::weak_ptr<Model::World> &world);

    void update(const key &key) override;

    ~MenuState() override;


};


#endif //PAC_MAN_MENUSTATE_H
