//
// Created by Samuel on 16/11/2023.
//

#ifndef PAC_MAN_OBSERVER_H
#define PAC_MAN_OBSERVER_H
#include "World.h"

class Model::Observer {
public:
    Observer();

    virtual void changeDirection(const direction &direction);

    [[nodiscard]] virtual double getCameraX() const = 0;

    virtual void setCameraX(double x) = 0;

    [[nodiscard]] virtual double getCameraY() const = 0;

    virtual void setCameraY(double y) = 0;
};


#endif //PAC_MAN_OBSERVER_H
