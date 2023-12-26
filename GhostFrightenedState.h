//
// Created by Samuel on 26/12/2023.
//

#ifndef PAC_MAN_GHOSTFRIGHTENEDSTATE_H
#define PAC_MAN_GHOSTFRIGHTENEDSTATE_H
#include "Subject.h"
#include "GhostState.h"

class Model::GhostFrightenedState: public Model::GhostState{
public:
    GhostFrightenedState();

    std::shared_ptr<GhostState> getNext() override;
};


#endif //PAC_MAN_GHOSTFRIGHTENEDSTATE_H
