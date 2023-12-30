//
// Created by Samuel on 16/11/2023.
//

#ifndef PAC_MAN_LEVELSTATE_H
#define PAC_MAN_LEVELSTATE_H
#include "State.h"
#include "VictoryState.h"
class GUI::LevelState: public GUI::State {
public:
    LevelState(const std::weak_ptr<StateManager> &stateManager, const std::weak_ptr<Model::World> &world);

    ~LevelState() override;

    void update(const key &key) override;
};


#endif //PAC_MAN_LEVELSTATE_H
