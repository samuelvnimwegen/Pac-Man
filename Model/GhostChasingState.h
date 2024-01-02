//
// Created by Samuel on 26/12/2023.
//

#ifndef PAC_MAN_GHOSTCHASINGSTATE_H
#define PAC_MAN_GHOSTCHASINGSTATE_H
#include "Subject.h"
#include "GhostState.h"
#include "Ghost.h"
class Model::GhostChasingState: public Model::GhostState{
public:
    GhostChasingState(const std::weak_ptr<Model::GhostStateManager> &stateManager,
                      const std::weak_ptr<Model::Ghost> &ghost);

    void update() override;

};


#endif //PAC_MAN_GHOSTCHASINGSTATE_H
