//
// Created by Samuel on 16/11/2023.
//

#ifndef PAC_MAN_OBSERVER_H
#define PAC_MAN_OBSERVER_H
#include "World.h"

class Observer {
    World* world;
public:
    Observer();

    Observer(World *world);

    [[nodiscard]] World *getWorld() const;

    void setWorld(World *world);
};


#endif //PAC_MAN_OBSERVER_H
