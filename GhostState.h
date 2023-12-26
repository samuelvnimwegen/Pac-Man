//
// Created by Samuel on 26/12/2023.
//

#ifndef PAC_MAN_GHOSTSTATE_H
#define PAC_MAN_GHOSTSTATE_H

enum ghostStateTag{idle, chasing, frightened, reset};

#include "Subject.h"
class Model::GhostState {
protected:
    ghostStateTag tag;
public:
    GhostState();

    virtual std::shared_ptr<GhostState> getNext() = 0;
};


#endif //PAC_MAN_GHOSTSTATE_H
