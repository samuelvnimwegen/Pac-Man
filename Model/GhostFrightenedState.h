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
    bool firstDirectionChange;
public:
    GhostFrightenedState(const std::weak_ptr<Model::GhostStateManager> &stateManager,
                         const std::weak_ptr<Model::Ghost> &ghost);

    GhostFrightenedState(const std::weak_ptr<Model::GhostStateManager> &stateManager,
                         const std::weak_ptr<Model::Ghost> &ghost, double frightenedTime);

    void update() override;

    [[nodiscard]] double getFrightenedTime() const;

    [[nodiscard]] bool isFirstDirectionChange() const;

    void setFirstDirectionChange(bool change);
};


#endif //PAC_MAN_GHOSTFRIGHTENEDSTATE_H
