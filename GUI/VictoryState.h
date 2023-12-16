//
// Created by Samuel on 16/11/2023.
//

#ifndef PAC_MAN_VICTORYSTATE_H
#define PAC_MAN_VICTORYSTATE_H
#include "State.h"

class GUI::VictoryState: public GUI::State {
public:
    VictoryState();

    ~VictoryState() override;

    std::shared_ptr<State> getNext() override;
};


#endif //PAC_MAN_VICTORYSTATE_H
