//
// Created by Samuel on 26/12/2023.
//

#ifndef PAC_MAN_GHOSTIDLESTATE_H
#define PAC_MAN_GHOSTIDLESTATE_H
#include "GhostState.h"
class Model::GhostIdleState: public Model::GhostState{
public:
    GhostIdleState();

    std::shared_ptr<GhostState> getNext() override;
};


#endif //PAC_MAN_GHOSTIDLESTATE_H
