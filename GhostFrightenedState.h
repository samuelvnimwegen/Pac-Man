//
// Created by Samuel on 26/12/2023.
//

#ifndef PAC_MAN_GHOSTFRIGHTENEDSTATE_H
#define PAC_MAN_GHOSTFRIGHTENEDSTATE_H
#include "Subject.h"
#include "GhostState.h"
#include "World.h"
#include "GhostResetState.h"
#include "GhostEatenState.h"

class Model::GhostFrightenedState: public Model::GhostState{
    double frightenedTime;
public:
    GhostFrightenedState(const std::weak_ptr<Model::GhostStateManager> &stateManager,
                         const std::weak_ptr<Model::Ghost> &ghost);

    void update() override;

    [[nodiscard]] double getFrightenedTime() const;
};


#endif //PAC_MAN_GHOSTFRIGHTENEDSTATE_H
