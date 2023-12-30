//
// Created by Samuel on 16/11/2023.
//

#ifndef PAC_MAN_STATE_H
#define PAC_MAN_STATE_H
#include "iostream"
#include "vector"
#include "../Subject.h"

enum key{space, backspace, escape, noKey};

enum stateTag{victory, menu, paused, level};

class GUI::State {
    stateTag tag;
    std::weak_ptr<StateManager> stateManager;
    std::weak_ptr<Model::World> world;
public:
    State(const std::weak_ptr<StateManager> &stateManager, const std::weak_ptr<Model::World> &world);

    virtual ~State();

    virtual void update(const key &key) = 0;

    [[nodiscard]] stateTag getTag() const;

    void setTag(const stateTag &stateTag);

    const std::weak_ptr<StateManager> &getStateManager() const;

    const std::weak_ptr<Model::World> &getWorld() const;
};


#endif //PAC_MAN_STATE_H
