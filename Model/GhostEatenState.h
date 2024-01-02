//
// Created by Samuel on 29/12/2023.
//

#ifndef PAC_MAN_GHOSTEATENSTATE_H
#define PAC_MAN_GHOSTEATENSTATE_H
#include "Subject.h"
#include "GhostState.h"
class Model::GhostEatenState: public Model::GhostState{
    double eatenTime;
public:
    GhostEatenState(const std::weak_ptr<Model::GhostStateManager> &stateManager,
                    const std::weak_ptr<Model::Ghost> &ghost);

    void update() override;

    [[nodiscard]] double getEatenTime() const;
};


#endif //PAC_MAN_GHOSTEATENSTATE_H
