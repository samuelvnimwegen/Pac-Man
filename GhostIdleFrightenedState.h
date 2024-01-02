//
// Created by Samuel on 02/01/2024.
//

#ifndef PAC_MAN_GHOSTIDLEFRIGHTENEDSTATE_H
#define PAC_MAN_GHOSTIDLEFRIGHTENEDSTATE_H
#include "Subject.h"
#include "GhostState.h"

class Model::GhostIdleFrightenedState: public Model::GhostState{
    double frightenedTime;
public:
    GhostIdleFrightenedState(const std::weak_ptr<Model::GhostStateManager> &stateManager,
                             const std::weak_ptr<Model::Ghost> &ghost);

    void update() override;

    [[nodiscard]] double getFrightenedTime() const;
};


#endif //PAC_MAN_GHOSTIDLEFRIGHTENEDSTATE_H
