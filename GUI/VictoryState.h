//
// Created by Samuel on 16/11/2023.
//

#ifndef PAC_MAN_VICTORYSTATE_H
#define PAC_MAN_VICTORYSTATE_H
#include "State.h"

class GUI::VictoryState: public GUI::State {
    double victoryTime;
public:
    VictoryState(const std::weak_ptr<StateManager> &stateManager, const std::weak_ptr<Model::World> &world);

    void update(const key &key) override;

    ~VictoryState() override;

    [[nodiscard]] double getVictoryTime() const;

};


#endif //PAC_MAN_VICTORYSTATE_H
