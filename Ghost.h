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
    string nextDirection;
    string currentState;
    double xSpeed;
    double ySpeed;
    bool justTurned;
    int startRow;
    int startCol;

public:
    Ghost(int row, int col, World *world);

    void move(const int &steps);

    void changeDirection();

    void reset();

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

    [[nodiscard]] const string &getNextDirection() const;

    void setNextDirection(const string &direction);

    void setWorld(World *gWorld);

    [[nodiscard]] const string &getCurrentState() const;

    void setCurrentState(const string &state);

    [[nodiscard]] int getStartRow() const;

    void setStartRow(int row);

    [[nodiscard]] int getStartCol() const;

    void setStartCol(int col);
};


#endif //PAC_MAN_GHOST_H
