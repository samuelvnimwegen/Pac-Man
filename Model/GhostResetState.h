//
// Created by Samuel on 26/12/2023.
//

#ifndef PAC_MAN_GHOSTRESETSTATE_H
#define PAC_MAN_GHOSTRESETSTATE_H
#include "Subject.h"
#include "GhostState.h"
#include "Ghost.h"

class Model::GhostResetState: public Model::GhostState{
public:
    GhostResetState(const std::weak_ptr<Model::GhostStateManager> &stateManager,
                    const std::weak_ptr<Model::Ghost> &ghost);

    void update() override;
};


#endif //PAC_MAN_GHOSTRESETSTATE_H
