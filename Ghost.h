//
// Created by Samuel on 16/11/2023.
//

#ifndef PAC_MAN_GHOST_H
#define PAC_MAN_GHOST_H
#include "EntityModel.h"
#include "Subject.h"

class Model::Ghost: public Model::EntityModel{
    Model::World* world;
    color ghostColor;
    direction currentDirection;
    direction nextDirection;
    std::string currentState;
    bool justTurned;
    int startRow;
    int startCol;

public:
    Ghost(int row, int col, World *world);

    void move(const int &steps);

    void changeDirection();

    void reset();

    [[nodiscard]] bool canMove(const int &row, const int &col) const;

    [[nodiscard]] int getManhattanDistance(const direction &direction);

    [[nodiscard]] World *getWorld() const;

    [[nodiscard]] bool isJustTurned() const;

    void setJustTurned(bool turned);

    void setWorld(World *gWorld);

    [[nodiscard]] const std::string &getCurrentState() const;

    void setCurrentState(const std::string &state);

    [[nodiscard]] int getStartRow() const;

    void setStartRow(int row);

    [[nodiscard]] int getStartCol() const;

    void setStartCol(int col);

    color getColor() const;

    void setColor(color col);

    direction getCurrentDirection() const;

    void setCurrentDirection(direction direction);

    direction getNextDirection() const;

    void setNextDirection(direction direction);
};


#endif //PAC_MAN_GHOST_H
