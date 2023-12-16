//
// Created by Samuel on 16/11/2023.
//

#ifndef PAC_MAN_PAUSEDSTATE_H
#define PAC_MAN_PAUSEDSTATE_H
#include "State.h"
#include "MenuState.h"
class GUI::PausedState: public GUI::State {
public:
    PausedState();

    ~PausedState() override;

    std::shared_ptr<State> getNext() override;
};


#endif //PAC_MAN_PAUSEDSTATE_H
