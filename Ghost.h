//
// Created by Samuel on 16/11/2023.
//

#ifndef PAC_MAN_GHOST_H
#define PAC_MAN_GHOST_H
#include "EntityModel.h"
class World;
class Ghost: public EntityModel{
    World* world;
    string color;
    string currentDirection;
    string currentState;
    double xSpeed;
    double ySpeed;
    bool justTurned;
public:
    Ghost(int row, int col, World *world);

    void move(const int &steps);

    void changeDirection();

    [[nodiscard]] bool canMove(const int &row, const int &col) const;

    [[nodiscard]] int getManhattanDistance(const string& direction);

    [[nodiscard]] World *getWorld() const;

    [[nodiscard]] const string &getColor() const;

    void setColor(const string &color);

    [[nodiscard]] const string &getCurrentDirection() const;

    void setCurrentDirection(const string &direction);

    [[nodiscard]] double getXSpeed() const;

    void setXSpeed(double speed);

    [[nodiscard]] double getYSpeed() const;

    void setYSpeed(double speed);

    [[nodiscard]] bool isJustTurned() const;

    void setJustTurned(bool turned);
};


#endif //PAC_MAN_GHOST_H
