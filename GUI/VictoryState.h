//
// Created by Samuel on 16/11/2023.
//

#ifndef PAC_MAN_VICTORYSTATE_H
#define PAC_MAN_VICTORYSTATE_H
#include "State.h"

class GUI::VictoryState: public GUI::State {
public:
    VictoryState(const std::weak_ptr<StateManager> &stateManager, const std::weak_ptr<Model::World> &world);

    void update(const key &key) override;

    ~VictoryState() override;

};


#endif //PAC_MAN_VICTORYSTATE_H
