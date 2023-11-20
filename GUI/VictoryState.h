//
// Created by Samuel on 16/11/2023.
//

#ifndef PAC_MAN_VICTORYSTATE_H
#define PAC_MAN_VICTORYSTATE_H
#include "State.h"

class VictoryState: public State {
public:
    VictoryState();

    ~VictoryState() override;

    State* getNext() override;
};


#endif //PAC_MAN_VICTORYSTATE_H
