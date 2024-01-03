//
// Created by Samuel on 16/11/2023.
//

#ifndef PAC_MAN_GHOST_H
#define PAC_MAN_GHOST_H
#include "EntityModel.h"
#include "Subject.h"
#include "GhostStateManager.h"
#include "GhostIdleState.h"

class Model::Ghost: public Model::EntityModel{
    std::weak_ptr<Model::World> world;
    direction startDirection;
    direction currentDirection;
    direction nextDirection;
    std::shared_ptr<Model::GhostStateManager> stateManager;
    int startRow;
    int startCol;
    double waitTime;
    double speed;
    double defaultSpeed;
    bool frightened;
    double frightenTime;
public:
    Ghost(int row, int col, const std::shared_ptr<Model::World>& world);

    void move(const double &seconds);

    void update(const double &seconds) override;

    void changeDirection();

    void reset();

    direction getDijkstraDirection();

    [[nodiscard]] bool canMove(const int &row, const int &col) ;

    bool canMove(const direction &direction);

    [[nodiscard]] int getManhattanDistancePacMan(const direction &direction);

    int getManhattanDistanceSpawn(const direction &direction);

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

    [[nodiscard]] const std::shared_ptr<Model::GhostStateManager> &getStateManager() const;

    [[nodiscard]] double getWaitTime() const;

    void setWaitTime(double seconds);

    [[nodiscard]] bool isFrightened() const;

    void setFrightened(bool b);

    void setSpeed(double d);

    [[nodiscard]] double getDefaultSpeed();

    [[nodiscard]] double getFrightenTime() const;

    void setFrightenTime(double d);
};
template<typename T> T templateMax(const T &x, const T &y);


#endif //PAC_MAN_GHOST_H
