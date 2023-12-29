//
// Created by Samuel on 26/12/2023.
//

#ifndef PAC_MAN_GHOSTSTATE_H
#define PAC_MAN_GHOSTSTATE_H

enum ghostStateTag{idle, chasing, frightened, reset, eaten};

#include "Subject.h"
class Model::GhostState {
    std::weak_ptr<Model::GhostStateManager> stateManager;
    std::weak_ptr<Model::Ghost> ghost;
protected:
    ghostStateTag tag;
public:
    GhostState(const std::weak_ptr<Model::GhostStateManager> &stateManager, const std::weak_ptr<Model::Ghost> &ghost);

    virtual ~GhostState();

    virtual void update() = 0;

    [[nodiscard]] ghostStateTag getTag() const;

    [[nodiscard]] const std::weak_ptr<Model::GhostStateManager> &getStateManager() const;

    [[nodiscard]] const std::weak_ptr<Model::Ghost> &getGhost() const;
};


#endif //PAC_MAN_GHOSTSTATE_H
