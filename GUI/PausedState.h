//
// Created by Samuel on 16/11/2023.
//

#ifndef PAC_MAN_PAUSEDSTATE_H
#define PAC_MAN_PAUSEDSTATE_H
#include "State.h"
#include "MenuState.h"

class GUI::PausedState: public GUI::State {
    double pausedTime;
public:
    PausedState(const std::weak_ptr<StateManager> &stateManager, const std::weak_ptr<Model::World> &world);

    void update(const key &key) override;

    ~PausedState() override;

    [[nodiscard]] double getPausedTime() const;
};


#endif //PAC_MAN_PAUSEDSTATE_H
