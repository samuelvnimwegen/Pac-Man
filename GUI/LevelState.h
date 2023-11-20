//
// Created by Samuel on 16/11/2023.
//

#ifndef PAC_MAN_LEVELSTATE_H
#define PAC_MAN_LEVELSTATE_H
#include "State.h"
#include "VictoryState.h"
class LevelState: public State {
public:
    LevelState();

    ~LevelState() override;

    VictoryState* getNext() override;
};


#endif //PAC_MAN_LEVELSTATE_H
