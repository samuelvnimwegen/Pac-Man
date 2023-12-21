//
// Created by Samuel on 16/11/2023.
//

#ifndef PAC_MAN_OBSERVER_H
#define PAC_MAN_OBSERVER_H
#include "Subject.h"
#include "SFML/Graphics.hpp"

class Model::Observer {
public:
    Observer();

    [[nodiscard]] virtual double getCameraX() const = 0;

    virtual void setCameraX(double x) = 0;

    [[nodiscard]] virtual double getCameraY() const = 0;

    virtual void setCameraY(double y) = 0;

    virtual void move(const int &ticks) = 0;

    virtual void update(const int &ticks) = 0;

};


#endif //PAC_MAN_OBSERVER_H
