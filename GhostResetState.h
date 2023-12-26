//
// Created by Samuel on 26/12/2023.
//

#ifndef PAC_MAN_GHOSTRESETSTATE_H
#define PAC_MAN_GHOSTRESETSTATE_H
#include "Subject.h"
#include "GhostState.h"

class Model::GhostResetState: public Model::GhostState{
public:
    GhostResetState();

    std::shared_ptr<GhostState> getNext() override;
};


#endif //PAC_MAN_GHOSTRESETSTATE_H
