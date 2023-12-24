//
// Created by Samuel on 16/11/2023.
//

#ifndef PAC_MAN_GHOST_H
#define PAC_MAN_GHOST_H
#include "EntityModel.h"
#include "Subject.h"

class Model::Ghost: public Model::EntityModel{
    std::weak_ptr<Model::World> world;
    direction startDirection;
    direction currentDirection;
    direction nextDirection;
    std::string currentState;
    int startRow;
    int startCol;
    double speed;


public:
    Ghost(int row, int col, const std::shared_ptr<Model::World>& world);

    void move(const double &seconds);

    void update(const double &seconds) override;

    void changeDirection();

    void reset();

    [[nodiscard]] bool canMove(const int &row, const int &col) ;

    bool canMove(const direction &direction);

    [[nodiscard]] int getManhattanDistance(const direction &direction);

    [[nodiscard]] const std::string &getCurrentState() const;

    void setCurrentState(const std::string &state);

    [[nodiscard]] int getStartRow() const;

    [[nodiscard]] int getStartCol() const;

    [[nodiscard]] direction getCurrentDirection() const;

    void setCurrentDirection(direction direction);

    [[nodiscard]] direction getNextDirection() const;

    void setNextDirection(direction direction);

    [[nodiscard]]  std::shared_ptr<Model::World> getWorld() ;

    [[nodiscard]] double getSpeed() const;

    [[nodiscard]] direction getStartDirection() const;

    void setStartDirection(direction direction);
};
template<typename T> T templateMax(const T &x, const T &y);


#endif //PAC_MAN_GHOST_H
