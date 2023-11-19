//
// Created by Samuel on 19/11/2023.
//

#ifndef PAC_MAN_PACMAN_H
#include "EntityModel.h"
#define PAC_MAN_PACMAN_H


class World;
class PacMan: public EntityModel{
    World* world;
    string currentDirection;
    double xSpeed;
    double ySpeed;
public:
    PacMan(int row, int col, World *world);

    void move(const int &ticks);

    [[nodiscard]] const string &getCurrentDirection() const;

    void setCurrentDirection(const string &direction);

    [[nodiscard]] World *getWorld() const;

    void setWorld(World *pWorld);

    [[nodiscard]] double getXSpeed() const;

    void setXSpeed(double speed);

    [[nodiscard]] double getYSpeed() const;

    void setYSpeed(double speed);
};


#endif //PAC_MAN_PACMAN_H
