//
// Created by Samuel on 26/12/2023.
//

#ifndef PAC_MAN_GHOSTCHASINGSTATE_H
#define PAC_MAN_GHOSTCHASINGSTATE_H
#include "Subject.h"
#include "GhostState.h"
class Model::GhostChasingState: public Model::GhostState{
public:
    GhostChasingState();

    std::shared_ptr<GhostState> getNext() override;
};


#endif //PAC_MAN_GHOSTCHASINGSTATE_H
